#include <stdio.h>
#include <string.h>
#include <ctype.h>

char Productions_List[100][100][100];
int FollowFound[100] = {0};

// Used to add to both First and Follow based on mode
void Add_Terminal_To_List(char terminal, char List[100][100], int Variable_Number, int mode)
{
    // if(mode)
    // 	printf("\tNeed to add %c to Follow[%d]\n",terminal,Variable_Number);
    int len = strlen(List[Variable_Number]);
    int i, found_flag = 0;
    if (mode == 1)
    {
        if (terminal == '#')
            return;
    }
    for (i = 0; i < len; i++)
    {
        if (List[Variable_Number][i] == terminal)
        {
            // printf("\tAlready Present\n");
            found_flag = 1;
            break;
        }
    }
    if (found_flag == 0)
    {
        // printf("\tNot Present so added at pos %d\n",len);
        List[Variable_Number][len] = terminal;
        List[Variable_Number][len + 1] = '\0';
    }
    return;
}

// Used to Make The Production Table
int AddProductionsToList(int Variable_Number, char Production[100])
{
    int i, j, len;
    int Production_Number = 0;
    len = strlen(Production);
    for (i = 0, j = 0; i < len; i++)
    {
        if (Production[i] == '|')
        {
            Productions_List[Variable_Number][Production_Number][j] = '\0';
            Production_Number++;
            j = 0;
        }
        else
        {
            Productions_List[Variable_Number][Production_Number][j] = Production[i];
            j++;
        }
    }
    return (Production_Number + 1);
}

// Used to Display Entire Table
void DisplayTransitions(char Variable_List[100], int Corresponding_Number_of_Productions[100], int N)
{
    int i, j, z;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < Corresponding_Number_of_Productions[i]; j++)
        {
            printf("\t%c -> ", Variable_List[i]);
            for (z = 0; Productions_List[i][j][z] != '\0'; z++)
            {
                printf("%c", Productions_List[i][j][z]);
            }
            printf("\n");
        }
    }
}

// Used to return the location in the list of Variables given the character
int GetVariableNumber(char Variable, char Variable_list[100], int N)
{
    int i = 0, Variable_Number = 0;
    for (i = 0; i < N; i++)
        if (Variable_list[i] == Variable)
            Variable_Number = i;
    return (Variable_Number);
}

// Recursve function to find the First
int Find_First(char First[100][100], int Corresponding_Number_of_Productions[100], char Variable_list[100], char original, int Found[], int Total)
{
    // printf("In Func for %c\n",original);
    int i, j, N, p, len, precision, Variable_Number;
    int Next_Variable_Number;
    int Nullout = 0, position;
    char t;
    Variable_Number = GetVariableNumber(original, Variable_list, Total);

    if (Found[Variable_Number] == -1)
        return -1;

    if (Found[Variable_Number] == 1)
        return 1;

    position = 0;
    precision = 0;

    N = Corresponding_Number_of_Productions[Variable_Number];
    for (position = 0; position <= precision; position++)
    {
        for (i = 0; i < N; i++)
        {
            // printf("In production:%s\n",Productions_List[Variable_Number][i]);
            t = Productions_List[Variable_Number][i][position];
            if (isupper(t))
            {
                // printf("Is Upper\n");
                Nullout = Find_First(First, Corresponding_Number_of_Productions, Variable_list, t, Found, Total);
                Next_Variable_Number = GetVariableNumber(t, Variable_list, Total);
                len = strlen(First[Next_Variable_Number]);
                for (j = 0; j <= len; j++)
                {
                    Add_Terminal_To_List(First[Next_Variable_Number][j], First, Variable_Number, 0);
                }

                if (Nullout == -1)
                {
                    len = strlen(Productions_List[Variable_Number][i]); // Rule 3 for First
                    if (precision < len)
                    {
                        // printf("\t\tNeed to go 1 more round casue of #");
                        precision += 1;
                    }
                }
            }
            else if (t == '#') // Rule 1 for First
            {
                Nullout = -1;
                Add_Terminal_To_List(t, First, Variable_Number, 0);
                Found[Variable_Number] = Nullout;
            }
            else
            {
                Add_Terminal_To_List(t, First, Variable_Number, 0); // Rule 2 for First
                Found[Variable_Number] = 1;
            }
        }
    }
    return (Nullout);
}

