#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <bits/c++io.h>
#include <iterator>
#include <map>

using namespace std;

string s = "FCI-001";
bool can = false;
string searchFile(ifstream & stream, string target);
bool CheckSubstring(string firstString, string secondString);
void balCorrec(string s1 ,string s2);

class BankAcount
{
    private:
        string accountID;
        int Balance;
    public:
        BankAcount()
        {
            Balance=0;
        }
        BankAcount(int val): Balance(val)
        {
        }
        void setAccID(string id)
        {
            accountID=id;
        }
        string getAccID() const
        {
            return accountID;
        }
        void setBalance(int val)
        {
            Balance=val;
        }
        int getBalanace() const
        {
            return Balance;
        }

        virtual void withDraw(int val)
        {
            if(Balance>=val)
            {
                Balance-=val;
                can = true;
            }else{
                cout << "Sorry. This is more than what you can withdraw." <<endl;
            }
        }
        virtual void deposit(int val)
        {
            Balance+=val;
            can = true;
        }

};

class SavingsBankAccount : public BankAcount
{
    private:
        int minBalance = 1000;

    public:
        SavingsBankAccount(int Bal , int minBal): BankAcount(Bal)
        {
            minBalance=minBal;
            if(Bal>=minBalance)
            {
                setBalance(Bal);
                setMinBalance(minBal);
            }else{
                cout << "sorry can not create a new account with this starting balance" << endl;
            }
        }
        void setMinBalance(int val)
        {
            minBalance=val;
        }
        int getMinBalance() const
        {
            return minBalance;
        }

        void withDraw(int val)
        {
            if((getBalanace()-val)>=minBalance)
            {
                int x = getBalanace();
                x-=val;
                setBalance(x);
                can = true;
            }else{
                cout << "Sorry. This is more than what you can withdraw." << endl;
            }
        }
        void deposit(int val)
        {
            if(val>=100)
            {
                int x = getBalanace();
                x+=val;
                setBalance(x);
                can = true;
            }else{
                cout << "Sorry. you can not deposit this amount." << endl;
            }
        }

};

class CertificateOfDeposite : public BankAcount
{
    private:
        int minBalance = 20000;
        float withdrawPenaltyPercent = 0.01;

    public:
        CertificateOfDeposite(int bal): BankAcount(bal)
        {
            if(bal%minBalance==0)
            {
                setBalance(bal);
            }else{
                cout << "not multiple of minimum balance which is " << minBalance << endl;
            }
        }
        void setMinBalance(int val)
        {
            if(val>=20000)
            {
                minBalance = val;
            }
        }
        int getMinBalance() const
        {
            return minBalance;
        }
        void setWithdrawPercent(int val)
        {
            withdrawPenaltyPercent = val/100;
        }
        float getWithdrawPercent() const
        {
            return withdrawPenaltyPercent;
        }

        void withDraw(int val)
        {
            if(minBalance<=(getBalanace()-(val*withdrawPenaltyPercent+val)))
            {
                int x = getBalanace();
                x-=((val*withdrawPenaltyPercent)+val);
                setBalance(x);
                can = true;
            }else{
                cout << "Sorry. This is more than what you can withdraw." << endl;
            }
        }

        void deposit(int val)
        {
            if(val%minBalance==0)
            {
                int x = getBalanace();
                x+=val;
                setBalance(x);
                can = true;
            }else{
                cout << "Sorry. you can not deposit this amount." << endl;
            }
        }
};

class Client
{
    private:
        string name , address , phoneNumber;

    public:
        Client()
        {
            name = " ";
            address = " ";
            phoneNumber = " ";
        }
        void setName(string n)
        {
            name = n;
        }
        void setAdress(string ad)
        {
            address = ad;
        }
        void setPhone(string n)
        {
            phoneNumber = n;
        }
        string getName() const
        {
            return name;
        }
        string getAddress() const
        {
            return address;
        }
        string getPhone() const
        {
            return phoneNumber;
        }

