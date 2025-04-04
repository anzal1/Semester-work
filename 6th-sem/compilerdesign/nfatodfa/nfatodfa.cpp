#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>    //for use in State Moves
#include <map>       //for use in State Table
#include <stack>     // for use in eclosure
#include <utility>   //pair, make_pair
#include <algorithm> //sort
using namespace std;
/*************************************************************
 * Global Variables, Structs, Typedefs
 **************************************************************/
const char OPENING_BRACKET = '{';
const char CLOSING_BRACKET = '}';

struct DFAState
{
    bool marked;
    vector<int> states;
    map<char, int> moves;
};

typedef map<int, DFAState> DFATableType;
typedef map<int, map<char, vector<int>>> NFATableType;

int INIT_STATE;
int TOTAL_STATES;
vector<int> FINAL_STATES;
vector<char> ALPHABET;
NFATableType STATE_TABLE;
DFATableType DFA_STATE_TABLE;

/*************************************************************
 * Membership Function:
 * Check if a vector<int> contains a certain integer.
 **************************************************************/
bool doesVectorContain(vector<int> vec, int key)
{
    for (vector<int>::const_iterator k = vec.begin(); k != vec.end(); k++)
    {
        if (*k == key)
        {
            return true;
        }
    }
    return false;
}

/*************************************************************
 * Print Vector Function:
 * Print a given vector in e-closure format: {x,y,z,..}
 **************************************************************/
void printVector(vector<int> vec)
{
    cout << "{";
    for (vector<int>::const_iterator i = vec.begin(); i != vec.end(); i++)
    {
        if (i != vec.end() - 1)
        {
            cout << *i << ",";
        }
        else
        {
            cout << *i;
        }
    }
    cout << "} ";
}

/*************************************************************
 * isAnythingUnmarked function:
 * Loop over the DTransition table and look for unmarked states.
 * If an unmarked state exists, return the int corresponding
 * to that state. If all states are marked, return -1.
 **************************************************************/
int isAnythingUnmarked(DFATableType DFATable)
{
    int size = DFATable.size();
    for (int i = 0; i < size; i++)
    {
        DFAState current = DFATable[i];
        if (!(current.marked))
        {
            return i;
        }
    }
    // everything is marked
    return -1;
}

/*************************************************************
 * isAMember function:
 * Checks to see if a vector<int> representing a DFAState
 * is already contained within the DFAStateTable.
 * If it is a member, return the state index. If not, return -1.
 **************************************************************/
int isAMember(vector<int> state, DFATableType DFATable)
{
    int size = DFATable.size();
    for (int i = 0; i < size; i++)
    {
        DFAState current = DFATable[i];
        // compare the two vectors
        if (current.states == state)
        {
            return i;
        }
    }
    // state is not already within the table
    return -1;
}

/*************************************************************
 * EClosure Function
 *
 * Given a state T, find and return the
 * eclosure as a vector<int>.
 **************************************************************/
vector<int> eclosure(vector<int> T, NFATableType NFATable)
{
    vector<int> eclosure;
    stack<int> myStack;

    // push all states of T onto stack;
    for (vector<int>::const_iterator j = T.begin(); j != T.end(); j++)
    {
        myStack.push(*j);
    }

    // init e-closure(T) to T
    for (vector<int>::const_iterator i = T.begin(); i != T.end(); i++)
    {
        eclosure.push_back(*i);
    }

    while (!(myStack.empty()))
    {

        int cur = myStack.top();
        myStack.pop();

        /*
         * We are looking at all the states reachable via an
         * epsilon move. So, fetch that state from the NFA Table,
         * and fetch its vector of E moves.
         */
        map<char, vector<int>> currentState = NFATable[cur];
        vector<int> EMoves = currentState['E'];

        // for each state within the EMoves vector
        for (vector<int>::const_iterator i = EMoves.begin(); i != EMoves.end(); i++)
        {

            /*
             * If the state is not already in, add it to
             * eclosure and push it onto the stack.
             */
            if (!(doesVectorContain(eclosure, *i)))
            {
                eclosure.push_back(*i);
                myStack.push(*i);
            }
        }
    }
    // for consistency in comparison, sort the eclosure
    sort(eclosure.begin(), eclosure.end());
    return eclosure;
}

/*************************************************************
 * Move Function
 *
 * Given a state T and a move x, return all reachable states
 * given that moves as a vector<int>.
 **************************************************************/