// Recursive Function to find the Follow
void Follow_Of(char Follow[100][100], char First[100][100], int original, char Variable_List[100], int N, int Corresponding_Number_of_Productions[100], int Found[100])
{
    // printf("In Follow(%c)\n",Variable_List[original]);
    if (FollowFound[original] != 0)
    {
        return;
    }
    else
    {
        FollowFound[original] = 1;
    }

    char Variable = Variable_List[original];
    int Character_Number, i, j, Variable_Number;
    char character, next_character, temp;
    int Production_Number, Number_Of_Productions;
    int next_char_number, nflag, fflag, temp_number;
    // for(i=0;i<N;i++)
    // 	printf("_%d",Found[i]);
    for (Variable_Number = 0; Variable_Number < N; Variable_Number++)
    {
        Number_Of_Productions = Corresponding_Number_of_Productions[Variable_Number];
        for (Production_Number = 0; Production_Number < Number_Of_Productions; Production_Number++)
        {
            Character_Number = 0;
            character = Productions_List[Variable_Number][Production_Number][Character_Number];
            for (; character != '\0'; Character_Number++)
            {
                character = Productions_List[Variable_Number][Production_Number][Character_Number];
                if (character == Variable)
                {
                    // printf("\tfound Variable in %c -> %s\n",Variable_List[Variable_Number],Productions_List[Variable_Number][Production_Number]);
                    next_character = Productions_List[Variable_Number][Production_Number][Character_Number + 1];
                    if (next_character == '\0')
                    {
                        // printf("Is last character\nSo Follow(%c)==Follow(%c)\n",Variable,Variable_List[Variable_Number]);
                        Follow_Of(Follow, First, Variable_Number, Variable_List, N, Corresponding_Number_of_Productions, Found); // Rule 2 of Follow
                        for (i = 0; i < strlen(Follow[Variable_Number]); i++)
                        {
                            Add_Terminal_To_List(Follow[Variable_Number][i], Follow, original, 1);
                        }
                        // printf("Done\n");
                        break;
                    }
                    else
                    {
                        if (isupper(next_character))
                        {
                            // printf("\tNext Character is Variable: %c\n",next_character);
                            next_char_number = GetVariableNumber(next_character, Variable_List, N);
                            // printf("number = %d\n",next_char_number);
                            if (Found[next_char_number] != -1) // Rule 3a of Follow
                            {
                                // printf("\t%c Doesnt contain '#' as %d\n",next_character,Found[next_char_number]);
                                for (i = 0; i < strlen(First[next_char_number]); i++)
                                {
                                    Add_Terminal_To_List(First[next_char_number][i], Follow, original, 1);
                                }
                            }
                            else
                            {
                                // printf("Has '#' as %d so-\n",Found[next_char_number]);
                                nflag = 0;
                                fflag = strlen(Productions_List[Variable_Number][Production_Number]);
                                fflag = fflag - (Character_Number + 1);

                                temp = Productions_List[Variable_Number][Production_Number][Character_Number + 1];
                                for (j = Character_Number + 1; temp != '\0'; j++)
                                {
                                    temp = Productions_List[Variable_Number][Production_Number][j];
                                    if (temp == '\0')
                                        break;
                                    // printf("\t\tchecking %c",temp);
                                    if (islower(temp) || !isalnum(temp))
                                    {
                                        // printf("\t\tIs a Terminal\n");
                                        Add_Terminal_To_List(temp, Follow, original, 1);
                                        break;
                                    }
                                    else
                                    {
                                        // printf("\t\tIs a Variable\n");
                                        temp_number = GetVariableNumber(temp, Variable_List, N);
                                        if (Found[temp_number] == -1)
                                        {
                                            nflag += 1;
                                            for (i = 0; i < strlen(First[temp_number]); i++)
                                            {
                                                Add_Terminal_To_List(First[temp_number][i], Follow, original, 1);
                                            }
                                        }
                                        else
                                        {
                                            for (i = 0; i < strlen(First[temp_number]); i++)
                                                Add_Terminal_To_List(First[temp_number][i], Follow, original, 1);
                                            break;
                                        }
                                        if (fflag == nflag)
                                        {
                                            // printf("Rest is equivalent to '#'");
                                            Follow_Of(Follow, First, Variable_Number, Variable_List, N, Corresponding_Number_of_Productions, Found);
                                            for (i = 0; i < strlen(Follow[Variable_Number]); i++)
                                            {
                                                Add_Terminal_To_List(Follow[Variable_Number][i], Follow, original, 1);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            Add_Terminal_To_List(next_character, Follow, original, 1);
                            break;
                        }
                    }
                }
            }
        }
    }
    // printf("\nEnd_OF_Function!!\n");
}

void main(void)
{
    int N = 0, i, j, k, z;
    int Number_of_Productions = 0, Variable_Number;
    char Variable, Start_Variable = 'S', Production[100];
    char Variable_List[100];
    char First[100][100];
    char Follow[100][100];
    int Found[100], Nullout;
    int Corresponding_Number_of_Productions[100];
    FILE *fp;
    fp = fopen("input.txt", "r");
    fscanf(fp, "\n%c -> %s", &Start_Variable, Production);
    N++;
    Variable_Number = 0;
    Variable_List[Variable_Number] = Start_Variable;
    Number_of_Productions = AddProductionsToList(Variable_Number, Production);
    Corresponding_Number_of_Productions[Variable_Number] = Number_of_Productions;
    Variable_Number++;
    while (!feof(fp))
    {
        // fscanf(fp, "%d", &N);
        fscanf(fp, "\n%c -> %s", &Variable, Production);
        Variable_List[Variable_Number] = Variable;
        Number_of_Productions = AddProductionsToList(Variable_Number, Production);
        Corresponding_Number_of_Productions[Variable_Number] = Number_of_Productions;
        Variable_Number++;
        N++;
    }

    printf("\n\n");
    DisplayTransitions(Variable_List, Corresponding_Number_of_Productions, N);
    printf("\n\n");
    // Find_First()
    for (i = 0; i < N; i++)
    {
        strcpy(First[i], "");
        Found[i] = 0;
    }
    for (i = 0; i < N; i++)
    {
        if (Found[i] == 0)
            Nullout = Find_First(First, Corresponding_Number_of_Productions, Variable_List, Variable_List[i], Found, N);
    }
    for (i = 0; i < N; i++)
    {
        printf("First(%c) -> ", Variable_List[i]);
        for (j = 0; j < strlen(First[i]); j++)
        {
            if (Variable_List[i] == 'S')
            {
                if (First[i][j] != '#')
                {
                    printf("%c ", First[i][j]);
                }
                if (First[i][j] == '#')
                    Found[i] = -1;
            }
            else
            {
                printf("%c ", First[i][j]);
                if (First[i][j] == '#')
                    Found[i] = -1;
            }
        }
        printf("\n");
    }
    // Find Follow
    strcpy(Follow[0], "$"); // Rule 1 of Follow
    for (i = 1; i < N; i++)
    {
        strcpy(Follow[i], "");
    }
    for (Variable_Number = 0; Variable_Number < N; Variable_Number++)
    {
        // printf("Main::");
        Follow_Of(Follow, First, Variable_Number, Variable_List, N, Corresponding_Number_of_Productions, Found);
    }
    printf("\n\n");
    for (i = 0; i < N; i++)
    {
        printf("Follow(%c) -> ", Variable_List[i]);
        for (j = 0; j < strlen(Follow[i]); j++)
            printf("%c ", Follow[i][j]);
        printf("\n");
    }
}