        BankAcount * pAcc;

};

class BankingApp
{
    public:

        void desplayMenu();
};

void BankingApp::desplayMenu()
{
    int choice;
    ofstream temp("temp.txt");
    map<string , int> mp;
    map<string , int>::iterator t;
    while(true){
    cout << "Welcome to FCI Banking Application" << endl;
    cout << "1. Create a New Account" << endl;
    cout << "2. List Clients and Accounts" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Deposit Money" << endl;
    cout << "Please Enter Choice ==> " ;
    cin >> choice;
    cin.ignore();
    cout << endl;

    if(choice==1)
    {
        Client cl;

        string name,addres,phone;
        int typeOfAccount;
        cout << "Please Enter Client Name ==> ";
        getline(cin , name);
        cl.setName(name);
        cout << "Please Enter Client Address ==> ";
        getline(cin , addres);
        cl.setAdress(addres);
        cout << "Please Enter Client Phone ==> ";
        getline(cin , phone);
        cl.setPhone(phone);
        cout << "What Type of Account Do You Like? (1) Basic (2) Saving (3) Certificate - Type 1 or 2 or 3" << endl;
        cin >> typeOfAccount;
        if(typeOfAccount==1)
        {
            int strBalance;
            ofstream bankData;
            cout << "Please Enter the Starting Balance ==> ";
            cin >> strBalance;
            cl.pAcc=new BankAcount(strBalance);
            cl.pAcc->setAccID(s);

            s[s.length()-1] = ((s[s.length()-1]-'0') + ('1'-'0'))+'0';
            bankData.open("BankData.txt", ios::app);
            bankData << "----------- " << cl.getName() << " -----------\n";
            bankData << "Address: " << cl.getAddress() << "\n";
            bankData << "Phone Number: " << cl.getPhone() << "\n";
            bankData << "Account ID: " << cl.pAcc->getAccID() << "  Account Type: (Basic)     ";
            bankData << "Balance: " << cl.pAcc->getBalanace() << "\n\n";
            cout << "An account was created with ID " << cl.pAcc->getAccID()
            << " and Starting Balance " << cl.pAcc->getBalanace() << " L.E" << endl;
            mp.insert(pair<string , int>(cl.pAcc->getAccID(), cl.pAcc->getBalanace()));

            bankData.close();
        }else if(typeOfAccount==2)
        {
            int balance , minBal;
            ofstream bankData;
            string decesion;
            cout << "Please Enter The Balance ==> ";
            cin >> balance;
            cout << "Do you want to change the minimum balance! (Y/N) ==> ";
            cin >> decesion;
            if(decesion == "Y")
            {
                cout << "Enter the minimum balance by default it's 1000 L.E ==> ";
                cin >> minBal;
            }else{
                cout << "Default is running" << endl;
                minBal = 1000;
            }
            SavingsBankAccount obj(balance , minBal);
            obj.setMinBalance(minBal);
            obj.setAccID(s);
            if(balance>=obj.getMinBalance())
            {

                s[s.length()-1] = ((s[s.length()-1]-'0') + ('1'-'0'))+'0';
                bankData.open("BankData.txt", ios::app);
                bankData << "----------- " << cl.getName() << " -----------\n";
                bankData << "Address: " << cl.getAddress() << "\n";
                bankData << "Phone Number: " << cl.getPhone() << "\n";
                bankData << "Account ID: " << obj.getAccID() << "  Account Type: (Saving)       ";
                bankData << "Balance: " << obj.getBalanace() << "\n\n";
                cout << "An account was created with ID " << obj.getAccID()
                << " and Starting Balance " << obj.getBalanace() << " L.E" << endl;
                mp.insert(pair<string , int>(obj.getAccID(), obj.getBalanace()));

                bankData.close();
            }

        }else if(typeOfAccount==3)
        {
           int balance;
           ofstream bankData;
           cout << "Please Enter The Balance ==> ";
           cin >> balance;
           CertificateOfDeposite obj(balance);
           obj.setAccID(s);
            if(balance%obj.getMinBalance()==0)
            {
                s[s.length()-1] = ((s[s.length()-1]-'0') + ('1'-'0'))+'0';
                bankData.open("BankData.txt", ios::app);
                bankData << "----------- " << cl.getName() << " -----------\n";
                bankData << "Address: " << cl.getAddress() << "\n";
                bankData << "Phone Number: " << cl.getPhone() << "\n";
                bankData << "Account ID: " << obj.getAccID() << "  Account Type: (Certificate)      ";
                bankData << "Balance: " << obj.getBalanace() << "\n\n";
                cout << "An account was created with ID " << obj.getAccID()
                << " and Starting Balance " << obj.getBalanace() << " L.E" << endl;
                mp.insert(pair<string , int>(obj.getAccID(), obj.getBalanace()));

                bankData.close();
            }
        }
    }else if(choice==2)
    {
        ifstream listClient;
        listClient.open("BankData.txt");

        if(listClient)
        {
         char line[100];
            while(listClient){
                listClient.getline(line,100);
                cout << line << endl;
            }
        }
    }else if(choice==3)
    {
        string targtedID , respon;
        int wdBalance;
        ifstream infile;
        infile.open("BankData.txt");
        cout << "Please Enter Account ID (e.g., FCI-005) ==> ";
        cin >> targtedID;
        respon = searchFile(infile , targtedID);
        cout << respon <<endl;

        if(CheckSubstring(respon , "(Basic)")==1)
        {
            int bal;
            t = mp.find(targtedID);
            BankAcount obj(t->second);
            while(true)
            {
                if(can==0)
                {
                    cout << "Please Enter The Amount to Withdraw ==> ";
                    cin >> bal;
                    obj.withDraw(bal);
                }else if(can == 1)
                {
                    cout << "Thank You." << endl;
                    cout << "Account ID: " << targtedID << endl;
                    cout << "New Balance: " << obj.getBalanace() << endl;
                    t->second = obj.getBalanace();
                    break;
                }
            }
            string s = to_string(obj.getBalanace());
            balCorrec(respon , "Account ID: "+targtedID+"  Account Type: (Basic)     Balance: "+s);
            can=false;
        }else if(CheckSubstring(respon , "(Saving)")==1)
        {
            int bal;
            t = mp.find(targtedID);
            SavingsBankAccount obj(t->second , 1000);
            while(true)
            {
                if(can==0)
                {
                    cout << "Please Enter The Amount to Withdraw ==> ";
                    cin >> bal;
                    obj.withDraw(bal);
                }else if(can == 1)
                {
                    cout << "Thank You." << endl;
                    cout << "Account ID: " << targtedID << endl;
                    cout << "New Balance: " << obj.getBalanace() << endl;
                    t->second = obj.getBalanace();
                    break;
                }
            }
            string s = to_string(obj.getBalanace());
            balCorrec(respon , "Account ID: "+targtedID+"  Account Type: (Saving)     Balance: "+s);
            can=false;
        }else if(CheckSubstring(respon , "(Certificate)")==1)
        {
            int bal;
            t = mp.find(targtedID);
            CertificateOfDeposite obj(t->second);
            while(true)
            {
                if(can==0)
                {
                    cout << "Please Enter The Amount to Withdraw ==> ";
                    cin >> bal;
                    obj.withDraw(bal);
                }else if(can == 1)
                {
                    cout << "Thank You." << endl;
                    cout << "Account ID: " << targtedID << endl;
                    cout << "New Balance: " << obj.getBalanace() << endl;
                    t->second = obj.getBalanace();
                    break;
                }
            }
            string s = to_string(obj.getBalanace());
            balCorrec(respon , "Account ID: "+targtedID+"  Account Type: (Certificate)     Balance: "+s);
            can=false;
        }
    }else if(choice==4)
    {
        string targtedID , respon;
        int wdBalance;
        ifstream infile;
        infile.open("BankData.txt");
        cout << "Please Enter Account ID (e.g., FCI-005) ==> ";
        cin >> targtedID;
        respon = searchFile(infile , targtedID);
        cout << respon <<endl;

        if(CheckSubstring(respon , "(Basic)")==1)
        {
            int bal;
            t = mp.find(targtedID);
            BankAcount obj(t->second);
            while(true)
            {
                if(can==0)
                {
                    cout << "Please Enter The Amount to Deposit ==> ";
                    cin >> bal;
                    obj.deposit(bal);
                }else if(can == 1)
                {
                    cout << "Thank You." << endl;
                    cout << "Account ID: " << targtedID << endl;
                    cout << "New Balance: " << obj.getBalanace() << endl;
                    t->second = obj.getBalanace();
                    break;
                }
            }
            string s = to_string(obj.getBalanace());
            balCorrec(respon , "Account ID: "+targtedID+"  Account Type: (Basic)     Balance: "+s);
            can=false;
        }else if(CheckSubstring(respon , "(Saving)")==1)
        {
            int bal;
            t = mp.find(targtedID);
            SavingsBankAccount obj(t->second , 1000);
            while(true)
            {
                if(can==0)
                {
                    cout << "Please Enter The Amount to Deposit ==> ";
                    cin >> bal;
                    obj.deposit(bal);
                }else if(can == 1)
                {
                    cout << "Thank You." << endl;
                    cout << "Account ID: " << targtedID << endl;
                    cout << "New Balance: " << obj.getBalanace() << endl;
                    t->second = obj.getBalanace();
                    break;
                }
            }
            string s = to_string(obj.getBalanace());
            balCorrec(respon , "Account ID: "+targtedID+"  Account Type: (Saving)     Balance: "+s);
            can=false;
        }else if(CheckSubstring(respon , "(Certificate)")==1)
        {
            int bal;
            t = mp.find(targtedID);
            CertificateOfDeposite obj(t->second);
            while(true)
            {
                if(can==0)
                {
                    cout << "Please Enter The Amount to Deposit ==> ";
                    cin >> bal;
                    obj.deposit(bal);
                }else if(can == 1)
                {
                    cout << "Thank You." << endl;
                    cout << "Account ID: " << targtedID << endl;
                    cout << "New Balance: " << obj.getBalanace() << endl;
                    t->second = obj.getBalanace();
                    break;
                }
            }
            string s = to_string(obj.getBalanace());
            balCorrec(respon , "Account ID: "+targtedID+"  Account Type: (Certificate)     Balance: "+s);
            can=false;
            can=false;
        }
    }
    cout << endl;
    }
}

