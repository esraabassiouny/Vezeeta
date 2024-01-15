#include<iostream>
#include<string>
#include<fstream>
#include<conio.h>
#include <limits>
#include <sstream>
#include <set>
#include <ctime>
#define size1 100
#define size2 20
using namespace std;

int main_list();
bool login(int& index, string& user);
void after_login(string user, int user_index);

//FOR DOCTOR(
void inputdataD();
void docappointment_list(int x);
void EditDocInfo(int index);
void addappo(int x);
void editappo(int x);
void  displayappo(int x);
void removeappo(int x);
void viewP_appointment_forD(int x);
void check_docusername(string s, int x);
//)
//FOR PATIENT(
void inputdataP();
void patientappointment_list(int x);
void EditPatInfo(int index);
void patient_viewappointment(int x);
void patient_editappointment(int x);
void patient_deleteappointment(int x);
void patient_clearhistory(int x);
void check_patusername(string s, int x);
void searchfordoc(int x);
//)
set<string> specialization;
set<string>::iterator it;
string chosen_spec[37];

int patient_no = 0; //for registeration
int doctor_no = 0; //for registeration

////////doctor information///////
struct  registerD
{
    string name;
    string specialization;
    string clinic_area;
    int price;
    string username;
    string pass;
    int no_of_p = 1;
    int no_of_app = 1;
};
registerD doctor_info[size1];

////////patient information///////
struct registerP
{
    string name;
    int age;
    string area;
    string username;
    string pass;
    int p_appo_no = 1;
    int dr_index[size2];
    int dr_app_index[size2];
};
registerP patient_info[size1];

struct pat_appointments
{
    string doc_name[size2];
    string doc_specialization[size2];
    string day[size2];
    string area[size2];
    int price[size2];
    string date[size2];
    int s_hour[size2], s_min[size2];
    string s_period[size2];
    int e_hour[size2], e_min[size2];
    string e_period[size2];
    int  dr_app_no[size2];

};
pat_appointments p_appointments[size1];

struct doc_appointments
{
    string day[size2];
    string date[size2];
    int s_hour[size2], s_min[size2];
    string s_period[size2];
    int e_hour[size2], e_min[size2];
    string e_period[size2];
    int noOfPatientsPerDay[size2];
};
doc_appointments appointments[size1];

struct booked_appo
{
    string p_name[size2];
    string day[size2];
    string date[size2];

};
booked_appo booked_appointments[size1];

///////Read and Write//////
fstream write;
ifstream read;
void write_doc(int x);
void read_doc();
void write_P(int x);
void read_P();
void write_doc_appo(int x);
void read_doc_appo();
void write_p_appo(int x);
void read_p_appo();
void write_booked_appo(int x);
void read_booked_appo();
void write_specialization();
void read_specialization();

//"main function"*/
///////////////////////////////////
int main()
{
    int index = 0;
    string user;
    read_doc();
    read_P();
    read_doc_appo();
    read_p_appo();
    read_booked_appo();
    read_specialization();
    cout << endl;
    cout << " \t\t <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   WELCOME TO VEZEETA   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   \n\n";
    int choice;
    do
    {
        choice = main_list();
        if (choice == 1)
        {
            bool loginCheck;
            loginCheck = login(index, user);
            string ans;
            do
            {
                if (!loginCheck)
                {
                    cout << "\n\n\t   **************\n";
                    cout << "login error check your username and password\n";
                    cout << "\t   **************\n\n";
                    do {
                        cout << "Do you want to try again? (y/n) ";
                        cin >> ans;
                        if (ans == "y" || ans == "Y") {
                            loginCheck = login(index, user);
                        }
                        else if (ans == "n" || ans == "N") {

                            break;
                        }
                        else {
                            cout << "Invalid! Try again.. \n";
                        }
                    } while (ans != "y" && ans != "Y" && ans != "N" && ans != "n");
                }
                else
                {
                    after_login(user, index);
                    break;

                }
                if (ans == "n" || ans == "N") {
                    break;
                }
            } while (true);
        }
        else if (choice == 2)
        {
            inputdataP();
        }
        else if (choice == 3)
        {
            inputdataD();
        }
        else if (choice == 4)
        {
        }
        else if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please choose from the options given  \n" << endl;
        }
        else
        {
            cout << "Please choose from the options given  \n" << endl;
        }
    } while (choice != 4);

    write_doc(doctor_no);
    write_P(patient_no);
    write_doc_appo(doctor_no);
    write_p_appo(patient_no);
    write_booked_appo(doctor_no);
    write_specialization();
    cout << "\t\t\t\tTHANK YOU FOR VISITING US\n";
    return 0;
}

//////MAIN LIST
int main_list()
{
    int num;
    cout << endl;
    cout << " PRESS 1-> LOGIN " << endl;
    cout << " PRESS 2-> REGISTRATION AS PATIENT " << endl;
    cout << " PRESS 3-> REGISTRATION AS DOCTOR " << endl;
    cout << " PRESS 4-> EXIT " << endl;
    cout << "\n \t Choose from the options: ";
    cin >> num;
    cout << endl;
    return num;
}

//////for login
bool login(int& index, string& user)
{

    bool found = 0;
    int ch;
    string username, password;
    cout << "\n---------------------------------------------------\n";
    cout << "\t Enter your username and password \n" << endl;
    cout << "USERNAME: ";
    cin.ignore(1, '\n');
    getline(cin, username);
    cout << "PASSWORD: ";
    ch = _getch();
    while (ch != 13) {
        password.push_back(ch);
        if (ch != 8)
            cout << "*";
        ch = _getch();
    }

    for (int i = 0; i < doctor_no; i++)
    {
        if (username == doctor_info[i].username)
        {
            if (password == doctor_info[i].pass)
            {
                cout << "\n LOGGED IN SUCCESSFULLY \n" << endl;
                found = 1;
                user = "doctor";
                index = i;
            }
        }
    }
    for (int i = 0; i < patient_no; i++) {
        if (username == patient_info[i].username)
        {
            if (password == patient_info[i].pass)
            {
                cout << "\n LOGGED IN SUCCESSFULLY \n" << endl;
                user = "patient";
                found = 1;
                index = i;
            }
        }
    }
    return found;
}
void after_login(string user, int user_index)
{
    int choice2;
    if (user == "doctor")
    {
        cout << "---------------------------------------------------\n";
        cout << " 1) Appointments" << endl;
        cout << " 2) Edit Information" << endl;
        cout << " 3) Log out" << endl;
        cout << "\n\t Choose from options: ";
        cin >> choice2;
        cout << "\n---------------------------------------------------\n";
        if (choice2 == 1)
        {
            docappointment_list(user_index);
        }
        else if (choice2 == 2)
        {
            EditDocInfo(user_index);
        }
        else if (choice2 == 3)
        {

        }
        else if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please choose from the options given:  \n" << endl;
            after_login("doctor", user_index);
        }
        else
        {
            cout << "Please choose from the options given:  \n" << endl;
            after_login("doctor", user_index);
        }


        if (choice2 != 3)
            after_login("doctor", user_index);
    }
    else
    {
        cout << "\n---------------------------------------------------\n";
        cout << "1) Search for doctors" << endl;
        cout << "2) Appointments" << endl;
        cout << "3) Edit Information" << endl;
        cout << "4) Log out" << endl;
        cout << "\n\t Choose from the options: ";
        cin >> choice2;
        if (choice2 == 1)
        {
            cout << "\n---------------------------------------------------\n";
            searchfordoc(user_index);
            after_login("patient", user_index);
        }
        else if (choice2 == 2)
        {
            cout << "\n---------------------------------------------------\n";
            patientappointment_list(user_index);
        }
        else if (choice2 == 3)
        {
            cout << "\n---------------------------------------------------\n";
            EditPatInfo(user_index);
            after_login("patient", user_index);
        }
        else if (choice2 == 4)
        {
            //  main_list();
        }
        else if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please choose from the options given:  \n" << endl;
            after_login("patient", user_index);
        }
        else {
            cout << "Please choose from the options given:  \n" << endl;
            after_login("patient", user_index);
        }
    }

}

