//
// Created by 14472 on 2021/12/25.
//

#include <sstream>
#include <iterator>
#include "Bank.h"

Bank::Bank() {
    this->customers = vector<Customer*>();
    this->manager = nullptr;
}

Bank::Bank(vector<Customer *> &cs, Manager *m, const string& ap, const string& bp) {
    this->customers = cs;
    this->manager = m;
    this->account_path = ap;
    this->bank_path = bp;
}

void Bank::Login() {
    string text;
    try {
        cout << "Please input your account number: ";
        cin >> text;
        int account = stoi(text);
        cout << "Please input you account password: ";
        text = "";
        cin >> text;
        int password = stoi(text);
        bool flag = false;
//        cout << "fff" << endl;
        if (this->manager->login(account, password)) {
            flag = true;
            this->ManagerInterface(this->manager);
        }
//        cout << "fff" << endl;
        for (int i = 0; i < customers.size(); i++) {
            if (this->customers[i]->login(account, password)) {
                flag = true;
                this->CustomerInterface(this->customers[i]);
                break;
            }
        }
        if (!flag) cout << "Error: Account or password not correct" << endl;

    } catch (exception& e) {
        cout << "Error: Input error!" << endl;
    }

}

void Bank::CustomerInterface(Customer* index) {
    while (true) {
        cout << "1. Inquiry" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Transfer" << endl;
        cout << "5. Loan" << endl;
        cout << "6. Repay" << endl;
        cout << "7. Change password" << endl;
        cout << "8. Quit" << endl;
        cout << "Please Select: ";
        string text;
        cin >> text;
        try {
            int number = stoi(text);
            switch (number) {
                case 1:
                    CustomerInquiry(index);
                    break;
                case 2:
                    CustomerDeposit(index, this->manager);
                    break;
                case 3:
                    CustomerWithdraw(index, this->manager);
                    break;
                case 4:
                    CustomerTransfer(index);
                    break;
                case 5:
                    CustomerLoan(index, this->manager);
                    break;
                case 6:
                    CustomerRepayment(index, this->manager);
                    break;
                case 7:
                    CustomerChangePassword(index);
                    break;
                case 8:
                    cout << "Bye" << endl;
                    system("pause");
                    return;
                default:
                    cout << "You can only input digit 1 to 8" << endl;
                    continue;
            }
            cout << "1. Continue" << endl;
            cout << "2. Quit" << endl;
            cout << "Please Select: ";
            text = "";
            cin >> text;
            number = stoi(text);
            switch (number) {
                case 1:
                    break;
                case 2:
                    cout << "Bye" << endl;
                    system("pause");
                    return;
                default:
                    cout << "You can only input digit 1 to 2" << endl;
                    system("pause");
                    return;
            }
        } catch (exception& e) {
            cout << "Error: Input error!" << endl;
            system("pause");
            return;
        }
    }
}

void Bank::ManagerInterface(Manager* index) {
    while (true) {
        cout << "1. Create a new account" << endl;
        cout << "2. Check borrowable amount of bank" << endl;
        cout << "3. Check total_deposits of bank" << endl;
        cout << "4. Check customer's information" << endl;
        cout << "5. Reset password for customer" << endl;
        cout << "6. Quit" << endl;
        cout << "Please Select: ";
        string text;
        cin >> text;
        try {
            int number = stoi(text);
            switch (number) {
                case 1:
                    CreateAccount();
                    break;
                case 2:
                    CheckBorrowable();
                    break;
                case 3:
                    CheckTotalDeposits();
                    break;
                case 4:
                    CheckInfo();
                    break;
                case 5:
                    ResetPassword();
                    break;
                case 6:
                    cout << "Bye" << endl;
                    system("pause");
                    return;
                default:
                    cout << "You can only input digit 1 to 6" << endl;
                    continue;
            }
            cout << "1. Continue" << endl;
            cout << "2. Quit" << endl;
            cout << "Please Select: ";
            text = "";
            cin >> text;
            number = stoi(text);
            switch (number) {
                case 1:
                    break;
                case 2:
                    cout << "Bye" << endl;
                    system("pause");
                    return;
                default:
                    cout << "You can only input digit 1 to 2" << endl;
                    system("pause");
                    return;
            }
        } catch (exception& e) {
            cout << "Error: Input error!" << endl;
            system("pause");
            return;
        }
    }
}

void Bank::CustomerInquiry(Customer *c) {
    c->Inquiry();
}

void Bank::CustomerDeposit(Customer *c, Manager *m) {
    try {
        string text;
        cout << "Please input the amount to save: ";
        text = "";
        cin >> text;
        double amount = stof(text);
        if (c->Deposit(amount)){
            m->Deposit(amount);
            this->WriteFile();
        }
    } catch (exception& e) {
        cout << "Error: Input error!" << endl;
    }
}

void Bank::CustomerWithdraw(Customer *c, Manager *m) {
    try {
        string text;
        cout << "Please input the amount to withdraw: ";
        text = "";
        cin >> text;
        double amount = stof(text);
        if (c->Withdraw(amount)){
            m->Withdraw(amount);
            this->WriteFile();
        }
    } catch (exception& e) {
        cout << "Error: Input error!" << endl;
    }
}

void Bank::CustomerTransfer(Customer *c) {
    try {
        string text;
        cout << "Please input the amount to withdraw: ";
        text = "";
        cin >> text;
        int account = stoi(text);
        Customer *other = nullptr;
        for (auto & customer : customers) {
            if (customer->getAccount() == account) {
                other = customer;
                break;
            }
        }
        if (other == c || other == nullptr) {
            cout << "Error: Invalid account" << endl;
            return;
        }
        text = "";
        cout << "Please input the amount to transfer: ";
        cin >> text;
        double amount = stod(text);
        if(c->Transfer(other, amount)) this->WriteFile();;

    } catch (exception& e) {
        cout << "Error: Input error!" << endl;
    }
}

