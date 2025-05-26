#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <conio.h>
#include <limits>

using namespace std;

class Account {
private:
    string account_holder[5]; //List of account owners details: (0) Full Name, (1) Phone Number, (2) Address, (3) DOB, (4) Date of Creation
    int acc_number;
    int acc_type;
    double balance = 0;
    double w_limit;
    double c_limit;

public:
    Account(string fn, string pn, string a, string dob, string doc, int an, int t, double wl, double cl) {
        account_holder[0] = fn;
        account_holder[1] = pn;
        account_holder[2] = a;
        account_holder[3] = dob;
        account_holder[4] = doc;
        acc_number = an;
        acc_type = t;
        w_limit = wl;
        c_limit = cl;
    }

    string request_acc_details(int i) {
        return account_holder[i];
    }

    int request_acc_number() {
        return acc_number;
    }

    string request_acc_type_s() {
        if (acc_type == 0) return "Debit";
        return "Credit";
    }

    int request_acc_type() {
        return acc_type;
    }

    double request_wlimit() {
        return w_limit;
    }

    double request_climit() {
        return c_limit;
    }

    void deposit(double money) {
        balance += money;
    }

    void withdraw(double money) {
        balance -= money;
    }

    double view_bal() {
        return balance;
    }

    bool check_credit(double amount) {
        double newbal = balance - amount;
        if (newbal < -c_limit) return false;
        return true;
    }

};

int num = -1;
vector<Account> accounts;

Account open_account() {
    string fn, pn, a, dob, doc, t;
    int an, intt;
    double wl = 2000;
    double cl = 0;

    cout << "Enter your Full Name: ";
    getline(cin, fn);
    cout << endl;

    cout << "Enter your phone number: ";
    getline(cin, pn);
    cout << endl;

    cout << "Enter your current address: ";
    getline(cin, a);
    cout << endl;

    cout << "Enter your date of birth: ";
    getline(cin, dob);
    cout << endl;

    time_t now = time(0);
    doc = ctime(&now);

    cout << "What type of account would you like to open: " << endl << "(0) Debit" << endl << "(1) Credit" << endl;
    getline(cin, t);
    cout << endl;
    while (t != "0" && t != "1") {
        cout << "Please select '0' or '1' out of the following options: " << endl << "(0) Debit" << endl << "(1) Credit" << endl;
        getline(cin, t);
        cout << endl;
    }

    intt = stoi(t);

    if (t == "1") {
        cout << "Please provide your monthly income: ";
        cin >> cl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
        cl = cl/10;
        cout << "Your monthly credit limit is: " << cl << endl;
    }

    num += 1;
    an = num;
    cout << "Congratulations your account has been successfully opened." << endl << endl << "Your account number is: " << an << endl << "Please take note of this." << endl << endl << "Thank you for choosing us." << endl << endl;
    return Account(fn,pn,a,dob,doc,an,intt,wl,cl);

}

bool switcher;