//register as a patient
void inputdataP()
{
    int ch;
    cout << "\n---------------------------------------------------\n";
    cout << "Enter your name: ";
    cin.ignore(1, '\n');
    getline(cin, patient_info[patient_no].name);
    while (true)
    {
        int i;
        for (i = 0; i < patient_info[patient_no].name.size(); i++)
        {
            int a;
            a = patient_info[patient_no].name[i];
            if (patient_info[patient_no].name[i] >= 'a' && patient_info[patient_no].name[i] <= 'z' || patient_info[patient_no].name[i] >= 'A' && patient_info[patient_no].name[i] <= 'Z' || a == 32)
            {
                continue;
            }
            else
            {
                cout << "Error! Try again..\n";
                cout << "\nEnter your name: ";
                getline(cin, patient_info[patient_no].name);
                i = -1;
            }

        }
        if (i == patient_info[patient_no].name.size())
            break;
    }
    cout << "\nEnter your age: ";
    cin >> patient_info[patient_no].age;
    while (cin.fail() || patient_info[patient_no].age < 1 || patient_info[patient_no].age >100) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error! Try again..\n";
        cout << "\nEnter your age: ";
        cin >> patient_info[patient_no].age;
    }
    int digits_no = 0;
    while (true) {
        cout << "\nEnter your area: ";
        cin.ignore(1, '\n');
        getline(cin, patient_info[patient_no].area);
        digits_no = 0;
        for (int i = 0; i < patient_info[patient_no].area.size(); i++)
        {
            if (patient_info[patient_no].area[i] >= 'a' && patient_info[patient_no].area[i] <= 'z' || patient_info[patient_no].area[i] >= 'A' && patient_info[patient_no].area[i] <= 'Z')
                continue;
            else
                digits_no++;
        }
        if (digits_no == patient_info[patient_no].area.size())
            cout << "Error! Try again..\n";
        else
            break;
    }

    cout << "\nEnter your username: ";
    cin >> patient_info[patient_no].username;
    check_patusername(patient_info[patient_no].username, patient_no);
    while (true) {
        if (patient_info[patient_no].username[0] >= 'a' && patient_info[patient_no].username[0] <= 'z' || patient_info[patient_no].username[0] >= 'A' && patient_info[patient_no].username[0] <= 'Z')
        {
            break;
        }
        else
        {
            cout << "\n\t\t** Username must start with a letter **\n\n";
            cout << "Enter your username: ";
            cin >> patient_info[patient_no].username;
            check_patusername(patient_info[patient_no].username, patient_no);
        }
    }
    int size = 0;
    cout << "\nEnter your password: ";
    ch = _getch();

    while (true)
    {
        while (ch != 13)
        {
            size++;
            patient_info[patient_no].pass.push_back(ch);
            if (ch != 8)
                cout << "*";
            ch = _getch();
        }
        if (size < 5)
        {
            patient_info[patient_no].pass.clear();
            size = 0;
            cout << "\n\n\t\t** Password must be at least five characters **\n\n";
            cout << "Enter your password: ";
            ch = _getch();
            while (ch != 13)
            {
                size++;
                patient_info[patient_no].pass.push_back(ch);
                if (ch != 8)
                    cout << "*";
                ch = _getch();
            }
        }
        else {
            break;
        }
    }

    patient_no++;
    cout << "\n---------------------------------------------------\n";
}

//register as a doctor
void inputdataD()
{
    int ch;
    cout << "\n---------------------------------------------------\n";
    cout << "Enter your name: ";
    cin.ignore(1, '\n');
    getline(cin, doctor_info[doctor_no].name);
    while (true)
    {
        int i;
        for (i = 0; i < doctor_info[doctor_no].name.size(); i++)
        {
            int a;
            a = doctor_info[doctor_no].name[i];
            if (doctor_info[doctor_no].name[i] >= 'a' && doctor_info[doctor_no].name[i] <= 'z' || doctor_info[doctor_no].name[i] >= 'A' && doctor_info[doctor_no].name[i] <= 'Z' || a == 32)
            {
                continue;
            }
            else
            {
                cout << "Error! Try again..\n\n";
                cout << "Enter your name: ";
                getline(cin, doctor_info[doctor_no].name);
                i = -1;
            }

        }
        if (i == doctor_info[doctor_no].name.size())
            break;
    }
    cout << "\nEnter your specialization: ";
    getline(cin, doctor_info[doctor_no].specialization);
    while (true)
    {
        int i = 0;
        for (i = 0; i < doctor_info[doctor_no].specialization.size(); i++)
        {
            int a;
            a = doctor_info[doctor_no].specialization[i];
            if (doctor_info[doctor_no].specialization[i] >= 'a' && doctor_info[doctor_no].specialization[i] <= 'z' || doctor_info[doctor_no].specialization[i] >= 'A' && doctor_info[doctor_no].specialization[i] <= 'Z' || a == 32)
            {
                continue;
            }
            else
            {
                cout << "Error! Try again..\n\n";
                cout << "Enter your specialization: ";
                getline(cin, doctor_info[doctor_no].specialization);
            }
        }
        if (i == doctor_info[doctor_no].specialization.size())
            break;
    }
    specialization.insert(doctor_info[doctor_no].specialization);
    int digits_no = 0;
    while (true) {
        cout << "\nEnter your clinic area: ";
        getline(cin, doctor_info[doctor_no].clinic_area);
        digits_no = 0;
        for (int i = 0; i < doctor_info[doctor_no].clinic_area.size(); i++)
        {
            if (doctor_info[doctor_no].clinic_area[i] >= 'a' && doctor_info[doctor_no].clinic_area[i] <= 'z' || doctor_info[doctor_no].clinic_area[i] >= 'A' && doctor_info[doctor_no].clinic_area[i] <= 'Z')
                continue;
            else
                digits_no++;
        }
        if (digits_no == doctor_info[doctor_no].clinic_area.size())
            cout << "Error! Try again..\n";
        else
            break;
    }


    cout << "\nEnter your price: ";
    cin >> doctor_info[doctor_no].price;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error! Try again..\n\n";
        cout << "Enter your price: ";
        cin >> doctor_info[doctor_no].price;
    }
    cout << "\nEnter your username: ";
    cin >> doctor_info[doctor_no].username;
    check_docusername(doctor_info[doctor_no].username, doctor_no);
    while (true) {
        if (doctor_info[doctor_no].username[0] >= 'a' && doctor_info[doctor_no].username[0] <= 'z' || doctor_info[doctor_no].username[0] >= 'A' && doctor_info[doctor_no].username[0] <= 'Z')
        {
            break;
        }
        else
        {
            cout << "\n\t\t** Username must start with a letter **\n\n";
            cout << "Enter your username: ";
            cin >> doctor_info[doctor_no].username;
            check_docusername(doctor_info[doctor_no].username, doctor_no);

        }
    }

    cout << "\nEnter your password: ";
    int size = 0;
    ch = _getch();

    while (true)
    {
        while (ch != 13)
        {
            size++;
            doctor_info[doctor_no].pass.push_back(ch);
            if (ch != 8)
                cout << "*";
            ch = _getch();
        }
        if (size < 5)
        {
            doctor_info[doctor_no].pass.clear();
            size = 0;
            cout << "\n\n\t\t** Password must be at least five characters **\n\n";
            cout << "Enter your password: ";
            ch = _getch();
            while (ch != 13)
            {
                size++;
                doctor_info[doctor_no].pass.push_back(ch);
                if (ch != 8)
                    cout << "*";
                ch = _getch();
            }
        }
        else {
            break;
        }
    }
    cout << "\n---------------------------------------------------\n";
    doctor_no++;

}



//////Checking if usernames exist
void check_docusername(string username, int doc_index)
{
    bool found = 0;
    for (int i = 0; i < doctor_no; i++)
    {
        if (i == doc_index)
            continue;
        else if (username == doctor_info[i].username)
        {
            found = 1;
            break;
        }

    }
    if (found)
    {
        cout << "Username already exist, try another one.\n";
        cout << "Enter another username: ";
        cin >> doctor_info[doctor_no].username;
        check_docusername(doctor_info[doctor_no].username, doctor_no);
    }

}

void check_patusername(string username, int pat_index)
{
    bool found = 0;
    for (int i = 0; i < doctor_no; i++)
    {
        if (i == pat_index)
            continue;
        else if (username == patient_info[i].username)
        {
            found = 1;
            break;
        }
    }
    if (found)
    {
        cout << "Username already exist, try another one.\n";
        cout << "Enter another username: ";
        cin >> patient_info[patient_no].username;
        check_patusername(patient_info[patient_no].username, patient_no);
    }
}