string searchFile(ifstream & stream, string target)
{
    bool found = false;
    string line;
    while(getline(stream , line))
    {
        if(line.find(target) != string::npos)
        {
            return line;
            found = true;
        }
    }
    if(!found)
    {
        return "there is no account with ID: "+target+" in the database";
    }
}

bool CheckSubstring(string firstString, string secondString){
    if(secondString.size() > firstString.size())
        return false;

    for (int i = 0; i < firstString.size(); i++){
        int j = 0;
        // If the first characters match
        if(firstString[i] == secondString[j]){
            int k = i;
            while (firstString[i] == secondString[j] && j < secondString.size()){
                j++;
                i++;
            }
            if (j == secondString.size())
                return true;
            else // Re-initialize i to its original value
                i = k;
        }
    }
    return false;
}

void balCorrec(string s1 ,string s2)
{
    ifstream filein("BankData.txt" , ios::in);
    ofstream fileout("temp.txt");
    string strTemp;
    while(getline(filein , strTemp))
    {
        if(strTemp == s1)
		{
            strTemp = s2;
        }

        fileout << strTemp <<endl;
    }
    ifstream    inFile("temp.txt");
    ofstream    outFile("BankData.txt");

    outFile << inFile.rdbuf();
}

int main()
{
    BankingApp ob;

    ob.desplayMenu();

    return 0;
}
