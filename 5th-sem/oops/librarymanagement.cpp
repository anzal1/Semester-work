#include <iostream>
#include <string>
// #include <conio.h>
#include <stdlib.h>
using namespace std;

int main();
void show_data(int searchkey);      // function used to show data to end-user.
void get_data(int i);               // function used to obtain data from end-user.
void show_book_data(int searchkey); // function used to show data to end-user.
void get_book_data(int i);
void search_student(int searchkey);
void add_student();              // This function is used to add record of new student.
void edit_student(int idnumber); // function is used to edit existing record.
void search_book(int searchkey);
void add_book(); // This function is used to add record of new student.
void edit_book_info(int idnumber);
void issue_book(int id, int rollno);
void fullscreen();
int ts;

class student
{
public:
    int rollno;
    string name;
    string fname;
    string cell;
    string dob;
    string address;
};

class book
{
public:
    int bookid;
    string name;
    string author;
    string issue_date;
    int issued_roll;
};

student rec[50];
book library[50];
int main()
{
    // system("CLS");
    // system("color B1");
    int choice;    // int variable used to determine which operation user want to do.
    int idnumber;  // int variable used to record ID number whih user want to edit.
    int searchkey; // int variable to store student roll_no by which user can search.

    cout << "Enter The Total Number of Student(s)- Max 50: ";
    cin >> ts;

    while (ts--)
    {
        cout << "\n\t\tWhat do you want to do?" << endl;
        cout << "\t\t----------------------" << endl;
        cout << "\t\t1-Add student" << endl;
        cout << "\t\t2-Edit student" << endl;
        cout << "\t\t3-Search student" << endl;
        cout << "\t\t4-Add book" << endl;
        cout << "\t\t5-Edit book info" << endl;
        cout << "\t\t6-Search book" << endl;
        cout << "\t\t7-Issue a book" << endl;
        cout << "\t\t8-Quit Program" << endl;
        cout << "\t\t----------------------" << endl;
        cout << "Enter your choice: ";

        cin >> choice;
        switch (choice)
        {
        case 1: // If user presses 1 then student adding module would be displayed.
            add_student();
            break;
        case 2: // If there are no records in array then it will ask the user to input records first.
            if (rec[0].rollno == 0)
            {
                cout << "Please Add sudents first." << endl;
                system("pause");
                main();
            }
            else // If records are present in array then it will show table.
            {
                cout << endl;
                cout << "--------------------------------------------------------------------------------" << endl;
                cout << "---------------------------Student record Table---------------------------------" << endl;
                cout << "--------------------------------------------------------------------------------" << endl;
                cout << "ID   "
                     << "Roll   "
                     << "Name      "
                     << "Father\tCell no.      "
                     << "DOB          "
                     << "Address\n\n";
                cout << "--------------------------------------------------------------------------------" << endl;

                for (int i = 0; i <= ts; i++)
                {
                    show_data(i); // funtion is called with index value to show data.
                }

                cout << "--------------------------------------------------------------------------------" << endl;
                cout << "Which ID number your want to edit: ";

                cin >> idnumber; // Asking the user at which ID he wants to make a change.

                if (idnumber > ts || idnumber < 0) // Validating the ID number.
                {
                    cout << "\nInvalid ID Number." << endl;
                }
                else
                {
                    edit_student(idnumber); // Passing ID number to Edit Function.
                }
            }
            break;

        case 3:
            if (rec[0].rollno == 0) // If no record exist then ask the user o enter records first.
            {
                cout << "Please Add sudents first." << endl;
                system("pause");
                main(); // Return to main so user can input new record.
            }
            else
            {
                cout << "Enter roll_no of student you want to search: ";
                cin >> searchkey; // roll_no as the search key can be entered by user.
                search_student(searchkey);
            }
            break;
        case 4: // If user presses 1 then student adding module would be displayed.
            add_book();
            break;
        case 5: // If there are no records in array then it will ask the user to input records first.
            if (library[0].bookid == 0)
            {
                cout << "Please Add sudents first." << endl;
                system("pause");
                main();
            }
            else // If records are present in array then it will show table.
            {
                cout << endl;
                cout << "--------------------------------------------------------------------------------" << endl;
                cout << "---------------------------Book record Table---------------------------------" << endl;
                cout << "--------------------------------------------------------------------------------" << endl;
                cout << "ID   "
                     << "Name      "
                     << "Author\n\n";
                cout << "--------------------------------------------------------------------------------" << endl;

                for (int i = 0; i <= ts; i++)
                {
                    show_book_data(i); // funtion is called with index value to show data.
                }

                cout << "--------------------------------------------------------------------------------" << endl;
                cout << "Which ID number your want to edit: ";

                cin >> idnumber; // Asking the user at which ID he wants to make a change.

                if (idnumber > ts || idnumber < 0) // Validating the ID number.
                {
                    cout << "\nInvalid ID Number." << endl;
                }
                else
                {
                    edit_book_info(idnumber); // Passing ID number to Edit Function.
                }
            }
            break;

        case 6:
            if (library[0].bookid == 0) // If no record exist then ask the user o enter records first.
            {
                cout << "Please Add books first." << endl;
                system("pause");
                main(); // Return to main so user can input new record.
            }
            else
            {
                cout << "Enter bookid of book you want to search: ";
                cin >> searchkey; // roll_no as the search key can be entered by user.
                search_student(searchkey);
            }
            break;
        case 7:
            cout << "Enter the book id and roll no to issue the book : " << endl;
            int id;
            int roll_no;
            cin >> id >> roll_no;
            issue_book(id, roll_no);
            break;
        case 8:
            return 0; // Terminating the records.
            break;
        default: // Default value for ivalid Input.
            cout << "Invalid number." << endl;
            system("pause");
            main();
        }
    }
    return 0;
}