//////the following list corresponds to a doctor
void EditDocInfo(int index)
{
    int choice, price;
    string name, specialization, clinic_area, username, pass;
    cout << "1) Name\n" << "2) Specialization\n" << "3) Clinic area\n" << "4) Price\n" << "5) Username\n" << "6) Password";
    cout << "\nWhat information do you want to edit? ";
    cin >> choice;
    if (choice == 1)
    {
        cout << "Enter your name: ";
        cin.ignore(1, '\n');
        getline(cin, name);
        while (true)
        {
            int i = 0;
            for (i = 0; i < name.size(); i++)
            {
                int a;
                a = name[i];
                if (name[i] >= 'a' && name[i] <= 'z' || name[i] >= 'A' && name[i] <= 'Z' || a == 32)
                {
                    continue;
                }
                else
                {
                    cout << "Error! Try again..\n";
                    cout << "Enter your name: ";
                    getline(cin, name);
                    cout << name << " " << endl;

                }

            }
            if (i == name.size())
                break;
        }
        doctor_info[index].name = name;
        cout << "\t\t\tYour name has been changed\n";

    }
    else if (choice == 2)
    {
        cout << "Enter your specialization: ";
        cin.ignore(1, '\n');
        getline(cin, specialization);
        while (true)
        {
            int i = 0;
            for (i = 0; i < specialization.size(); i++)
            {
                int a;
                a = doctor_info[doctor_no].specialization[i];
                if (specialization[i] >= 'a' && specialization[i] <= 'z' || specialization[i] >= 'A' && specialization[i] <= 'Z' || a == 32)
                {
                    continue;
                }
                else
                {
                    cout << "Error! Try again..\n";
                    cout << "Enter your specialization: ";
                    getline(cin, specialization);
                    cout << specialization << " " << endl;

                }

            }
            if (i == specialization.size())
                break;
        }
        doctor_info[index].specialization = specialization;
        cout << "\t\t\tYour specialization has been changed\n";
    }
    else if (choice == 3)
    {
        int digits_no = 0;
        while (true)
        {
            cout << "Enter new clinic area: ";
            cin.ignore(1, '\n');
            getline(cin, clinic_area);
            digits_no = 0;
            for (int i = 0; i < clinic_area.size(); i++)
            {
                if (clinic_area[i] >= 'a' && clinic_area[i] <= 'z' || clinic_area[i] >= 'A' && clinic_area[i] <= 'Z')
                    continue;
                else
                    digits_no++;
            }
            if (digits_no == clinic_area.size())
                cout << "Error! Try again..\n";
            else
                break;
        }
        doctor_info[index].clinic_area = clinic_area;
        cout << "\t\t\tYour area has been changed\n";

    }
    else if (choice == 4)
    {
        cout << "\nEnter new price: ";
        cin >> price;
        while (cin.fail() || price <= 0 || price > 10000)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error! Try again..\n";
            cout << "Enter new price: ";
            cin >> price;
        }


        doctor_info[index].price = price;
        cout << "\t\t\tYour price has been changed\n";
    }
    else if (choice == 5)
    {
        cout << "\nEnter new username: ";
        cin.ignore(1, '\n');
        getline(cin, username);
        check_docusername(username, doctor_no);
        while (true) {
            if (username[0] >= 'a' && username[0] <= 'z' || username[0] >= 'A' && username[0] <= 'Z')
            {
                break;
            }
            else
            {
                cout << "\n\t\t** Username must start with a letter **\n\n";
                cout << "Enter new username: ";
                cin.ignore(1, '\n');
                getline(cin, username);
                check_docusername(username, doctor_no);

            }
        }

        doctor_info[index].username = username;
        cout << "\t\t\tYour username has been changed\n";

    }
    else if (choice == 6) {

        char ch, ch1;
        string oldpass;

        int size = 0;
        do {
            cout << "Enter old password: ";
            ch1 = _getch();
            while (ch1 != 13)
            {
                oldpass.push_back(ch1);
                if (ch1 != 8)
                    cout << "*";
                ch1 = _getch();

            }
            if (doctor_info[index].pass == oldpass)
            {
                cout << "\nEnter new password: ";
                ch = _getch();
                while (ch != 13)
                {
                    size++;
                    pass.push_back(ch);
                    if (ch != 8)
                        cout << "*";
                    ch = _getch();

                }
                cout << endl;
            }
            else
                cout << " \nWrong password! try again..\n";
        } while (doctor_info[index].pass != oldpass);
        while (true)
        {
            if (size < 5)
            {
                size = 0;
                cout << "\n\n\t\t** Password must be at least five characters **\n\n";
                cout << "Enter new password: \n";
                ch = _getch();
                while (ch != 13)
                {
                    size++;
                    pass.push_back(ch);
                    if (ch != 8)
                        cout << "*";
                    ch = _getch();
                }
            }
            else {
                break;
            }
        }

        doctor_info[index].pass = pass;
        cout << "\t\t\tYour passsword has been changed\n";

    }
    else if (cin.fail())
    {

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Choose from the options given: \n" << endl;
        EditDocInfo(index);
    }
    else
    {
        cout << "Choose from the options given: \n" << endl;
        EditDocInfo(index);
    }

}

void docappointment_list(int indexx)
{
    int app_choice;
    do {
        cout << endl;
        cout << "1) Add available time" << endl;
        cout << "2) Edit available time" << endl;
        cout << "3) Remove Time" << endl;
        cout << "4) View patients with appointments" << endl;
        cout << "5) To exit this menu \n";
        cout << "\n\t Choose from the options: ";
        cin >> app_choice;
        if (app_choice == 1)
        {
            addappo(indexx);

        }
        else if (app_choice == 2)
        {
            displayappo(indexx);
            editappo(indexx);
        }
        else if (app_choice == 3)
        {
            displayappo(indexx);
            removeappo(indexx);
        }
        else if (app_choice == 4)
        {
            viewP_appointment_forD(indexx);
        }
        else if (app_choice == 5)
        {
            break;
        }
        else if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nChoose from the options given: " << endl;
        }
        else
        {
            cout << "\nChoose from the options given: " << endl;
        }
    } while (true);
}

