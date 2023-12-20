#ifndef CUSTOMER_H
#define CUSTOMER_H

const string Trains[6]= {"Qena","Luxor","Assuit","Cairo","AlexAndria","Aswan"};
const string Food[9]= {"Koshari","Chicken_Shawrma","Meat_Shawrma","Hawashi","Ful_Medames", "Ta3mia","Konafa","Umm_Ali"};
const int FoodCost[9]= {20,50,60,30,10,5,35,40};
map<string,int>mp_FoodCost;
map<pair<string,pair<int,int>>,int>Price;/// (city,(class,idx)),cost

class Customer
{

public :

    Customer()
    {
    }

    Customer(string file,string PNR)
    {
        this->PNRT=PNR;
        this->file = file;
    }
    string Def;
protected :
    int Age;
    string Name,Gender,ID;

    friend istream&operator>>(istream &is,Customer &c);

private :
    string PNRT,file;
};

istream&operator>>(istream &is,Customer &c)
{

    ofstream os;
    string f ="./Tickets/"+c.file+"_"+c.PNRT+"C.txt";
    os.open(f,ios::app);

    cout<<"Enter the Customer ID : ";
    is>>c.ID;
    cout<<"\n";

    cout<<"Enter the Customer Name : ";
    is>>c.Name;
    cout<<"\n";

    cout<<"Enter the Customer Age : ";
    is>>c.Age;
    cout<<"\n";

    cout<<"Enter the Customer Gender : ";
    is>>c.Gender;
    cout<<"\n";

    string temp = "Customer ID : "+c.ID+"\t Name : "+c.Name+"\t Age : "+to_string(c.Age)+"\t Gender : "+c.Gender+"\t PNR : "+c.PNRT;
    os<<temp<<"\n\n";
    c.Def = temp;
    os.close();

    return is;
}



class Ticket
{

public  :
    int PNR,counter=0;
    vector<Customer>v;
    vector<string>C,F;
    map<string,int>mp;
    Ticket(int Class,string city,int num,string file,int Train_idx)
    {

        this->PNR = 20+(rand()%100);
        while(isExist(this->PNR))
        {
            this->PNR = 20+(rand()%100);
        }
        ofstream os;
        os.open("PNRs.txt",ios::app);
        os<<to_string(PNR)<<"\n";
        os.close();

        this->Class = Class;
        this->Destination = city;

        this->sz = num;
        this->file = file;

        pair<string,pair<int,int>>train= {city,{Class,Train_idx}};

        this->BCost = num * Price[train];

        v = vector<Customer>(sz);

        for(int i=0; i<sz; ++i)
            v[i] = Customer(this->file,to_string(this->PNR));

        ofstream os1;
        string f ="./Tickets/"+file+"_"+to_string(PNR)+"C.txt";

        os1.open(f,ios::app);

        string temp = "Ticket Which PNR Code is "+to_string(PNR)+" and Destination is "+Destination+" And Total Cost = "+to_string(this->BCost)+" P.E : "+"Having "+to_string(num)+" Customers ";
        os1<<temp<<"\n";
        C.push_back(temp);
        os1.close();

        ofstream os2;

        f ="./Tickets/"+file+"_"+to_string(PNR)+"F.txt";
        os2.open(f,ios::app);
        temp  = "ORDERED FOOD LIST : ";
        F.push_back(temp);
        os2<<temp<<"\n";
        os2.close();

    }

    Ticket()
    {
    }

    void AddData()
    {


        ofstream os1;
        string f ="./Tickets/"+file+"_"+to_string(PNR)+"C.txt";

        os1.open(f,ios::app);

        string temp = "Ticket Which PNR Code is "+to_string(PNR)+" and Destination is "+Destination+" And Total Cost = "+to_string(this->BCost)+" P.E : "+"Having "+to_string(sz)+" Customers ";
        os1<<temp<<"\n";
        for(auto &s :  this->C)
            os1<<s<<endl;
        os1.close();

        ofstream os2;

        f ="./Tickets/"+file+"_"+to_string(PNR)+"F.txt";
        os2.open(f,ios::app);
        temp  = "ORDERED FOOD LIST : ";
        os2<<temp<<"\n";
        for(auto &s : this->F)
            os2<<s<<endl;
        os2.close();



    }

    void ShowCustomersData()
    {

        for(auto &s : this->C)
            cout<<s<<endl;
    }

    void AddFood(int idx,bool restore=0)
    {
        this->FCost += FoodCost[idx];
        this->mp[Food[idx]]++;
        this->counter++;
        if(restore)
            return;
        ofstream os;
        string f ="./Tickets/"+file+"_"+to_string(PNR)+"F.txt";
        os.open(f,ios::app);
        string temp = to_string(this->counter)+"- "+Food[idx]+" With Price = "+to_string(FoodCost[idx]);
        F.push_back(temp);
        os<<temp<<"\n";
        os.close();
    }

    void ShowFoodData()
    {

        for(auto &s : this->F)
            cout<<s<<endl;
    }

    int TotalCost()
    {
        return BCost+FCost;
    }

    int BCost=0,Class,FCost=0;
    string Destination,file;
    int sz;
protected :

private :

    void MoveData()
    {
        for(int i=0; i<this->sz; ++i)
        {
            C.push_back(v[i].Def);
        }
    }

    bool isExist(int num)
    {

        ifstream os;
        os.open("PNRs.txt");
        string s;
        bool Exist=0;
        while(getline(os,s))
        {
            if(s.size() && stoi(s)==num)
                Exist = 1;
        }
        os.close();
        return Exist;
    }
    friend istream&operator>>(istream &is,Ticket &tk);

};

istream&operator>>(istream &is,Ticket &tk)
{
    for(int i=0; i<tk.sz; ++i){
        cout<<"Details For Customer No : "<<i+1<<": \n\n";
        is>>tk.v[i];
    }
    tk.MoveData();
    return is;
}

#include "User.h"


#endif // CUSTOMER_H