vector<int> move(vector<int> T, char move, NFATableType NFATable)
{
    vector<int> ans;
    for (vector<int>::const_iterator j = T.begin(); j != T.end(); j++)
    {
        // get the moves vector for the state and move
        vector<int> reachableStates = NFATable[*j][move];
        for (vector<int>::const_iterator k = reachableStates.begin(); k != reachableStates.end(); k++)
        {
            // if k is not already in ans, add it
            if (!(doesVectorContain(ans, *k)))
            {
                ans.push_back(*k);
            }
        }
    }
    // for consistency in comparison, sort the eclosure
    sort(ans.begin(), ans.end());
    return ans;
}

/*************************************************************
 * DFAState Constuctor Function
 *
 * Helper function to initialize and return a new DFAState.
 **************************************************************/
DFAState newDFAState(bool mark, vector<int> s)
{
    DFAState newState;
    map<char, int> init;
    newState.marked = mark;
    newState.states = s;
    newState.moves = init;
    return newState;
}

/*************************************************************
 * findFinalDFAStates Function
 *
 * Takes in the final state(s) of the NFA, parses the DFATable
 * to see which states should be marked as final.
 **************************************************************/
vector<int> findFinalDFAStates(DFATableType DFATable, vector<int> finalStates)
{
    vector<int> finals;
    for (int i = 0; i < DFATable.size(); i++)
    {
        for (vector<int>::const_iterator k = finalStates.begin(); k != finalStates.end(); k++)
        {
            if (doesVectorContain(DFATable[i].states, *k))
            {
                finals.push_back(i);
            }
        }
    }
    return finals;
}

/*************************************************************
 * Subset Construction Function
 *
 * Create the corresponding DFA Transition Table given an
 * initial state, final state(s), and an NFA Table
 **************************************************************/
void subsetConstruction(int initialState, vector<int> finalStates, NFATableType &NFATable, DFATableType &DFATable)
{

    int currentDFAStateNumber = 0;
    /*
     * Initially, e-closure(s0) is the only state in DStates, and it is unmarked.
     * Take the e-closure of the initial state and add it to DStates as unmarked.
     */

    vector<int> initialStateVector;
    initialStateVector.push_back(initialState);

    vector<int> eclos = eclosure(initialStateVector, NFATable);
    cout << "E-closure(IO) = ";
    printVector(eclos);
    cout << " = " << currentDFAStateNumber << "\n\n";

    // Adding the eclosure(s0) to DStates as unmarked.
    DFAState initState = newDFAState(false, eclos);

    DFATable[currentDFAStateNumber] = initState;
    currentDFAStateNumber++;

    while (isAnythingUnmarked(DFATable) >= 0)
    {

        int k = isAnythingUnmarked(DFATable);
        DFATable[k].marked = true;
        cout << "\nMark " << k << endl;

        for (vector<char>::const_iterator w = ALPHABET.begin(); w != ALPHABET.end() - 1; w++)
        {

            vector<int> theMove = move(DFATable[k].states, *w, NFATable);
            vector<int> alphaMove = eclosure(theMove, NFATable);

            // pretty print the move if it is not empty
            if (!(theMove.empty()))
            {
                printVector(DFATable[k].states);
                cout << "--" << *w << "--> ";
                printVector(theMove);
                cout << "\n";
                cout << "E-closure";
                printVector(theMove);
                cout << " = ";
                printVector(alphaMove);
                cout << " = ";
            }

            int j = isAMember(alphaMove, DFATable);

            if (j >= 0)
            {
                cout << j << "\n";
                DFATable[k].moves[*w] = j;
            }
            else
            {
                if (!(alphaMove.empty()))
                {

                    cout << currentDFAStateNumber << "\n";

                    // add alphamove as a new state to the DFATable.
                    DFAState newState = newDFAState(false, alphaMove);
                    DFATable[currentDFAStateNumber] = newState;
                    DFATable[k].moves[*w] = currentDFAStateNumber;
                    currentDFAStateNumber++;
                }
                else
                {
                    DFATable[k].moves[*w] = -1;
                }
            }
        }
    } // end while
    cout << "\n";
}

/*************************************************************
 * ReadFile function
 *
 * handles parsing input file and initializing all
 * high level variables.
 **************************************************************/