void addappo(int x)
{
    cout << "\n---------------------------------------------------\n";
    cout << "\t\tTo add available time\n\n";
    int chosen_day;
    bool check1 = 0;
    do {
        check1 = 0;
        cout << "1) Saturday\t2) Sunday\t3) Monday\t4) Tuesday\t5) Wednesday\t6) Thursday\t7) Friday\n" << "Choose the day: ";
        cin >> chosen_day;
        if (chosen_day == 1) {
            appointments[x].day[doctor_info[x].no_of_app] = "Saturday";
            break;
        }
        else if (chosen_day == 2) {
            appointments[x].day[doctor_info[x].no_of_app] = "Sunday";
            break;
        }
        else if (chosen_day == 3) {
            appointments[x].day[doctor_info[x].no_of_app] = "Monday";
            break;
        }
        else if (chosen_day == 4) {
            appointments[x].day[doctor_info[x].no_of_app] = "Tuesday";
            break;
        }
        else if (chosen_day == 5) {
            appointments[x].day[doctor_info[x].no_of_app] = "Wednesday";
            break;
        }
        else if (chosen_day == 6) {
            appointments[x].day[doctor_info[x].no_of_app] = "Thursday";
            break;
        }
        else if (chosen_day == 7) {
            appointments[x].day[doctor_info[x].no_of_app] = "Friday";
            break;
        }
        else if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Choose from the options given: \n" << endl;
            check1 = 1;
        }
        else {
            cout << "Choose from the options given: \n" << endl;
            check1 = 1;
        }
    } while (check1);
    cout << "\nEnter the date: ";
    cin >> appointments[x].date[doctor_info[x].no_of_app];
    bool letterCheck = 0;
    while (true) {
        int i = 0;
        letterCheck = 0;
        for (; i < appointments[x].date[doctor_info[x].no_of_app].size(); i++) {
            if (appointments[x].date[doctor_info[x].no_of_app][i] >= 'a' && appointments[x].date[doctor_info[x].no_of_app][i] <= 'z' || appointments[x].date[doctor_info[x].no_of_app][i] >= 'A' && appointments[x].date[doctor_info[x].no_of_app][i] <= 'Z')
            {
                letterCheck = 1;

            }
            else
            {
                continue;

            }

        }
        if (letterCheck)
        {
            cout << "Invalid! Try again \n";
            cout << "\nEnter the date: ";
            cin >> appointments[x].date[doctor_info[x].no_of_app];

        }
        else
            break;
    }
    do {
        cout << "\nEnter start time\n";
        cout << "Hour: ";
        cin >> appointments[x].s_hour[doctor_info[x].no_of_app];
        while (cin.fail() || appointments[x].s_hour[doctor_info[x].no_of_app] < 1 || appointments[x].s_hour[doctor_info[x].no_of_app]>12)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid! Try again.. \n" << endl;
            cout << "Enter start time: \n";
            cout << "Hour: ";
            cin >> appointments[x].s_hour[doctor_info[x].no_of_app];
        }
        cout << "Minutes: ";
        cin >> appointments[x].s_min[doctor_info[x].no_of_app];
        while (cin.fail() || appointments[x].s_min[doctor_info[x].no_of_app] < 0 || appointments[x].s_min[doctor_info[x].no_of_app]>59)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid! Try again.. \n" << endl;
            cout << "Minutes: ";
            cin >> appointments[x].s_min[doctor_info[x].no_of_app];
        }
        int choice;
        bool check = 0;
        do {
            check = 0;
            cout << "\n1-AM\n2-PM\n Choose period: ";
            cin >> choice;
            if (choice == 1)
                appointments[x].s_period[doctor_info[x].no_of_app] = "AM";
            else if (choice == 2)
                appointments[x].s_period[doctor_info[x].no_of_app] = "PM";

            else if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Choose from the options given: \n" << endl;
                check = 1;
            }
            else
            {
                cout << "Choose from the options given: \n" << endl;
                check = 1;
            }
        } while (check);

        cout << "\nEnter end time\n";
        cout << "Hour: ";
        cin >> appointments[x].e_hour[doctor_info[x].no_of_app];
        while (cin.fail() || appointments[x].e_hour[doctor_info[x].no_of_app] < 1 || appointments[x].e_hour[doctor_info[x].no_of_app]>12)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid! Try again.. \n" << endl;
            cout << "Enter end time: \n";
            cout << "Hour: ";
            cin >> appointments[x].e_hour[doctor_info[x].no_of_app];
        }
        cout << "Minutes: ";
        cin >> appointments[x].e_min[doctor_info[x].no_of_app];
        while (cin.fail() || appointments[x].e_min[doctor_info[x].no_of_app] < 0 || appointments[x].e_min[doctor_info[x].no_of_app]>59)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid! Try again.. \n" << endl;
            cout << "Minutes: ";
            cin >> appointments[x].e_min[doctor_info[x].no_of_app];
        }

        int choice2;
        bool check2 = 0;
        do {
            check2 = 0;
            cout << "\n1-AM\n2-PM\n Choose period: ";
            cin >> choice2;
            if (choice2 == 1)
                appointments[x].e_period[doctor_info[x].no_of_app] = "AM";
            else if (choice2 == 2)
                appointments[x].e_period[doctor_info[x].no_of_app] = "PM";

            else if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Choose from the options given: \n" << endl;
                check2 = 1;

            }
            else
            {
                cout << "Select from the options given: \n" << endl;
                check2 = 1;
            }
        } while (check2);
        if (appointments[x].s_hour[doctor_info[x].no_of_app] == appointments[x].e_hour[doctor_info[x].no_of_app] && appointments[x].s_min[doctor_info[x].no_of_app] == appointments[x].e_min[doctor_info[x].no_of_app] && appointments[x].s_period[doctor_info[x].no_of_app] == appointments[x].e_period[doctor_info[x].no_of_app])
            cout << "\t** Start time cannot be the same as end time **\n";
        else
            break;
    } while (true);
    //3shan a3rf kam patient y2dr y7gz nfs l m3ad
    if (appointments[x].e_period[doctor_info[x].no_of_app] != appointments[x].s_period[doctor_info[x].no_of_app])
    {
        if (appointments[x].s_hour[doctor_info[x].no_of_app] == 12)
            appointments[x].noOfPatientsPerDay[doctor_info[x].no_of_app] = (appointments[x].e_hour[doctor_info[x].no_of_app] + 12) - (appointments[x].s_hour[doctor_info[x].no_of_app] - 12);
        else
            appointments[x].noOfPatientsPerDay[doctor_info[x].no_of_app] = (appointments[x].e_hour[doctor_info[x].no_of_app] + 12) - appointments[x].s_hour[doctor_info[x].no_of_app];
    }
    else
    {
        if (appointments[x].s_hour[doctor_info[x].no_of_app] == 12)
            appointments[x].noOfPatientsPerDay[doctor_info[x].no_of_app] = appointments[x].e_hour[doctor_info[x].no_of_app] - (appointments[x].s_hour[doctor_info[x].no_of_app] - 12);
        else
            appointments[x].noOfPatientsPerDay[doctor_info[x].no_of_app] = appointments[x].e_hour[doctor_info[x].no_of_app] - appointments[x].s_hour[doctor_info[x].no_of_app];
    }
    doctor_info[x].no_of_app++;
}

void editappo(int x)
{
    int new_s_hour;
    int new_s_min;
    int new_e_hour;
    int new_e_min;
    string new_s_period;
    string new_e_period;
    string new_day;
    string new_date;
    string ans;
    int edit_ans;
    bool checkFdate = 0;

    if (doctor_info[x].no_of_app == 1)
    {
        cout << "\t\t\t** There is no appointment **";
    }
    else
    {
        bool check = 0;
        {
            cout << "Choose number of appointment you want to edit: ";
            do {
                cin >> edit_ans;
                check = 0;
                if (edit_ans >= 1 && edit_ans < doctor_info[x].no_of_app) {
                    break;
                }
                else if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Choose from the options given: \n" << endl;
                    check = 1;
                }
                else {
                    cout << "Choose from the options given: \n" << endl;
                    check = 1;
                }

            } while (check);


        }
        do
        {
            cout << "Do you want to change the day? (y/n) ";
            cin >> ans;

            int chosen_day;
            bool check1;
            if (ans == "y" || ans == "Y")
            {
                checkFdate = 1;
                cout << "Choose the day: \n " << "1-Saturday\t2-Sunday\t3-Monday\t4-Tuesday\t5-Wednesday\t6-Thursday\t7-Friday\n";
                cin >> chosen_day;
                if (chosen_day == 1)
                {
                    appointments[x].day[edit_ans] = "Saturday";
                    break;
                }
                else if (chosen_day == 2)
                {
                    appointments[x].day[edit_ans] = "Sunday";
                    break;
                }
                else if (chosen_day == 3)
                {
                    appointments[x].day[edit_ans] = "Monday";
                    break;
                }
                else if (chosen_day == 4)
                {
                    appointments[x].day[edit_ans] = "Tuesday";
                    break;
                }
                else if (chosen_day == 5)
                {
                    appointments[x].day[edit_ans] = "Wednesday";
                    break;
                }
                else if (chosen_day == 6)
                {
                    appointments[x].day[edit_ans] = "Thursday";
                    break;
                }
                else if (chosen_day == 7)
                {
                    appointments[x].day[edit_ans] = "Friday";
                    break;
                }
                else if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Choose from the options given: \n" << endl;
                    check1 = 1;
                }
                else
                {
                    cout << "Choose from the options given: \n" << endl;
                    check1 = 1;
                }
                while (check1);
            }
            else if (ans == "n" || ans == "N")
                break;
            else
                cout << "Invalid choice!";

        } while (true);
        if (checkFdate)
        {
            cout << "Enter the date: ";
            cin >> appointments[x].date[edit_ans];
            bool letterCheck = 0;
            while (true)
            {
                int i = 0;
                letterCheck = 0;
                for (; i < appointments[x].date[edit_ans].size(); i++)
                {
                    if (appointments[x].date[edit_ans][i] >= 'a' && appointments[x].date[edit_ans][i] <= 'z' || appointments[x].date[edit_ans][i] >= 'A' && appointments[x].date[edit_ans][i] <= 'Z')
                    {
                        letterCheck = 1;

                    }
                    else
                    {
                        continue;

                    }

                }
                if (letterCheck)
                {
                    cout << "Invalid! Try again \n";
                    cout << "Enter the date: ";
                    cin >> appointments[x].date[edit_ans];

                }
                else
                    break;
            }
        }
        do
        {
            do
            {
                cout << "Do you want to change start time? (y/n)";
                cin >> ans;
                if (ans == "y" || ans == "Y")
                {
                    cout << "Enter start time\n";
                    cout << "Hour: ";
                    cin >> new_s_hour;
                    while (cin.fail() || new_s_hour < 1 || new_s_hour>12)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\nInvalid! Try again.. \n" << endl;
                        cout << "Enter start time: \n";
                        cout << "Hour: ";
                        cin >> new_s_hour;
                    }
                    cout << "Minutes: ";
                    cin >> new_s_min;
                    while (cin.fail() || new_s_min < 0 || new_s_min>59)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\nInvalid! Try again.. \n" << endl;
                        cout << "Minutes: ";
                        cin >> new_s_min;
                    }
                    int choice;
                    bool check2 = 0;
                    do {
                        check2 = 0;
                        cout << "\n1-AM\n2-PM\n Choose period: ";
                        cin >> choice;
                        if (choice == 1)
                            appointments[x].s_period[edit_ans] = "AM";
                        else if (choice == 2)
                            appointments[x].s_period[edit_ans] = "PM";

                        else if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Choose from the options given: \n" << endl;
                            check2 = 1;

                        }
                        else
                        {
                            cout << "Choose from the options given: \n" << endl;
                            check2 = 1;
                        }
                    } while (check2);
                    appointments[x].s_hour[edit_ans] = new_s_hour;
                    appointments[x].s_min[edit_ans] = new_s_min;
                    break;
                }
                else if (ans == "n" || ans == "N")
                    break;
                else
                    cout << "Invalid choice!";
            } while (true);
            do
            {
                cout << "Do you want to change end time? (y/n)";
                cin >> ans;

                if (ans == "y" || ans == "Y")
                {
                    cout << "Enter end time\n";
                    cout << "Hour: ";
                    cin >> new_e_hour;
                    while (cin.fail() || new_e_hour < 1 || new_e_hour>12)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\nInvalid! Try again.. \n" << endl;
                        cout << "Enter end time\n";
                        cout << "Hour: ";
                        cin >> new_e_hour;
                    }
                    cout << "Minutes: ";
                    cin >> new_e_min;
                    while (cin.fail() || new_e_min < 0 || new_e_min>59)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\nInvalid! Try again.. \n" << endl;
                        cout << "Minutes: ";
                        cin >> new_e_min;
                    }
                    int choice1;
                    bool check3 = 0;
                    do
                    {
                        check3 = 0;
                        cout << "\n1-AM\n2-PM\n Choose period: ";
                        cin >> choice1;
                        if (choice1 == 1)
                            appointments[x].e_period[edit_ans] = "AM";
                        else if (choice1 == 2)
                            appointments[x].e_period[edit_ans] = "PM";

                        else if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Choose from the options given: \n" << endl;
                            check3 = 1;

                        }
                        else
                        {
                            cout << "Choose from the options given: \n" << endl;
                            check3 = 1;
                        }
                    } while (check3);
                    appointments[x].e_hour[edit_ans] = new_e_hour;
                    appointments[x].e_min[edit_ans] = new_e_min;
                    break;
                }
                else if (ans == "n" || ans == "N")
                    break;
                else
                    cout << "Invalid choice!";
            } while (true);
            if (appointments[x].s_hour[edit_ans] == appointments[x].e_hour[edit_ans] && appointments[x].s_min[edit_ans] == appointments[x].e_min[edit_ans] && appointments[x].s_period[edit_ans] == appointments[x].e_period[edit_ans])
                cout << "\t** Start time cannot be the same as end time **\n";
            else
                break;
        } while (true);

        //3shan a3rf kam patient y2dr y7gz nfs l m3ad
        if (appointments[x].e_period[edit_ans] != appointments[x].s_period[edit_ans])
        {
            if (appointments[x].s_hour[edit_ans] == 12)
                appointments[x].noOfPatientsPerDay[edit_ans] = (appointments[x].e_hour[edit_ans] + 12) - (appointments[x].s_hour[edit_ans] - 12);
            else
                appointments[x].noOfPatientsPerDay[edit_ans] = (appointments[x].e_hour[edit_ans] + 12) - appointments[x].s_hour[edit_ans];
        }
        else
        {
            if (appointments[x].s_hour[edit_ans] == 12)
                appointments[x].noOfPatientsPerDay[edit_ans] = appointments[x].e_hour[edit_ans] - (appointments[x].s_hour[edit_ans] - 12);
            else
                appointments[x].noOfPatientsPerDay[edit_ans] = appointments[x].e_hour[edit_ans] - appointments[x].s_hour[edit_ans];
        }
    }
}

