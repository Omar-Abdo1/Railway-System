#include<iostream>
using namespace std;
#ifndef USER_H
#define USER_H




#include "Customer.h"


class User
{
public :
    string Email,file;
    int counter=0;

    User()
    {
    }

     bool operator<(const User&user )const{
    }

    User(string email,string pass)
    {
        this->Email = email;
        this->Pass = pass;
        this->file = Email;
    }

    void MakeEmail()
    {

        if(IsEmailExist(this->Email).size())
        {
            throw "\t\tEmail Is Already Exist Please Make A Different One\n";
        }

        ofstream os;
        os.open("UsersData.txt",ofstream::app);
        os<<this->Email<<" "<<this->Pass<<"\n";
        os.close();
        Hello1(this->Email);
    }

    static void IsThere(string &email,string &pass)
    {

        string here = IsEmailExist(email);
        if(here.empty())
        {
            throw 1;
        }
        else if(pass!=here)
        {
            throw 2;
        }
        else
        {
            Hello2(email);
        }
    }

    static void Hello1(string &S)
    {
        cout<<"\t\t Welcome "<<S<<" Your Register is successfully Done \n\n";
    }

    static void Hello2(string &S)
    {
        cout<<"\t\t Welcome "<<S<<" You successfully Entered \n\n";
    }

    void Add(Ticket &oth)
    {
        counter++;
        mp[oth.PNR] = oth;
    }

    bool IsPNR_Exist(int num)
    {
        if(mp.find(num)==mp.end())
            return 0;
        return 1;
    }

    void Delete(int num)
    {
        if(!IsPNR_Exist(num))return;
        mp.erase(num);
        counter--;
        RemoveFromFile("PNRs.txt",to_string(num));
        string f ="./Tickets/"+file+"_"+to_string(num)+"C.txt";
        int temp = remove(f.c_str());
        assert(temp==0);
        f ="./Tickets/"+file+"_"+to_string(num)+"F.txt";
        temp = remove(f.c_str());
        assert(temp==0);
    }

    Ticket *GetBY_PNR(int num)
    {
        return &mp[num];
    }

    void RemoveFromFile(string file,string s)
    {

        ifstream myfile2; //for reading records
        myfile2.open("PNRs.txt");

        ofstream temp;
        temp.open("temp.txt",ios::app);
        string line;
        while (getline(myfile2, line))
        {
            if (line != s)
                temp << line << endl;
        }
        myfile2.close();
        temp.close();
        remove("PNRs.txt");
        rename("temp.txt", "PNRs.txt");
    }
    map<int,Ticket>mp;

    string Pass;

private :
    static string IsEmailExist(string &me)
    {

        string Exist = "";

        ifstream os;
        os.open("UsersData.txt");
        string s,t;
        while(os>>s>>t)
        {
            if(s==me)
                Exist = t;
        }
        os.close();
        return Exist;
    }

};

map<pair<string,string>,User>LOGING;


class Control
{

public :

    Control()
    {
    }

    void ShowCustomers()
    {
        DataBase1();
    }


    void ShowFood()
    {
        DataBase2();
    }

    void Add(User &user)
    {
        all.push_back(user);
    }

private :

    vector<User>all;

    void DataBase1()
    {

         if(all.empty()){
            cout<<"There Is No Users Yet\n\n";
            return;
         }

        cout<<"\n___________________________________________________________________________________" << endl;
        cout << "____________________________Customers DataBase______________________________" << endl;
        cout<<endl;

         for(int i=0;i<all.size();++i){
            User user = all[i];

                 cout<<"USER : "<<user.Email<<"\t PASSWORD : "<<user.Pass<<"  :\n\n";

                for(auto &[pnr,tk] : user.mp){

                 for(int i=1;i<tk.C.size();++i){
                   cout<<tk.C[i]<<"\n";
                 }
              }
            cout<<"\n___________________________________________________________________________________" << endl;
         }

    }

