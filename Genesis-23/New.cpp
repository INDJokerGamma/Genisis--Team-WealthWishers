#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Account
{
public:
    double balance = 0;
    long long int deposit = 0;
    long long int withdraw = 0;
    string username;
    string password;
    string mail;
    string phoneNumber;

    void userRegistration(string &name, string &Phone, string &password, string &email)
    {
        this->username = name;
        this->phoneNumber = Phone;
        this->password = password;
        this->mail = email;
        ofstream out;
        out.open("data.txt", ios::app);
        ofstream temp("temp.txt",ios::app);
        if (out)
        {
            out << this->username << endl
                << this->phoneNumber << endl
                << this->mail << endl
                << this->password << endl
                << this->balance << endl;
            temp << this->username << endl
                << this->phoneNumber << endl
                << this->mail << endl
                << this->password << endl
                << this->balance << endl;
            out.close();
            temp.close();
            cout << "Your Information Is Saved To File" << endl;
        }
        else
        {
            cerr << "Your Information Is Not Saved To File Because Of Some Error" << endl;
        }
    }

    bool userLogin()
    {
        string userEmail;
        string userPassword;
        cout << "Enter Your Email: ";
        cin >> userEmail;
        cout << "Enter Your Password: ";
        cin >> userPassword;
        ifstream input;
        input.open("data.txt");
        if (!input)
        {
            cerr << "Error opening file." << endl;
            return false;
        }

        // Check if file is empty
        if (input.peek() == std::ifstream::traits_type::eof())
        {
            cout << "File is empty." << endl;
            input.close();
            return false;
        }
        int cnt = 1;
        string line;
        cout << "hi";
        while (getline(input, line))
        {
            cnt++;
            if (line == userEmail)
            {
                getline(input, line);
                if (line == userPassword)
                {
                    cout << "Successfully Logged In! Thanks For Visiting Our Application!" << endl;
                    ifstream inp("data.txt");
                    string str;
                    for (int i = 1; i < cnt - 2; i++)
                    {
                        getline(inp, str);
                    }
                    this->username = str;
                    getline(inp, str);
                    this->phoneNumber = str;
                    getline(inp, str);
                    this->mail = str;
                    getline(inp, str);
                    this->password = str;
                    double b;
                    inp >> b;
                    this->balance = b;
                    input.close();
                    return true;
                }
            }
        }

        cout << "Doesn't Found Account With This Email And Password!" << endl;
        cout << "Please Register First Or Check Your Email Or Password Carefully!" << endl;
        input.close();
        return false;
    }

    void displayProfile()
    {
        ifstream input;
        input.open("data.txt");
        if (!input)
        {
            cerr << "Error opening file." << endl;
            return;
        }

        // Check if file is empty
        if (input.peek() == std::ifstream::traits_type::eof())
        {
            cout << "File is empty." << endl;
            input.close();
            return;
        }
        string line;
        while (getline(input, line))
        {
            if (line == this->username)
            {
                cout << "Name: " << line << endl;
                getline(input, line);
                cout << "Phone No: " << line << endl;
                getline(input, line);
                cout << "Email: " << line << endl;
                getline(input, line);
                cout << "Password: " << line << endl;
                break;
            }
        }
        input.close();
    }

    void displayBalance()
    {
        cout << "Total Available Balance In Your Wallet: " << this->balance << " Rs" << endl;
    }

    vector<pair<string, int>> transactions;
    int cnt = 0;
    void depositMoney()
    {
        long long money;
        cout << "Enter Amount You Want To Deposit: ";
        cin >> money;
        deposit += money;
        balance += money;
        transactions.push_back({"Deposited:", deposit});
        ifstream out("data.txt");
        string line;
        while (getline(out, line))
        {
            if (line == this->username)
            {
                for (int i = 0; i < 4; i++)
                {
                    getline(out, line);
                }
                ofstream output;
                output.open("data.txt", ios::app);
                output << "Deposited:" << deposit << endl;
                break;
            }
        }

        cout << money << " Rs Deposited In Your Wallet!" << endl;
        displayBalance();
        cout << endl;
    }

    void transactionsHistory()
    {
        ifstream out("data.txt", ios::app);
        string line;
        while (getline(out, line))
        {
            if (line == this->username)
            {
                for (int i = 0; i < 5; i++)
                {
                    getline(out, line);
                }
                cout << line << endl;
                break;
            }
        }
    }
    void withdrawMoney()
    {
        long long money;
        cout << "Enter Amount You Want To Withdraw: ";
        cin >> money;
        if (money <= balance)
        {
            withdraw += money;
            balance -= money;
            transactions.push_back({"Withdrawn: ", withdraw});
            cout << money << " Rs Withdrawn From Your Wallet!You Can Check Your Balance!" << endl;
            ifstream out("data.txt", ios::app);
            string line;
            while (getline(out, line))
            {
                if (line == this->username)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        getline(out, line);
                    }
                    ofstream output;
                    output.open("data.txt",ios :: app);
                    output << "Withdrawn:" << withdraw << endl;
                    break;
                }
            }
            displayBalance();
            cout << endl;
        }
        else
        {
            cout << "Insufficient Balance!" << endl;
            displayBalance();
            cout << endl;
        }
    }

    void feedback()
    {
        string userFeedback;
        cout << "Write Your Feedback: ";
        cin.ignore();
        getline(cin, userFeedback);
        cout << "Thanks For Giving Feedback!" << endl;
    }
};