void removeappo(int x)
{
    int rem_ans;
    bool check = 0;
    if (doctor_info[x].no_of_app == 1)
    {
        cout << "\t\t\t** There are no appointments **";
    }
    else
    {
        do
        {

            cout << "Enter number of appointment you want to remove: ";
            cin >> rem_ans;
            check = 0;
            if (rem_ans >= 1 && rem_ans < doctor_info[x].no_of_app)
            {
                break;
            }
            else if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Choose from the options given: \n" << endl;
                check = 1;
            }
            else
            {
                cout << "Choose from the options given: \n" << endl;
                check = 1;
            }

        } while (check);

        for (int i = rem_ans; i < doctor_info[x].no_of_app; i++) {
            appointments[x].s_hour[i] = appointments[x].s_hour[i + 1];
            appointments[x].s_min[i] = appointments[x].s_min[i + 1];
            appointments[x].s_period[i] = appointments[x].s_period[i + 1];
            appointments[x].date[i] = appointments[x].date[i + 1];
            appointments[x].day[i] = appointments[x].day[i + 1];
            appointments[x].e_hour[i] = appointments[x].e_hour[i + 1];
            appointments[x].e_min[i] = appointments[x].e_min[i + 1];
            appointments[x].e_period[i] = appointments[x].e_period[i + 1];
        }
        doctor_info[x].no_of_app--;

    }
}

void viewP_appointment_forD(int doc_index)
{
    cout << "\n---------------------------------------------------\n";
    if (doctor_info[doc_index].no_of_p == 1) {
        cout << "There are no appointments\n";
    }
    else {
        for (int i = 1; i < doctor_info[doc_index].no_of_p; i++) {
            cout << "Patient " << i << ": " << booked_appointments[doc_index].p_name[i] << endl;
            cout << "Day: " << booked_appointments[doc_index].day[i] << endl;
            cout << "Date: " << booked_appointments[doc_index].date[i] << endl;
            cout << "\n---------------------------------------------------\n";
        }
    }
}


//////the following list corresponds to a patient
void EditPatInfo(int index)
{
    int choice, age;
    string name, area, username, pass;
    cout << "1) Name\n" << "2) Age\n" << "3) Area\n" << "4) Username\n" << "5) Password\n";
    cout << "choose the information you want to edit: " << endl;
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter new name: ";
        cin.ignore(1, '\n');
        getline(cin, name);
        while (true)
        {
            int i = 0;
            for (i = 0; i < name.size(); i++)
            {
                int a;
                a = name[i];
                if (name[i] >= 'a' && name[i] <= 'z' || name[i] >= 'A' && name[i] <= 'Z' || a == 32)
                {
                    continue;
                }
                else
                {
                    cout << "Error! Try again..\n";
                    cout << "Enter your name doctor: ";
                    getline(cin, name);
                    cout << name << " " << endl;

                }

            }
            if (i == name.size())
                break;
        }
        patient_info[index].name = name;
        cout << "\t\t\tYour name has been changed\n";
    }
    else if (choice == 2)
    {

        cout << "Enter your age: ";
        cin >> age;
        while (cin.fail() || age < 1 || age >100)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error! Try again..\n";
            cout << "Enter your age: ";
            cin >> age;
        }
        patient_info[index].age = age;
        cout << "\t\t\tYour age has been changed\n";
    }

    else if (choice == 3)
    {

        int digits_no = 0;
        while (true)
        {
            cout << "Enter new area: ";
            cin.ignore(1, '\n');
            getline(cin, area);
            digits_no = 0;
            for (int i = 0; i < area.size(); i++)
            {
                if (area[i] >= 'a' && area[i] <= 'z' || area[i] >= 'A' && area[i] <= 'Z')
                    continue;
                else
                    digits_no++;
            }
            if (digits_no == area.size())
                cout << "Error! Try again..\n";
            else
                break;
        }

        patient_info[index].area = area;
        cout << "\t\t\tYour area has been changed\n";
    }
    else if (choice == 4)
    {
        cout << "Enter new username: ";
        cin.ignore(1, '\n');
        getline(cin, username);
        check_patusername(username, patient_no);
        while (true) {
            if (username[0] >= 'a' && username[0] <= 'z' || username[0] >= 'A' && username[0] <= 'Z')
            {
                break;
            }
            else
            {
                cout << "\t\t** Username must start with a letter **\n\n";
                cout << "Enter your username: ";
                cin.ignore(1, '\n');
                getline(cin, username);
                check_patusername(username, patient_no);
            }
        }
        patient_info[index].username = username;
        cout << "\t\t\tYour username has been changed\n";
    }
    else if (choice == 5)
    {
        char ch, ch1;
        string oldpass;

        int size = 0;
        do {
            cout << "Enter old password: ";
            ch1 = _getch();
            while (ch1 != 13)
            {
                oldpass.push_back(ch1);
                if (ch1 != 8)
                    cout << "*";
                ch1 = _getch();

            }
            if (patient_info[index].pass == oldpass)
            {
                cout << "\nEnter new password: ";
                ch = _getch();
                while (ch != 13)
                {
                    size++;
                    pass.push_back(ch);
                    if (ch != 8)
                        cout << "*";
                    ch = _getch();

                }
                cout << endl;
            }
            else
                cout << " Wrong password! try again.. \n";
        } while (patient_info[index].pass != oldpass);
        while (true)
        {
            if (size < 5)
            {
                size = 0;
                cout << "\n\t\t** Password must be at least five characters **\n";
                cout << "Enter new password: \n";
                ch = _getch();
                while (ch != 13)
                {
                    size++;
                    pass.push_back(ch);
                    if (ch != 8)
                        cout << "*";
                    ch = _getch();
                }
            }
            else
            {
                break;
            }
        }

        patient_info[index].pass = pass;
        cout << "\t\t\tYour password has been changed\n";
    }
    else if (cin.fail())
    {

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Choose from the options given: \n" << endl;
        EditPatInfo(index);
    }
    else
    {
        cout << "Choose from the options given: \n" << endl;
        EditPatInfo(index);
    }
}