void UI(int acc_num) {
    string schoice;
    int ichoice;
    if (accounts[acc_num].request_acc_type() == 0) {
        cout << "Select an option:" << endl << "(1) View Balance" << endl << "(2) Deposit" << endl << "(3) Withdraw" << endl << "(4) Account details" << endl << "(5) Open a new account" << endl << "(6) View a different account" << endl;
        cin >> ichoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
        while (ichoice != 1 && ichoice != 2 && ichoice != 3 && ichoice != 4 && ichoice != 5 && ichoice != 6) {
            cout << "Invalid choice. Please choose one of the listed options." << endl;
            cout << "Select an option:" << endl << "(1) View Balance" << endl << "(2) Deposit" << endl << "(3) Withdraw" << endl << "(4) Account details" << endl << "(5) Open a new account" << endl << "(6) View a different account" << endl;
            cin >> ichoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
        }
        switch(ichoice) {
            case 1:
                cout << "Your current balance is: " << accounts[acc_num].view_bal() << endl << endl;
                break;
            case 2:
                double damount;
                cout << "Enter how much you would like to deposit: ";
                cin >> damount;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                accounts[acc_num].deposit(damount);
                cout << "Your new balance is: " << accounts[acc_num].view_bal() << endl << endl;
                break;
            case 3:
                if (accounts[acc_num].view_bal() == 0) {
                    cout << "Unable to withdraw as your balance is 0." << endl;
                    break;
                }
                double wamount;
                cout << "Enter how much you would like to withdraw: ";
                cin >> wamount;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (wamount > accounts[acc_num].view_bal()) {
                    cout << "Unable to withdraw due to insufficient funds" << endl;
                    break;
                }
                accounts[acc_num].withdraw(wamount);
                cout << "Your new balance is: " << accounts[acc_num].view_bal() << endl << endl;
                break;
            case 4:
                cout << "Full Name: " << accounts[acc_num].request_acc_details(0) << endl << "Phone Number: " << accounts[acc_num].request_acc_details(1) << endl << "Address: " << accounts[acc_num].request_acc_details(2) << endl << "Date of Birth: " << accounts[acc_num].request_acc_details(3) << endl << "Date of Account Creation: " << accounts[acc_num].request_acc_details(4) << endl << endl << "Account Type: " << accounts[acc_num].request_acc_type_s() << endl << "Daily Withdrawal Limit: " << accounts[acc_num].request_wlimit() << endl << endl;
                break;
            case 5:
                accounts.push_back(open_account());
                cout << "Would you like to view your new account? (Y/N): ";
                getline(cin, schoice);
                cout << endl << endl;
                while (schoice != "Y" && schoice != "N") {
                    cout << "Would you like to view your new account? (Y/N): ";
                    getline(cin, schoice);
                    cout << endl << endl;
                }
                if (schoice == "Y") switcher = false;
                break;
            case 6:
                switcher = false;
                break;
        }
    } else {
        cout << "Select an option:" << endl << "(1) View Balance" << endl << "(2) Pay Bill" << endl << "(3) Withdraw" << endl << "(4) Account details" << endl << "(5) Open a new account" << endl << "(6) View a different account" << endl;
        cin >> ichoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
        while (ichoice != 1 && ichoice != 2 && ichoice != 3 && ichoice != 4 && ichoice != 5 && ichoice != 6) {
            cout << "Invalid choice. Please choose one of the listed options." << endl;
            cout << "Select an option:" << endl << "(1) View Balance" << endl << "(2) Pay Bill" << endl << "(3) Withdraw" << endl << "(4) Account details" << endl << "(5) Open a new account" << endl << "(6) View a different account" << endl;
            cin >> ichoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
        }
        switch(ichoice) {
            case 1:
                cout << "Your current balance is: " << accounts[acc_num].view_bal() << endl << endl;
                break;
            case 2:
                if (accounts[acc_num].view_bal() == 0) {
                    cout << "You have nothing left to pay." << endl;
                    break;
                }
                double damount;
                cout << "Your current credit balance is: " << accounts[acc_num].view_bal() << endl;
                cout << "Enter the amount you would like to pay: ";
                cin >> damount;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (damount > -accounts[acc_num].view_bal()) {
                    cout << "This amount is more than your current bill." << endl;
                    break;
                }
                accounts[acc_num].deposit(damount);
                cout << "Your new balance is: " << accounts[acc_num].view_bal() << endl << endl;
                break;
            case 3:
                if (accounts[acc_num].view_bal() == -accounts[acc_num].request_climit()) {
                    cout << "Cannot withdraw as you have met your credit limit for this month" << endl;
                    break;
                }
                double wamount;
                cout << "Enter how much you would like to withdraw: ";
                cin >> wamount;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (!accounts[acc_num].check_credit(wamount)) {
                    cout << "Unable to withdraw as this exceeds your credit limit for this month." << endl;
                    break;
                }
                accounts[acc_num].withdraw(wamount);
                cout << "Your new balance is: " << accounts[acc_num].view_bal() << endl << endl;
                break;
            case 4:
                cout << "Full Name: " << accounts[acc_num].request_acc_details(0) << endl << "Phone Number: " << accounts[acc_num].request_acc_details(1) << endl << "Address: " << accounts[acc_num].request_acc_details(2) << endl << "Date of Birth: " << accounts[acc_num].request_acc_details(3) << endl << "Date of Account Creation: " << accounts[acc_num].request_acc_details(4) << endl << endl << "Account Type: " << accounts[acc_num].request_acc_type_s() << endl << "Daily Withdrawal Limit: " << accounts[acc_num].request_wlimit() << endl << "Monthly Credit Limit: " << accounts[acc_num].request_climit() << endl << endl;
                break;
            case 5:
                accounts.push_back(open_account());
                cout << "Would you like to view your new account? (Y/N): ";
                getline(cin, schoice);
                cout << endl << endl;
                while (schoice != "Y" && schoice != "N") {
                    cout << "Would you like to view your new account? (Y/N): ";
                    getline(cin, schoice);
                    cout << endl << endl;
                }
                if (schoice == "Y") switcher = false;
                break;
            case 6:
                switcher = false;
                break;
        }
    }
}

void find_account() {
    switcher = true;
    int ichoice;
    cout << "Please enter your account number: ";
    cin >> ichoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl;
    while (ichoice >= accounts.size()) {
        cout << "Account does not exist. Please enter a valid account number: ";
        cin >> ichoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
    }
    while (switcher) {
        UI(ichoice);
    }
}

int main()
{
    string choice;

    cout << "Would you like to open an account (Y/N) : ";
    getline(cin, choice);
    cout << endl;
    while(choice != "Y") {
        cout << "Would you like to open an account (Y/N) : ";
        getline(cin, choice);
        cout << endl;
    }
    accounts.push_back(open_account());

    while(true) {
        find_account();
    }

    return 0;
}