class Stock
{
private:
    string company;
    double price;

public:
    Stock(string company, int price)
    {
        this->company = company;
        this->price = price;
    }
    string getCompany() const
    {
        return this->company;
    }
    int getPrice() const
    {
        return this->price;
    }
};

class portfolio : public Account
{
private:
    vector<Stock> stocks;

public:
    void buyStocks(Stock &stock, int quantity)
    {
        double totalCost = stock.getPrice() * quantity;
        if (totalCost > balance)
        {
            cout << "Insufficient Balance To Buy " << quantity << "Shares Of " << stock.getCompany() << endl;
            return;
        }
        for (int i = 0; i < quantity; i++)
        {
            stocks.push_back(stock);
        }
        balance -= totalCost;
        cout << "Bought" << quantity << "Stocks Of " << stock.getCompany() << endl;
    }

    void sellStocks(Stock &stock, int quantity)
    {
        int cnt = 0;
        for (auto i = stocks.begin(); i != stocks.end();)
        {
            if (cnt == quantity)
                break;
            if (i->getCompany() == stock.getCompany())
            {
                i = stocks.erase(i);
                cnt++;
            }
            else
            {
                i++;
            }
        }
        double totalSale = stock.getPrice() * cnt;
        balance += totalSale;
        cout << "Successfully Sold " << cnt << "Shares Of " << stock.getCompany() << endl;
    }
};

int main()
{
    Stock apple("Apple", 80);
    Stock google("Google", 100);
    Stock samsung("Samsung", 50);
    Account Person;
    portfolio User;
    int choice;
    string name;
    string password;
    string phone;
    string email;
    bool registration = false;
    bool loggedIn = false;
    bool decide;
    cout << "*" << endl;
    while (1)
    {
        if (!registration)
            cout << "Press 1 for User Registration" << endl;
        if (!loggedIn)
            cout << "Press 2 for User Login" << endl;
        cout << "*" << endl;
        if (loggedIn)
        {
            cout << "Choose From Below Options:" << endl;
            cout << "Press 3 To Check Your Profile!" << endl;
            cout << "Press 4 for Checking Total Balance In Your Wallet!" << endl;
            cout << "Press 5 for Withdrawing Money From Wallet!" << endl;
            cout << "Press 6 for Depositing Money In Wallet!" << endl;
            cout << "Press 7 for Viewing Transaction History!" << endl;
            cout << "Press 8 For Giving Feedback!";
            cout << "Press 9 for Viewing Market Analysis!" << endl;
            cout << "Press 10 for Viewing Available Schemes!" << endl;
            cout << "Press 11 for Buying Stocks!" << endl;
            cout << "Press 12 for Selling Stocks!" << endl;
            cout << "Press 13 for Logging Out!" << endl;
            cout << "*" << endl;
        }

        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Your Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Your Phone Number: ";
            cin >> phone;
            while (phone.length() != 10)
            {
                cout << "Enter Valid Mobile Number!" << endl;
                cin >> phone;
            }
            cout << "Enter Your Email: ";
            cin >> email;
            cout << "Enter Your Password: ";
            cin >> password;
            Person.userRegistration(name, phone, password, email);
            cout << "You Have Registered Successfully!" << endl;
            break;
        case 2:
            decide = Person.userLogin();
            if (decide)
            {
                loggedIn = true;
                registration = true;
            }
            else
            {
                while (!decide)
                {
                    decide = Person.userLogin();
                }
                loggedIn = true;
                registration = true;
            }
            break;

        case 3:
            Person.displayProfile();
            break;

        case 4:
            Person.displayBalance();
            break;

        case 5:
            Person.withdrawMoney();
            break;

        case 6:
            Person.depositMoney();
            break;

        case 7:
            Person.transactionsHistory();
            break;
        case 8:
            Person.feedback();
            break;

        case 11:
            cout << "Press 1 To Buy Stocks Of Apple!" << endl;
            cout << "Press 2 To Buy Stocks Of Google!" << endl;
            cout << "Press 3 To Buy Stocks Of Samsung!" << endl;
            int companyChoice;
            cin >> companyChoice;
            switch (companyChoice)
            {
                int a;
            case 1:
                cout << "Enter No Of Shares You Want to Buy = ";
                cin >> a;
                User.buyStocks(apple, a);
                break;

            case 2:
                cout << "Enter No Of Shares You Want to Buy = ";
                cin >> a;
                User.buyStocks(google, a);
                break;

            case 3:
                cout << "Enter No Of Shares You Want to Buy = ";
                cin >> a;
                User.buyStocks(samsung, a);
                break;

            default:
                break;
            }
            break;
        case 12:
            exit(0);
            break;
        }
    }
    return 0;
}