void patientappointment_list(int user_index)
{
    bool check = 0;
    do {
        check = 0;
        int choice;
        cout << "1) View Appointments" << endl;
        cout << "2) Edit Appointments" << endl;
        cout << "3) Delete Appointments" << endl;
        cout << "4) Clear appointments history" << endl;
        cout << "5) Exit this list" << endl;
        cout << "Choose from the options: ";
        cin >> choice;
        if (choice == 1)
        {
            patient_viewappointment(user_index);
            after_login("patient", user_index);
            break;
        }
        else if (choice == 2)
        {
            patient_editappointment(user_index);
            after_login("patient", user_index);
            break;
        }
        else if (choice == 3) {
            patient_deleteappointment(user_index);
            after_login("patient", user_index);
            break;
        }
        else if (choice == 4)
        {
            patient_clearhistory(user_index);
            after_login("patient", user_index);
        }
        else if (choice == 5)
        {
            after_login("patient", user_index);
            break;
        }
        else if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Choose from the options given: \n" << endl;
            check = 1;
        }
        else {
            cout << "Choose from the options given: \n" << endl;
            check = 1;
        }
    } while (check);
}

void searchfordoc(int x)
{
    int doc_ans, doc_indexx[100], no = 1;
    int doc_index;
    bool found = 0, doc_app = 1, noApp = 1, Check = 0;
    int option;
    cout << "1) Search for doctor name" << endl;
    cout << "2) Search for specialization" << endl;
    cout << "\tChoose from the options: ";
    cin >> option;
    if (option == 1)
    {
        cout << "\nEnter doctor name: ";
        string name;
        cin.ignore(1, '\n');
        getline(cin, name);
        for (int i = 0; i < doctor_no; i++)
        {
            if (doctor_info[i].name == name)
            {
                cout << "\nName: " << doctor_info[i].name << "\t\t" << "Area: " << doctor_info[i].clinic_area << "\t\t" << "Price: " << doctor_info[i].price << "\t";
                for (int j = 1; j < doctor_info[i].no_of_app; j++)
                {
                    if (appointments[i].noOfPatientsPerDay[j] != 0)
                        Check = 1;
                }
                if (doctor_info[i].no_of_app == 1 || !Check)
                {
                    cout << "\n\nAppointments: There is no available appointment\n";
                    noApp = 0;

                }
                else
                {
                    cout << endl << "Appointments: " << endl << endl;
                    displayappo(i);
                    doc_ans = i;
                    doc_indexx[i] = i;
                    doc_index = i;
                    found = 1;
                }
            }
        }
    }
    else if (option == 2)
    {
        int i = 0, ans;

        //display specializations without repetition
        for (it = ++specialization.begin(); it != specialization.end(); it++)
        {
            cout << i + 1 << ") " << *it << endl;
            chosen_spec[i + 1] = *it;
            i++;
        }
        cout << "\nChoose from the specializations: ";
        cin >> ans;

        while (ans<1 || ans>specialization.size() - 1 || cin.fail())
        {
            i = 0;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Erorr! Choose from options given\n";
            for (it = ++specialization.begin(); it != specialization.end(); it++)
            {
                cout << i + 1 << ") " << *it << endl;
                chosen_spec[i + 1] = *it;
                i++;
            }
            cin >> ans;
        }
        for (int i = 0; i < doctor_no; i++)
        {
            if (doctor_info[i].specialization == chosen_spec[ans] && doctor_info[i].clinic_area == patient_info[x].area)
            {
                cout << no << ") " << "Name: " << doctor_info[i].name << "\t" << "Area: " << doctor_info[i].clinic_area << "\t" << "Price: " << doctor_info[i].price << "\n";
                found = 1;
                doc_index = i;
                doc_indexx[no] = i;
                no++;

            }
        }
        for (int i = 0; i < doctor_no; i++)
        {
            if (doctor_info[i].specialization == chosen_spec[ans] && doctor_info[i].clinic_area != patient_info[x].area)
            {
                cout << no << ") " << "Name: " << doctor_info[i].name << "\t" << "Area: " << doctor_info[i].clinic_area << "\t" << "Price: " << doctor_info[i].price << "\n";
                found = 1;
                doc_index = i;
                doc_indexx[no] = i;
                no++;
            }
        }
        cout << "Choose doctor: ";
        cin >> doc_ans;
        while (doc_ans < 1 || doc_ans >= no || cin.fail())
        {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Choose from options given: \n";
            cin >> doc_ans;
        }
        cout << "\n";
        if (doctor_info[doc_indexx[doc_ans]].no_of_app > 1)
        {
            cout << "Appointments: " << endl;
            displayappo(doc_indexx[doc_ans]);
        }
        else
        {
            cout << "There are no appointments\n";
            doc_app = 0;
        }

    }
    else if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Choose from the options given: \n" << endl;
        searchfordoc(x);

    }
    else
    {
        cout << "Choose from the options given: \n";
        searchfordoc(x);
    }
    if (noApp)
    {
        if (found && doc_app)
        {
            int index;
            cout << "Choose an appointment: ";
            cin >> index;
            cout << "\n---------------------------------------------------\n";
            cout << appointments[doc_indexx[doc_ans]].day[index] << endl;
            cout << appointments[doc_indexx[doc_ans]].date[index] << endl;
            cout << "from " << appointments[doc_indexx[doc_ans]].s_hour[index] << ':' << appointments[doc_indexx[doc_ans]].s_min[index] << appointments[doc_indexx[doc_ans]].s_period[index] << " to "
                << appointments[doc_indexx[doc_ans]].e_hour[index] << ':' << appointments[doc_indexx[doc_ans]].e_min[index] << appointments[doc_indexx[doc_ans]].e_period[index] << endl << endl;
            cout << "   The appointment has been successfully booked";
            //saving appointment for patient
            p_appointments[x].doc_name[patient_info[x].p_appo_no] = doctor_info[doc_indexx[doc_ans]].name;
            p_appointments[x].doc_specialization[patient_info[x].p_appo_no] = doctor_info[doc_indexx[doc_ans]].specialization;
            p_appointments[x].area[patient_info[x].p_appo_no] = doctor_info[doc_indexx[doc_ans]].clinic_area;
            p_appointments[x].price[patient_info[x].p_appo_no] = doctor_info[doc_indexx[doc_ans]].price;
            p_appointments[x].date[patient_info[x].p_appo_no] = appointments[doc_indexx[doc_ans]].date[index];
            p_appointments[x].day[patient_info[x].p_appo_no] = appointments[doc_indexx[doc_ans]].day[index];
            p_appointments[x].s_hour[patient_info[x].p_appo_no] = appointments[doc_indexx[doc_ans]].s_hour[index];
            p_appointments[x].s_min[patient_info[x].p_appo_no] = appointments[doc_indexx[doc_ans]].s_min[index];
            p_appointments[x].s_period[patient_info[x].p_appo_no] = appointments[doc_indexx[doc_ans]].s_period[index];
            p_appointments[x].e_hour[patient_info[x].p_appo_no] = appointments[doc_indexx[doc_ans]].e_hour[index];
            p_appointments[x].e_min[patient_info[x].p_appo_no] = appointments[doc_indexx[doc_ans]].e_min[index];
            p_appointments[x].e_period[patient_info[x].p_appo_no] = appointments[doc_indexx[doc_ans]].e_period[index];
            patient_info[x].dr_index[patient_info[x].p_appo_no] = doc_indexx[doc_ans];
            patient_info[x].dr_app_index[patient_info[x].p_appo_no] = index;
            p_appointments[x].dr_app_no[patient_info[x].p_appo_no] = doctor_info[doc_indexx[doc_ans]].no_of_p;
            patient_info[x].p_appo_no++;
            //saving appointment for doctor
            booked_appointments[doc_indexx[doc_ans]].p_name[doctor_info[doc_indexx[doc_ans]].no_of_p] = patient_info[x].name;
            booked_appointments[doc_indexx[doc_ans]].day[doctor_info[doc_indexx[doc_ans]].no_of_p] = appointments[doc_indexx[doc_ans]].day[index];
            booked_appointments[doc_indexx[doc_ans]].date[doctor_info[doc_indexx[doc_ans]].no_of_p] = appointments[doc_indexx[doc_ans]].date[index];
            appointments[doc_indexx[doc_ans]].noOfPatientsPerDay[index]--;
            doctor_info[doc_indexx[doc_ans]].no_of_p++;
        }

        else if (!found)
        {
            cout << "Not found\n";
        }
    }
}

