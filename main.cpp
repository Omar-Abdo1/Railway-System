#include <bits/stdc++.h>
using namespace std;
#include "User.h"
#include "Customer.h"

void InterFace1()
{


    while(true)
    {

        FillData();

        cout<<"\n___________________________________________________________________________________" << endl;
        cout << "____________________________WELCOME TO Omar RAILWAYS______________________________" << endl;
        cout << "\t\t|\t 1. Admin Mode    \t|" << endl;
        cout << "\t\t|\t 2. User Mode     \t|" << endl;
        cout << "\t\t|\t 3. Exit          \t|" << endl;

        cout<<"Enter the Choice : ";
        int Choice;

        try
        {
           string s;
            cin>>s;

            if(s=="1" or s=="2" or s=="3")
            Choice = stoi(s);
            else
                throw 1;
        }
        catch(...)
        {
            cout<<"\t\tInvalid Input Please Enter A number Between 1-3\n\n";
            continue;
        }

        if(Choice==1)
        {

            cout << "____________________________________________________________" << endl;
            cout << endl
                 << "Enter Admin Username: ";
            string email,pass;
            cin>>email;
            cout<<"Enter Admin PassWord: ";
            cin>>pass;
            if(email!="admin" or pass!="admin")
            {
                cout<<"Invalid Email or Password\n";
            }
            else
            {

                cout << "\n_______________________________________________________________________________" << endl;
                cout << "WELCOME TO ADMIN MODE" << endl;
            cout << "\t1. View Customers DataBase" << endl;
            cout << "\t2. View Food DataBase" << endl;
            cout << "\t3. Back " << endl;
            cout << "\n\tSelect: ";
                string num;
                cin>>num;

                if(num=="1")
                {
                     Admin.ShowCustomers();
                }
                else if(num=="2")
                {
                        Admin.ShowFood();
                }
                else if(num=="3"){

                }
                else
                {
                    cout<<"Invalid Input Back to Main Menu..\n";
                }
            }
        }
        else if(Choice==2)
        {

Repeat :
            cout << "\n_______________________________________________________________________________" << endl;
            cout << "WELCOME TO USER MODE" << endl;
            cout << "\t1. Create New Account" << endl;
            cout << "\t2. Login using existing account" << endl;
            cout << "\t3. Back " << endl;
            cout << "\n\tSelect: ";
             int Choice;
            try
            {
              string s;
            cin>>s;

            if(s=="1" or s=="2" or s=="3")
            Choice = stoi(s);
            else
                throw 1;
            }
            catch(...)
            {
                cout<<"\t\t Invalid Number Please Enter A number Between 1-3\n\n";
                goto Repeat;
            }

            if(Choice==1)
            {
                string uid, upass;

                cout << "__________________________________________________________________________________" << endl;
                cout << "______________________________CREATING NEW ACCOUNT_________________________________" << endl;

Reapet :

                cout << "\nEnter the New Email : ";
                cin >> uid;
                cout << "\nEnter Password: ";
                cin >> upass;
                User obj(uid,upass);
                try
                {
                    obj.MakeEmail();
                }
                catch(const char *msg)
                {
                    cout<<msg<<"\n";
                    goto Reapet;
                }

                cout << "New User Email created!\n\n";
                cout << "Your User Email is " << uid << " and password is " << upass << endl;
                cout << "Use this as Login Credentials!" << endl
                     << endl;

                InterFace2(obj);
                Admin.Add(obj);
            }
            else if(Choice==2)
            {

                cout << "__________________________________________________________________________________" << endl;
                cout << "__________________________________LOGING IN_______________________________________" << endl;

                string uid, upass;

Reapet1 :

                cout << "\nEnter Email: ";
                cin >> uid;

Reapet2 :

                cout << "\nEnter Password: ";
                cin >> upass;


                try
                {
                    User::IsThere(uid,upass);
                }
                catch(int num)
                {

                    if(num==1)
                    {
                        cout<<"\t\t Email Does not Exist \n\n";
                        goto Reapet1;
                    }
                    else
                    {
                        cout<<"\t\t Password Seems To Be wrong \n\n";
                        goto Reapet2;
                    }
                }

                User obj = LOGING[ {uid,upass}];

                InterFace2(obj);
                Admin.Add(obj);
            }
            else
            {
                continue;
            }
        }
        else
        {
            cout<<"\t\t Thanks For Using Our Railway System\n\n";
            return;
        }
    }
}



int main()
{


    InterFace1();








    return 0;
}