    void DataBase2()
    {
       if(all.empty()){
            cout<<"There Is No Users Yet\n\n";
            return;
         }

        cout<<"\n___________________________________________________________________________________" << endl;
        cout << "____________________________FOOD DataBase______________________________" << endl;
        cout<<endl;

           for(int i=0;i<all.size();++i){
            User user = all[i];

                 cout<<"USER : "<<user.Email<<"\t PASSWORD : "<<user.Pass<<"  :\n\n";

                for(auto &[pnr,tk] : user.mp){

                  for(int i=1;i<tk.F.size();++i){

                     int j = 0;
                     while( isalpha(tk.F[i][j])==0)++j;

                      for(;j<tk.F[i].size();++j)
                        cout<<tk.F[i][j];
                      cout<<"\t PNR :"<<pnr;
                   cout<<endl;
                  }

              }
            cout<<"\n___________________________________________________________________________________" << endl;
         }

    }

} Admin;



void ReturnCustomers(string &file,Ticket &tk)
{

    ifstream os;
    os.open(file);

    string s;
    while(getline(os,s))
    {
        tk.C.push_back(s);
    }
    s = tk.C[0];

    string d;
    int sum=0;
    for(int i=0; i<s.size(); ++i)
    {

        if(s[i]=='i' && s[i+1]=='s' && isalnum(s[i+3]))
        {
            int j = i+3;
            while(isalpha(s[j]))
            {
                d.push_back(s[j]);
                ++j;
            }
            i = j;
        }

        if(s[i]=='=')
        {
            int j=i+2;
            while(isdigit(s[j]))
            {
                sum = sum*10 + s[j]-'0';
                ++j;
            }
            i =j;
        }
    }

    tk.BCost = sum;
    tk.Destination = d;
    os.close();
}

void ReturnFood(string &file,Ticket &tk)
{

    ifstream os;
    os.open(file);

    string s;
    while(getline(os,s))
    {

        tk.F.push_back(s);

        for(int i=0; i<s.size(); ++i)
        {

            if(s[i]=='-')
            {
                int j = i+2;
                string t="";
                while(j<s.size() && (isalpha(s[j]) || s[j]=='_' || s[j]=='3') )
                {
                    t.push_back(s[j]);
                    ++j;
                }
                i = j;
                int idx = -1;
                for(int k=0; k<9; ++k)
                {
                    if(Food[k]==t)
                    {
                        idx = k;
                        break;
                    }
                }
                assert(idx!=-1);
                tk.AddFood(idx,1);
            }
        }

    }

    os.close();
}


void FillData()
{

    for(int i=0; i<9; ++i)
    {
        mp_FoodCost[Food[i]] = FoodCost[i];
    }

    for(int i=0; i<6; ++i)
    {
        string city = Trains[i];
        ifstream os;
        string f ="./Trains/"+city+"Trains.txt";
        os.open(f);
        string s;
        int cnt= 1,idx=1;
        while(getline(os,s))
        {

            if(cnt%2==0)
            {
                int cls=-1,pr=0;
                for(int i=0; i<s.size(); ++i)
                {

                    if(cls!=-1 && isdigit(s[i]))
                    {
                        int j = i;
                        while(j<s.size() && isdigit(s[j]))
                        {
                            pr = pr*10 + s[j]-'0';
                            ++j;
                        }
                        i = j;
                    }

                    if(isdigit(s[i-1]) && s[i]=='A')
                    {
                        cls = s[i-1]-'0';
                    }

                    if(cls!=-1 and pr!=0)
                    {
                        pair<string,pair<int,int>>train= {city,{cls,idx}};
                        Price[train] = pr;
                        cls=-1;
                        pr = 0;
                    }
                }

                ++idx;
            }
            ++cnt;
        }
        os.close();
    }


    ifstream os;
    os.open("UsersData.txt");
    string em,ps;
    while(os>>em>>ps)
    {

        if(em.empty() or ps.empty())
            continue;

        User me(em,ps);

        vector<string>pnrs;
        ifstream os1;
        string s;
        os1.open("PNRs.txt");
        while(getline(os1,s))
        {
            if(s.size())
                pnrs.push_back(s);
        }
        os1.close();

        for(auto &pnr : pnrs)
        {

            string c ="./Tickets/"+em+"_"+pnr+"C.txt";

            ifstream Check(c);
            if(Check.good())
            {

                Ticket tk;
                tk.PNR = stoi(pnr);
                ReturnCustomers(c,tk);
                c = "./Tickets/"+em+"_"+pnr+"F.txt";
                ReturnFood(c,tk);
                me.Add(tk);
            }
        }
        if(LOGING.find({em,ps})==LOGING.end()){
        LOGING[ {em,ps}] = me;
        Admin.Add(me);
        }
    }
    os.close();

}