void displayappo(int x)
{
    for (int j = 1; j < doctor_info[x].no_of_app; j++)
    {
        if (appointments[x].noOfPatientsPerDay[j] == 0)
            continue;
        else {
            cout << j << "-" << appointments[x].day[j] << endl;
            cout << appointments[x].date[j] << endl;
            cout << "from " << appointments[x].s_hour[j] << ':' << appointments[x].s_min[j] << appointments[x].s_period[j] << " to "
                << appointments[x].e_hour[j] << ':' << appointments[x].e_min[j] << appointments[x].e_period[j];
            cout << "\n---------------------------------------------------\n";
        }
    }
}

void patient_viewappointment(int x) {
    cout << "\n---------------------------------------------------\n";
    if (patient_info[x].p_appo_no == 1) {
        cout << "There are no appointments" << endl;
        cout << "\n---------------------------------------------------\n";
    }
    else {

        for (int i = 1; i < patient_info[x].p_appo_no; i++) {
            cout << "\nAppointment " << i << endl;
            cout << "Doctor name: " << p_appointments[x].doc_name[i] << endl;
            cout << "Doctor specialization: " << p_appointments[x].doc_specialization[i] << endl;
            cout << "Doctor area: " << p_appointments[x].area[i] << endl;
            cout << "price: " << p_appointments[x].price[i] << endl;
            cout << "Day: " << p_appointments[x].day[i] << endl;
            cout << "Date: " << p_appointments[x].date[i] << endl;
            cout << "Time from: ";
            cout << p_appointments[x].s_hour[i] << ':' << p_appointments[x].s_min[i] << p_appointments[x].s_period[i];
            cout << " to ";
            cout << p_appointments[x].e_hour[i] << ':' << p_appointments[x].e_min[i] << p_appointments[x].e_period[i] << endl;
        }
    }
}

void patient_editappointment(int x)//patient id
{
    int doc_index;
    int edit_app;//appointment
    int new_app;
    bool check = 0;
    patient_viewappointment(x);//
    if (patient_info[x].p_appo_no == 1)
    {
        patientappointment_list(x);
    }
    else {
        cout << "\n---------------------------------------------------\n";
        cout << "Choose appointment you want to edit: ";
        do {
            cin >> edit_app;
            check = 0;
            if (edit_app >= 1 && edit_app < patient_info[x].p_appo_no) {
                break;
            }
            else if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Choose from the options given: \n" << endl;
                check = 1;
            }
            else {
                cout << "Choose from the options given: \n" << endl;
                check = 1;
            }

        } while (check);
        cout << endl;
        for (int i = 0; i < doctor_no; i++)
        {
            if (doctor_info[i].name == p_appointments[x].doc_name[edit_app])
            {
                displayappo(i);
                doc_index = i;
            }
        }
        cout << "Choose a new appointment: ";
        do {
            cin >> new_app;
            check = 0;
            if (new_app >= 1 && new_app < doctor_info[doc_index].no_of_app) {
                break;
            }
            else if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Choose from the options given: \n" << endl;
                check = 1;
            }
            else {
                cout << "Choose from the options given: \n" << endl;
                check = 1;
            }

        } while (check);
        p_appointments[x].day[edit_app] = appointments[doc_index].day[new_app];
        p_appointments[x].date[edit_app] = appointments[doc_index].date[new_app];
        p_appointments[x].s_hour[edit_app] = appointments[doc_index].s_hour[new_app];
        p_appointments[x].s_min[edit_app] = appointments[doc_index].s_min[new_app];
        p_appointments[x].s_period[edit_app] = appointments[doc_index].s_period[new_app];
        p_appointments[x].e_hour[edit_app] = appointments[doc_index].e_hour[new_app];
        p_appointments[x].e_min[edit_app] = appointments[doc_index].e_min[new_app];
        p_appointments[x].e_period[edit_app] = appointments[doc_index].e_period[new_app];
        //edit appointment for doctor
        booked_appointments[doc_index].day[p_appointments[x].dr_app_no[edit_app]] = appointments[doc_index].day[new_app];
        booked_appointments[doc_index].date[p_appointments[x].dr_app_no[edit_app]] = appointments[doc_index].date[new_app];
    }
    cout << "\n\t\tTHE APPOINTMENT HAS BEEN SUCCESSFULLY CHANGED\n";
}

void patient_deleteappointment(int x)

{
    bool check = 0;
    cout << "\n---------------------------------------------------\n";

    if (patient_info[x].p_appo_no == 1) {
        cout << " \t There are no appointments" << endl;
        cout << "\n---------------------------------------------------\n";

        patientappointment_list(x);
    }
    else {
        patient_viewappointment(x);
        int remove_ans;
        cout << " \t Enter number of appointment you want to remove: ";
        cin >> remove_ans;
        do {
            cin >> remove_ans;
            check = 0;
            if (remove_ans >= 1 && remove_ans < patient_info[x].p_appo_no) {
                break;
            }
            else if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Choose from the options given: \n" << endl;
                check = 1;
            }
            else {
                cout << "Choose from the options given: \n" << endl;
                check = 1;
            }

        } while (check);
        for (int i = remove_ans; i <= patient_info[x].p_appo_no; i++) {
            p_appointments[x].doc_name[i] = p_appointments[x].doc_name[i + 1];
            p_appointments[x].doc_specialization[i] = p_appointments[x].doc_specialization[i + 1];
            p_appointments[x].area[i] = p_appointments[x].area[i + 1];
            p_appointments[x].price[i] = p_appointments[x].price[i + 1];
            p_appointments[x].date[i] = p_appointments[x].date[i + 1];
            p_appointments[x].day[i] = p_appointments[x].day[i + 1];
            p_appointments[x].s_hour[i] = p_appointments[x].s_hour[i + 1];
            p_appointments[x].s_min[i] = p_appointments[x].s_min[i + 1];
            p_appointments[x].s_period[i] = p_appointments[x].s_period[i + 1];
            p_appointments[x].e_hour[i] = p_appointments[x].e_hour[i + 1];
            p_appointments[x].e_min[i] = p_appointments[x].e_min[i + 1];
            p_appointments[x].e_period[i] = p_appointments[x].e_period[i + 1];
        }
        patient_info[x].p_appo_no--;
        for (int i = patient_info[x].dr_app_index[patient_info[x].p_appo_no]; i <= doctor_info[patient_info[x].dr_index[patient_info[x].p_appo_no]].no_of_p; i++) {
            booked_appointments[patient_info[x].dr_index[patient_info[x].p_appo_no]].day[i] = booked_appointments[patient_info[x].dr_index[patient_info[x].p_appo_no]].day[i + 1];
            booked_appointments[patient_info[x].dr_index[patient_info[x].p_appo_no]].date[i] = booked_appointments[patient_info[x].dr_index[patient_info[x].p_appo_no]].date[i + 1];
            booked_appointments[patient_info[x].dr_index[patient_info[x].p_appo_no]].p_name[i] = booked_appointments[patient_info[x].dr_index[patient_info[x].p_appo_no]].p_name[i + 1];
        }
        cout << "\n---------------------------------------------------\n";
        doctor_info[patient_info[x].dr_index[patient_info[x].p_appo_no]].no_of_p--;
        appointments[patient_info[x].dr_index[patient_info[x].p_appo_no]].noOfPatientsPerDay[patient_info[x].dr_app_index[patient_info[x].p_appo_no]]++;
    }
    cout << "\n\t\tTHE APPOINTMENT HAS BEEN SUCCESSFULLY CANCELED\n";
}