void Bank::CustomerLoan(Customer *c, Manager *m) {
    try {
        string text;
        cout << "Please input the amount to loan: ";
        text = "";
        cin >> text;
        double amount = stod(text);
        if (m->IsBorrowable(amount)) {
            if (c->Loan(amount)) {
                m->Loan(amount);
                this->WriteFile();
            };
        } else cout << "Sorry, bank borrowable money insufficient" << endl;

    } catch (exception& e) {
        cout << "Error: Input error!" << endl;
    }
}

void Bank::CustomerRepayment(Customer *c, Manager *m) {
    try {
        double interest;
        if (c->getCategory() == "personal") interest = m->getLoanPersonal();
        else interest = m->getLoanEnterprise();
        double amount;
        if((amount = c->Repayment(interest)) != -1){
            m->Repay(amount * (1 + interest));
            m->Withdraw(amount);
            this->WriteFile();
        }
    } catch (exception& e) {
        cout << "Error: Input error!" << endl;
    }
}

void Bank::CustomerChangePassword(Customer *c) {
    try {
        string text;
        cout << "Please input your original password: ";
        text = "";
        cin >> text;
        int old_password = stoi(text);
        cout << "Please input your new password: ";
        text = "";
        cin >> text;
        int new_password = stoi(text);
        cout << "Please input your new password again: ";
        text = "";
        cin >> text;
        int confirm = stoi(text);
        if (confirm != new_password) {
            cout << "Error: Password and confirm are not same" << endl;
            return;
        }
        if (new_password / 100000 < 1 || new_password / 100000 > 9) {
            cout << "Error: Invalid password" << endl;
            return;
        }
        if (old_password != c->getPassword()) {
            cout << "Error: Original password is incorrect" << endl;
            return;
        }
        c->ChangePassword(new_password);
        this->WriteFile();
    } catch (exception& e) {
        cout << "Error: Input error!" << endl;
    }
}

void Bank::CheckBorrowable() {
    cout << "The borrowable amount: " << this->manager->getBorrowableAmount() << endl;
}

void Bank::CheckTotalDeposits() {
    cout << "The total deposits amount now is: " << this->manager->getTotalDeposits() << endl;
}

void Bank::CheckInfo() {
    try {
        cout << "Please input the account number: ";
        string text;
        cin >> text;
        int account = stoi(text);
        bool flag = false;
        for (auto & customer : customers) {
            if (customer->getAccount() == account) {
                customer->print();
                flag = true;
                break;
            }
        }
        if (!flag) {
            cout << "Error: Invalid account" << endl;
        }
    } catch (exception& e) {
        cout << "Error: Input error!" << endl;
    }
}

void Bank::ResetPassword() {
    try {
        cout << "Please input the account number: ";
        string text;
        cin >> text;
        int account = stoi(text);
        bool flag = false;
        for (auto & customer : customers) {
            if (customer->getAccount() == account) {
                CustomerChangePassword(customer);
                flag = true;
                break;
            }
        }
        if (!flag) {
            cout << "Error: Invalid account" << endl;
        }
    } catch (exception& e) {
        cout << "Error: Input error!" << endl;
    }
}

void Bank::CreateAccount() {
    try {
        cout << "Please input a customer information" << endl;
        cout << "(name password withdrawable category)" << endl;
        string text;
        cin.clear(); cin.sync();
        getline(cin, text);
        int account = 1000;
        for (auto & customer : customers) {
            account = max(account, customer->getAccount());
        }
        account++;
        vector<string>ss = this->split(text);
//        for(auto s : ss) {
//            cout << s << endl;
//        }
        if (ss.size() != 4) {
            cout << "Error: Input error!" << endl;
            return;
        }
        string username = ss[0];
        int password = stoi(ss[1]);
        double withdrawable = stod(ss[2]);
        string category = ss[3];
        if (category != "personal" && category != "enterprise") {
            cout << "Error: Invalid Category!" << endl;
            return;
        }
        if (password / 100000 < 1 || password / 100000 > 9) {
            cout << "Error: Invalid password" << endl;
            return;
        }
//        cout << "ffff" << endl;
        auto* new_customer = new Customer(account, username, password,
                                          withdrawable, category, 0,
                                          category == "personal"? 20000 : 50000, withdrawable);
        customers.push_back(new_customer);
        this->WriteFile();
    } catch (exception& e) {
        cout << "Error: Input error!" << endl;
//        cout << "what fuck" << endl;
    }
}

void Bank::WriteFile() {
//    cout << "Write start" << endl;
    ofstream account_file;
    account_file.open(this->account_path);
    account_file << "account    name    password    withdrawable"
                    "    category    loan_amount    loan_quota_left    net_value\n";
    for (auto & customer : customers) {
        account_file << customer->printLine() << "\n";
    }
    account_file.close();
    ofstream bank_file;
    bank_file.open(this->bank_path);
    bank_file << "account    name    password    borrowable_amount"
                 "    total_deposits    loan_interest_personal    loan_interest_enterprise\n";
    bank_file << manager->printLine() << "\n";
    bank_file.close();
//    cout << "Write success" << endl;
}

vector<string> Bank::split(const string &s) {

    stringstream ss(s);
    istream_iterator<std::string> begin(ss);
    istream_iterator<std::string> end;
    vector<string>ans(begin, end);
//    std::copy(ans.begin(), ans.end(), ostream_iterator<string>(cout, "\n"));
    return ans;
}