void readFile(string filename)
{

    string line;
    ifstream myfile(filename);

    if (myfile.is_open())
    {

        getline(myfile, line);

        /*************************************
         * GET INITIAL STATE
         *************************************/
        istringstream iss(line);
        char test = iss.get();

        while (iss.peek() != OPENING_BRACKET)
        {
            iss.ignore();
        }

        iss.ignore();
        iss >> INIT_STATE;

        /*************************************
         * GET FINAL STATES
         *************************************/
        getline(myfile, line);
        iss.str(line);

        while (iss.peek() != OPENING_BRACKET)
        {
            iss.ignore();
        }

        iss.ignore();
        int finalState;
        iss >> finalState;
        FINAL_STATES.push_back(finalState);

        // could have multiple final states. Look for a , loop until we hit the closing brace.
        while (iss.peek() != CLOSING_BRACKET)
        {
            if (iss.peek() == ',')
            {
                iss.ignore();
            }
            iss >> finalState;
            FINAL_STATES.push_back(finalState);
        }

        /*************************************
         * GET TOTAL STATES
         *************************************/
        getline(myfile, line);
        iss.str(line);

        while (iss.peek() != ':')
        {
            iss.ignore();
        }
        iss.ignore();
        iss.ignore();
        iss >> TOTAL_STATES;

        /*************************************
         * INITIALIZE NFA STATES
         *************************************/

        // READ IN THE ALPHABET
        getline(myfile, line);
        string trash;
        char move;
        istringstream alphabet(line);

        // consume the "state" word
        alphabet >> trash;

        while (alphabet >> move)
        {
            ALPHABET.push_back(move);
        }

        getline(myfile, line);

        for (int i = 1; i <= TOTAL_STATES; i++)
        {
            istringstream _iss(line);
            map<char, vector<int>> StateMovesMap;

            for (int j = 0; j < ALPHABET.size(); j++)
            {
                int state;
                string bracketMoves;
                vector<int> states;

                /*
                 * We are on a fresh line.ignore the state integer and the
                 * blank space.
                 */
                if (j == 0)
                {
                    _iss.ignore();
                    _iss.ignore();
                }
                else
                {
                    /*
                     * We are parsing moves after a, so just need to ignore the whitespace.
                     */
                    _iss.ignore();
                }

                _iss >> bracketMoves;
                // remove the opening and closing bracket
                bracketMoves = bracketMoves.substr(1, bracketMoves.size() - 2);

                if (bracketMoves != "")
                {

                    istringstream movestr(bracketMoves);

                    while (movestr >> state)
                    {
                        states.push_back(state);
                        if (movestr.peek() == ',')
                        {
                            movestr.ignore();
                        }
                    }
                }

                /*
                 * Finished parsing states for a move.
                 * Insert it into the StateMovesMap
                 */
                sort(states.begin(), states.end());
                StateMovesMap[ALPHABET[j]] = states;
            } // End Moves Loop

            /*
             * Finishing parsing all moves for a state. Insert the StateMovesMap
             * into the STATE_TABLE, which will be used in the subset and e-closure
             * functions
             */
            STATE_TABLE[i] = StateMovesMap;
            getline(myfile, line);
        } // End Total States Loop
    }     // End If My File is_open();
} // End ReadFile()

/*************************************************************
 * prettyPrintDFA function
 *
 * Prints DFATable in desired format.
 **************************************************************/
void prettyPrintDFA(DFATableType DFATable)
{

    // print out the whole alphabet.
    cout << "State      ";
    for (vector<char>::const_iterator k = ALPHABET.begin(); k != ALPHABET.end() - 1; k++)
    {
        cout << *k << "        ";
    }
    cout << endl;

    for (int i = 0; i < DFATable.size(); i++)
    {
        // for each DFA State, print out the moves for each alphabet symbol.
        cout << i << "         ";
        for (vector<char>::const_iterator k = ALPHABET.begin(); k != ALPHABET.end() - 1; k++)
        {
            cout << OPENING_BRACKET;
            if (DFATable[i].moves[*k] != -1)
            {
                cout << DFATable[i].moves[*k];
            }
            cout << CLOSING_BRACKET << "       ";
        }
        cout << endl;
    }
}

/*************************************************************
 * Main function
 *
 * Parse file, subset construction, print output.
 **************************************************************/
int main(int argc, char **argv)
{

    cout << "\n\n************************\nNFA to DFA CONVERSION\n************************\n\n";

    // parse input file to populate the global variables
    // string filename = argv[1];
    readFile("input.txt");

    // subset construction algo.
    subsetConstruction(INIT_STATE, FINAL_STATES, STATE_TABLE, DFA_STATE_TABLE);

    // printing out the Final DFA Table
    cout << "Initial State: {0}\n";
    cout << "Final State(s): ";
    printVector(findFinalDFAStates(DFA_STATE_TABLE, FINAL_STATES));
    cout << "\n";
    prettyPrintDFA(DFA_STATE_TABLE);

    return 0;
}

/*
Input file format :

Initial State: {1}
Final States: {3}
Total States: 3
State	a	b	E
1   {1} {1,2} {}
2   {} {3} {}
3	{}   {} {}

*/