void patient_clearhistory(int x)
{
    int calendar[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int month[20], day[20], l = 0;
    int current_month, current_day;
    ////seconds in a day = 86400
    ////from 1/1/1970 to 1/1/2023 = 19357
    time_t current_time = time(nullptr);
    current_time /= 86400;
    current_time -= 19357;
    while (current_time > 31)
    {
        current_time -= calendar[l];
        l++;
    }
    current_month = l + 1;
    current_day = current_time;
    istringstream iss[20];
    int m = 1;
    for (int i = 1; i < patient_info[x].p_appo_no; i++)
    {
        iss[m].str(p_appointments[x].date[i]);
        iss[m] >> day[m];
        iss[m].ignore(10, '/');
        iss[m] >> month[m];
        int remove;
        if (current_month > month[m])
        {
            remove = i;
            for (int j = remove; j < patient_info[x].p_appo_no; j++)
            {
                p_appointments[x].doc_name[j] = p_appointments[x].doc_name[j + 1];
                p_appointments[x].doc_specialization[j] = p_appointments[x].doc_specialization[j + 1];
                p_appointments[x].area[j] = p_appointments[x].area[j + 1];
                p_appointments[x].price[j] = p_appointments[x].price[j + 1];
                p_appointments[x].date[j] = p_appointments[x].date[j + 1];
                p_appointments[x].day[j] = p_appointments[x].day[j + 1];
                p_appointments[x].s_hour[j] = p_appointments[x].s_hour[j + 1];
                p_appointments[x].s_min[j] = p_appointments[x].s_min[j + 1];
                p_appointments[x].s_period[j] = p_appointments[x].s_period[j + 1];
                p_appointments[x].e_hour[j] = p_appointments[x].e_hour[j + 1];
                p_appointments[x].e_min[j] = p_appointments[x].e_min[j + 1];
                p_appointments[x].e_period[j] = p_appointments[x].e_period[j + 1];
            }
            patient_info[x].p_appo_no--;
            i--;
        }
        else if (current_month == month[i] && current_day > day[i])
        {
            remove = i;
            for (int j = remove; j < patient_info[x].p_appo_no; j++)
            {
                p_appointments[x].doc_name[j] = p_appointments[x].doc_name[j + 1];
                p_appointments[x].doc_specialization[j] = p_appointments[x].doc_specialization[j + 1];
                p_appointments[x].area[j] = p_appointments[x].area[j + 1];
                p_appointments[x].price[j] = p_appointments[x].price[j + 1];
                p_appointments[x].date[j] = p_appointments[x].date[j + 1];
                p_appointments[x].day[j] = p_appointments[x].day[j + 1];
                p_appointments[x].s_hour[j] = p_appointments[x].s_hour[j + 1];
                p_appointments[x].s_min[j] = p_appointments[x].s_min[j + 1];
                p_appointments[x].s_period[j] = p_appointments[x].s_period[j + 1];
                p_appointments[x].e_hour[j] = p_appointments[x].e_hour[j + 1];
                p_appointments[x].e_min[j] = p_appointments[x].e_min[j + 1];
                p_appointments[x].e_period[j] = p_appointments[x].e_period[j + 1];
            }
            patient_info[x].p_appo_no--;
            i--;
        }
        m++;
    }
    cout << "\n\t\tYOUR HISTORY HAS BEEN SUCCESSFULLY CLEARED\n";
}

////////READ & WRITE FUNCTIONS
void write_doc(int x)
{
    write.open("Register as Doc.txt", ios::out);
    for (int i = 0; i < x; i++)
    {
        write << doctor_info[i].name << ',' << doctor_info[i].clinic_area << ',' << doctor_info[i].specialization << endl <<
            doctor_info[i].price << endl << doctor_info[i].username << endl << doctor_info[i].pass << endl <<
            doctor_info[i].no_of_p << endl << doctor_info[i].no_of_app << endl << doctor_no;
    }
    write.close();
}

void read_doc()
{
    read.open("Register as Doc.txt");
    int i = 1;
    for (int x = 0; x < i; x++)
    {
        getline(read, doctor_info[x].name, ','); getline(read, doctor_info[x].clinic_area, ',');
        read >> doctor_info[x].specialization >> doctor_info[x].price >> doctor_info[x].username >> doctor_info[x].pass >>
            doctor_info[x].no_of_p >> doctor_info[x].no_of_app >> doctor_no;
        i = doctor_no;
    }
    read.close();
}

void write_P(int x)
{
    write.open("Register as Patien.txt", ios::out);
    for (int i = 0; i < x; i++)
    {
        write << patient_info[i].name << ',' << patient_info[i].area << ',' << patient_info[i].age << endl <<
            patient_info[i].username << endl << patient_info[i].pass << endl << x << endl << patient_info[i].p_appo_no << endl;
        for (int j = 1; j < patient_info[i].p_appo_no; j++)
        {
            write << patient_info[i].dr_index[j] << endl << patient_info[i].dr_app_index[j] << endl;
        }
    }
    write.close();
}

void read_P()
{
    read.open("Register as Patien.txt");
    int x = 1;
    for (int i = 0; i < x; i++)
    {
        getline(read, patient_info[i].name, ','); getline(read, patient_info[i].area, ','); read >> patient_info[i].age >>
            patient_info[i].username >> patient_info[i].pass >> patient_no >> patient_info[i].p_appo_no;
        for (int j = 1; j < patient_info[i].p_appo_no; j++)
        {
            read >> patient_info[i].dr_index[j] >> patient_info[i].dr_app_index[j];
        }
        x = patient_no;
    }
    read.close();
}

void write_doc_appo(int x)
{
    write.open("Appo.txt", ios::out);
    for (int z = 0; z < doctor_no; z++)
    {
        for (int i = 1; i < doctor_info[z].no_of_app; i++)
        {
            write << appointments[z].day[i] << endl << appointments[z].date[i] << endl <<
                appointments[z].s_hour[i] << endl << appointments[z].s_min[i] << endl << appointments[z].s_period[i] << endl <<
                appointments[z].e_hour[i] << endl << appointments[z].e_min[i] << endl << appointments[z].e_period[i] << endl << appointments[z].noOfPatientsPerDay[i] << endl;
        }
    }
    write.close();
}

void read_doc_appo()
{
    read.open("Appo.txt");
    for (int z = 0; z < doctor_no; z++)
    {
        for (int i = 1; i < doctor_info[z].no_of_app; i++)
        {
            read >> appointments[z].day[i] >> appointments[z].date[i] >>
                appointments[z].s_hour[i] >> appointments[z].s_min[i] >> appointments[z].s_period[i] >>
                appointments[z].e_hour[i] >> appointments[z].e_min[i] >> appointments[z].e_period[i] >> appointments[z].noOfPatientsPerDay[i];
        }
    }
    read.close();
}

void write_p_appo(int x)
{
    write.open("pat_appo.txt", ios::out);
    for (int z = 0; z < x; z++)
    {
        for (int i = 1; i < patient_info[z].p_appo_no; i++)
        {
            write << p_appointments[z].doc_name[i] << ',' << p_appointments[z].area[i] << ',' << p_appointments[z].doc_specialization[i] << endl << p_appointments[z].day[i] << endl
                << p_appointments[z].price[i] << endl << p_appointments[z].date[i] << endl << p_appointments[z].s_hour[i] << endl
                << p_appointments[z].s_min[i] << endl << p_appointments[z].s_period[i] << endl << p_appointments[z].e_hour[i] << endl
                << p_appointments[z].e_min[i] << endl << p_appointments[z].e_period[i] << endl << p_appointments[z].dr_app_no[i];
        }
    }
    write.close();
}

void read_p_appo()
{
    read.open("pat_appo.txt");
    for (int z = 0; z < patient_no; z++)
    {
        for (int i = 1; i < patient_info[z].p_appo_no; i++)
        {
            getline(read, p_appointments[z].doc_name[i], ','); getline(read, p_appointments[z].area[i], ',');
            read >> p_appointments[z].doc_specialization[i] >> p_appointments[z].day[i]
                >> p_appointments[z].price[i] >> p_appointments[z].date[i] >> p_appointments[z].s_hour[i] >>
                p_appointments[z].s_min[i] >> p_appointments[z].s_period[i] >> p_appointments[z].e_hour[i] >>
                p_appointments[z].e_min[i] >> p_appointments[z].e_period[i] >> p_appointments[z].dr_app_no[i];
        }
    }
    read.close();
}

void write_booked_appo(int x)
{
    write.open("booked appo for doc.txt", ios::out);
    for (int z = 0; z < x; z++)
    {
        for (int i = 1; i < doctor_info[z].no_of_p; i++)
        {
            write << booked_appointments[z].p_name[i] << ',' << booked_appointments[z].day[i]
                << endl << booked_appointments[z].date[i] << endl;
        }
    }
    write.close();
}

void read_booked_appo()
{
    read.open("booked appo for doc.txt");
    for (int z = 0; z < doctor_no; z++)
    {

        for (int i = 1; i < doctor_info[z].no_of_p; i++)
        {
            getline(read, booked_appointments[z].p_name[i], ','); read >> booked_appointments[z].day[i]
                >> booked_appointments[z].date[i];
        }
    }
    read.close();
}

void write_specialization()
{
    write.open("Chosen specialization.txt", ios::out);
    for (it = specialization.begin(); it != specialization.end(); it++)
    {
        write << *it << endl;
    }
    write.close();
}

void read_specialization()
{
    read.open("Chosen specialization.txt");
    for (int i = 0; i < 37; i++)
    {
        read >> chosen_spec[i];
        specialization.insert(chosen_spec[i]);
    }
    read.close();
}