void InterFace2(User &user)
{



    while(true)
    {

        FillData();
        cout<<"\t\t----------------------------------------------------------------------------------------------\n";
        cout<<"\t\t\t\t\t Welcome To Our Railways\n\n\n";
        cout<<"\t\t----------------------------------Main Menu--------------------------------------\n\n";
        cout<<"\t\t|\t\t\tPress 1 to Book a Ticket \t\t\t\t|\n";
        cout<<"\t\t|\t\t\tPress 2 to Get Your Ticket and Charge \t\t\t|\n";
        cout<<"\t\t|\t\t\tPress 3 to Cancel a Ticket \t\t\t\t|\n";
        cout<<"\t\t|\t\t\tPress 4 to Order Food \t\t\t\t\t\|\n";
        cout<<"\t\t|\t\t\tPress 5 to View Ordered Food \t\t\t\t\|\n";
        cout<<"\t\t|\t\t\tPress 6 to View Total Cost for Ticket \t\t\t\|\n";
        cout<<"\t\t|\t\t\tPress 7 to Exist \t\t\t\t\t\|\n\n";
        cout<<"\t\t---------------------------------------------------------------------------------\n\n";

        int Choice;
        cout<<"Enter the Choice : ";

        try
        {
           string s;
            cin>>s;

            if(s>="1" and s<="7")
            Choice = stoi(s);
            else
                throw 1;
        }
        catch(int q)
        {
            cout<<"\t\tInvalid Input Please Enter A number Between 1-6\n\n";
            continue;
        }

        if(Choice==1)
        {

            cout<<"____ Book a Ticket Section\n\n";

Repeat:
            cout<<"1. Train to Qena\n";
            cout<<"2. Train to Luxor\n";
            cout<<"3. Train to Assuit\n";
            cout<<"4. Train to Cairo\n";
            cout<<"5. Train to Alexandria\n";
            cout<<"6. Train to Aswan\n";

            cout<<"Press the number of the city you want to book to : ";

            try
            {
                 string s;
            cin>>s;

            if(s>="1" and s<="6")
            Choice = stoi(s);
            else
                    throw "Invalid number Please Enter a number between 1-6\n";
            }
            catch(const char *msg)
            {
                cout<<msg<<"\n";
                goto Repeat;
            }

            string City = Trains[--Choice];

            cout<<"\n";
            cout<<"__Welcome to "<<City<<" __\n\n";

            cout<<"Your Comfort is our Priority , Enjoy the Journey !\n";

            cout<<"Following are the Trains :\n\n";

            ifstream is;

            string f ="./Trains/"+City+"Trains.txt";
            is.open(f);

            string s;
            while(getline(is,s))
            {
                cout<<s<<"\n";
            }

            is.close();

            here1:

            cout<<"Select the Train you want to travel : ";

             cin>>s;
             if(s>="1" and s<="3"){

             }
             else{
                cout<<"There is no Train With This Number \n";
                goto here1;
             }

            cout<<"\n";
            string Class;
            here2:

            cout<<"Select the Ac class in which you want travel : ";
            cin>>Class;

              if(Class>="1" and Class<="3"){

             }
             else{
                cout<<"There is no Class With This Number \n";
                goto here2;
             }

            cout<<"\n";

            cout<<"You Have Successfully Booked \n\n";

             here3:
            cout<<"Enter the Number of Passengers : ";

            string num;
            cin>>num;

             if(num>="1" && num<="6"){

             }
             else{
                cout<<"Invalid input or The number is Greater Than 6\n";
                goto here3;
             }


            cout<<"\n";
            Ticket ticket(stoi(Class),City,stoi(num),user.file,stoi(s));

            cin>>ticket;

            cout<<"Your Details Are Saved With Us.\n";
            user.Add(ticket);
            cout<<"Your PNR Code is : "<<ticket.PNR<<" and you now have "<<user.counter<<" Tickets for this User \n";

            cout<<"Please Save Your PNR Code In Safe Area To Get along with Your Journey!\n\n";
            cout<<"press any key to go back...\n";
            string x;
            cin>>x;

        }
        else if(Choice==2)
        {

            cout<<"Currently This User Has "<<user.counter<<" Tickets \n";

            cout<<"Enter the PNR Number Of the Ticket You want to see :";
            int num;
            cin>>num;

            if(!user.IsPNR_Exist(num))
            {
                cout<<"There are no Ticket with this PNR number \n";
                cout<<"Due to This Invalid Input we will get Back To Main Menu\n";
            }
            else
            {
                user.GetBY_PNR(num)->ShowCustomersData();
            }
            cout<<"Press any key to go back ... \n";
            string x;
            cin>>x;

        }
        else if(Choice==3)
        {
            cout<<"Enter PNR No : ";
            int num;
            cin>>num;
            cout<<"the record with name "<<num<<" has been deleted if it exists\n";
            user.Delete(num);
            cout<<"Press any key to go back... \n";
            string x;
            cin>>x;
        }
        else if(Choice==4)
        {

            cout << "\n____________________________________________________________________" << endl;
            cout << "____________________________FOOD MENU_________________________________" << endl
                 << endl;

            cout << "\t|S.no."
                 << "\t|Item Name"
                 << "\t\t\t|Price"
                 << "\t\t\t|" << endl;
            cout << "\t|1."
                 << "\t|Koshari"
                 << "\t\t\t| 20 L.E"
                 << "\t\t|" << endl;
            cout << "\t|2."
                 << "\t|Chicken Shawrma"
                 << "\t\t| 50 L.E"
                 << "\t\t|" << endl;
            cout << "\t|3."
                 << "\t|Meat Shawrma"
                 << "\t\t\t| 60 L.E"
                 << "\t\t|" << endl;
            cout << "\t|4."
                 << "\t|Hawashi"
                 << "\t\t\t| 30 L.E"
                 << "\t\t|" << endl;
            cout << "\t|5."
                 << "\t|Ful Medames Sandawitch"
                 << "\t\t| 10 L.E"
                 << "\t\t|" << endl;
            cout << "\t|6."
                 << "\t|Ta3mia Sandwitch"
                 << "\t\t| 5 L.E"
                 << "\t\t\t|" << endl;
            cout << "\t|7."
                 << "\t|Konafa "
                 << "\t\t\t| 35 L.E"
                 << "\t\t|" << endl;
            cout << "\t|8."
                 << "\t|Umm Ali"
                 << "\t\t\t| 40 L.E"
                 << "\t\t|" << endl;

            cout<<"Enter The PNR Code for Ticket :";
            int pnr;
            cin>>pnr;

            if(user.IsPNR_Exist(pnr)==0)
            {
                cout<<"There is no Ticket With This PNR In This User\n";
                cout<<"For This Invalid PNR Code For Security Reasons Back To Main Menu\n";
                continue;
            }

            Ticket *tk = user.GetBY_PNR(pnr);

            cout<<"Enter the Number Of Items You Want : ";
            int no;
            cin>>no;

            for(int i=1;i<=no;++i)
            {

                cout<<"Enter the Number of Item you Want To buy :";
                int num;
                cin>>num;
                --num;
                cout<<Food[num]<<" Has Been Purchased\n\n";

                tk->AddFood(num);
            }
        }
        else if(Choice==5)
        {
            cout<<"Enter The PNR Code for Ticket :";
            int pnr;
            cin>>pnr;

            if(user.IsPNR_Exist(pnr)==0)
            {
                cout<<"There is no Ticket With This PNR In This User\n";
                cout<<"For This Invalid PNR Code For Security Reasons Back To Main Menu\n";
                continue;
            }

            Ticket *tk = user.GetBY_PNR(pnr);

            tk->ShowFoodData();
        }
        else if(Choice==6){
             cout<<"Enter The PNR Code for Ticket :";
            int pnr;
            cin>>pnr;

            if(user.IsPNR_Exist(pnr)==0)
            {
                cout<<"There is no Ticket With This PNR In This User\n";
                cout<<"For This Invalid PNR Code For Security Reasons Back To Main Menu\n";
                continue;
            }
            Ticket *tk = user.GetBY_PNR(pnr);
           cout<<"Total Cost for Ticket With PNR : "<<pnr<<"\n\n";
           cout<<"Cost for Food = "<<tk->FCost<<" L.E and For Train = "<<tk->BCost<<" L.E \n\n";

            cout<<"So Total Cost = "<<tk->TotalCost()<<" L.E \n\n";
        }
        else
        {
            cout<<"\t\tBye "<<user.Email<<" Thanks For Using Our Railway\n\n";
            cout<<"\t\tNow Returning To The Main Menu : \n\n";
            break;
        }
    }
}

#endif // USER_H