void get_data(int i) // Function for receiving data from user and populatiing the variables with values.
{
    cout << "Enter student roll number in  format(1XXX): ";
    cin >> rec[i].rollno;
    cout << "Enter student name: ";
    cin >> rec[i].name;
    cout << "Enter student's Father name: ";
    cin >> rec[i].fname;
    cout << "Enter student's cell phone number: ";
    cin >> rec[i].cell;
    cout << "Enter student's Date of Birth(dd/mm/yyyy): ";
    cin >> rec[i].dob;
    cout << "Enter student's Address: ";
    cin >> rec[i].address;
}

void show_data(int searchkey) // Function for showing data on the screen.
{
    int i = searchkey;
    cout << i << "    ";
    cout << rec[i].rollno << "   ";
    cout << rec[i].name << "     ";
    cout << rec[i].fname << "\t";
    cout << rec[i].cell << "   ";
    cout << rec[i].dob << "   ";
    cout << rec[i].address << "\n\n";
}

void search_student(int searchkey)
{
    for (int i = 0; i <= ts; i++) // Loop thrugh complete array.
    {
        if (rec[i].rollno == searchkey) // If roll number matches to search term.
        {
            cout << "ID   "
                 << "Roll   "
                 << "Name      "
                 << "Father\tCell no.      "
                 << "DOB          "
                 << "Address\n\n";
            show_data(i); // A function is used inside another function.
        }
    }
}

void add_student() // This function is used to add record of new student.
{
    for (int i = 0; i <= ts; i++)
    {
        get_data(i); // Loop was processed 5 times to get input for 5 students.
    }
    system("CLS");
    cout << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "---------------------------Student record Table---------------------------------" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "ID   "
         << "Roll   "
         << "Name      "
         << "Father\tCell no.      "
         << "DOB          "
         << "Address\n\n";
    cout << "--------------------------------------------------------------------------------" << endl;

    for (int i = 0; i <= ts; i++)
    {
        show_data(i); // Loop was processed for 5 times to show obtained records.
    }
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "---------------------------------FINISH-----------------------------------------" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    system("pause");

    main(); // Return to main function to again show menu.
}

