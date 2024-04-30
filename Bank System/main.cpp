#include <iostream>
#include "Customer.h"
#include "Manager.h"
#include "Bank.h"

#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;

vector<string>split(const string& s){
    stringstream ss(s);
    istream_iterator<std::string> begin(ss);
    istream_iterator<std::string> end;
    vector<string>ans(begin, end);
//    std::copy(ans.begin(), ans.end(), ostream_iterator<string>(cout, "\n"));
    return ans;
}

void readFile(const string& account_path, const string& bank_path, vector<Customer*>& customer_list, Manager** manager) {
    ifstream account_file;
    account_file.open(account_path);
    string line;
    getline(account_file, line);
    while (getline(account_file, line)) {
        vector<string> ss = split(line);
        int account = stoi(ss[0]);
        string username = ss[1];
        int password = stoi(ss[2]);
        double withdrawable = stod(ss[3]);
        string category = ss[4];
        double loan_amount = stod(ss[5]);
        double loan_quota_left = stod(ss[6]);
        double net_value = stod(ss[7]);
        auto* new_customer = new Customer(account, username, password, withdrawable,
                                          category, loan_amount, loan_quota_left, net_value);
        customer_list.push_back(new_customer);
    }
    account_file.close();

    ifstream bank_file;
    bank_file.open(bank_path);
    getline(bank_file, line);
    getline(bank_file, line);
    vector<string> ss = split(line);
    int account = stoi(ss[0]);
    string username = ss[1];
    int password = stoi(ss[2]);
    double borrowable_amount = stod(ss[3]);
    double total_deposits = stod(ss[4]);
    double loan_interest_personal = stod(ss[5]);
    double loan_interest_enterprise = stod(ss[6]);

    *manager = new Manager(account, username, password, borrowable_amount,
                           total_deposits, loan_interest_personal, loan_interest_enterprise);
    bank_file.close();
}


int main() {
    string bank_file = "./bank.txt";
    string account_file = "./account.txt";
//    auto* c1 = new Customer(1001, "Alice", 123456,
//                            100000.23, "personal", 0, 20000, 100000.23);
//    auto* c2 = new Customer(1002, "Naruto", 654321,
//                            101000.23  , "enterprise", 1000, 49000, 100000.23);
//    vector<Customer*>cs = vector<Customer*>();
//    cs.push_back(c1);
//    cs.push_back(c2);
//    auto* m = new Manager(1000, "manager", 123456, 10000000, 200000.46, 0.05, 0.03);
    vector<Customer*>customer_list;
    Manager* manager = nullptr;
    readFile(account_file, bank_file, customer_list, &manager);
    auto* bank = new Bank(customer_list, manager, account_file, bank_file);
    bank->Login();

    return 0;

    return 0;
}