void edit_student(int idnumber) // function is used to edit existing record.
{
    for (int i = 0; i <= ts; i++) // Loop is started.
    {
        if (idnumber == i) // Through loop every value is compared with search term.
        {
            cout << "\nExisted information about this record.\n\n";
            cout << "--------------------------------------------------------------------------------" << endl;
            cout << "ID   "
                 << "Roll   "
                 << "Name      "
                 << "Father\tCell no.      "
                 << "DOB          "
                 << "Address\n\n";
            cout << "--------------------------------------------------------------------------------" << endl;
            show_data(i); // Load information for existing record.
            cout << "\n\nEnter new data for above shown record.\n\n";
            get_data(i); // Inputing data for that specific record.
            cout << "\n\nRecord updated successfully." << endl;
            system("pause");
            main(); // Return to main function.
        }
    }
}

void get_book_data(int i) // Function for receiving data from user and populatiing the variables with values.
{
    cout << "Enter book id in  format(1XXX): ";
    cin >> library[i].bookid;
    cout << "Enter book name: ";
    cin >> library[i].name;
    cout << "Enter book's Author name: ";
    cin >> library[i].author;
}

void show_book_data(int searchkey) // Function for showing data on the screen.
{
    int i = searchkey;
    cout << i << "    ";
    cout << library[i].bookid << "   ";
    cout << library[i].name << "     ";
    cout << library[i].author << "\n\n";
}
void search_book(int searchkey)
{
    for (int i = 0; i <= ts; i++) // Loop thrugh complete array.
    {
        if (library[i].bookid == searchkey) // If book number matches to search term.
        {
            cout << "Sn   "
                 << "ID   "
                 << "Name      "
                 << "Author\n\n";
            show_book_data(i); // A function is used inside another function.
        }
    }
}

void add_book() // This function is used to add record of new student.
{
    for (int i = 0; i <= ts; i++)
    {
        get_book_data(i); // Loop was processed 5 times to get input for 5 students.
    }
    system("CLS");
    cout << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "---------------------------Book record Table---------------------------------" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Sn   "
         << "ID   "
         << "Name      "
         << "Author\n\n";
    cout << "--------------------------------------------------------------------------------" << endl;

    for (int i = 0; i <= ts; i++)
    {
        show_book_data(i); // Loop was processed for 5 times to show obtained records.
    }
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "---------------------------------FINISH-----------------------------------------" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    system("pause");

    main(); // Return to main function to again show menu.
}

void edit_book_info(int idnumber) // function is used to edit existing record.
{
    for (int i = 0; i <= ts; i++) // Loop is started.
    {
        if (idnumber == i) // Through loop every value is compared with search term.
        {
            cout << "\nExisted information about this record.\n\n";
            cout << "--------------------------------------------------------------------------------" << endl;
            cout << "Sn   "
                 << "ID   "
                 << "Name      "
                 << "Author\n\n";
            cout << "--------------------------------------------------------------------------------" << endl;
            show_book_data(i); // Load information for existing record.
            cout << "\n\nEnter new data for above shown record.\n\n";
            get_book_data(i); // Inputing data for that specific record.
            cout << "\n\nRecord updated successfully." << endl;
            system("pause");
            main(); // Return to main function.
        }
    }
}
void issue_book(int id, int rollno)
{
    if (library[id].issued_roll != 0)
    {
        cout << "Enter the issued date : " << endl;
        string issue_now = "";
        cin >> issue_now;
        library[id].issue_date = issue_now;
        library[id].issued_roll = rollno;
        cout << "Book issued to student " << rec[rollno].name << endl;
    }
    else
    {
        cout << "Book already issued ,can't give more"
             << "\n";
    }
}   

