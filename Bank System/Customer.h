//
// Created by 14472 on 2021/12/25.
//

#ifndef INC_2021_CPP_PROJECT_CUSTOMER_H
#define INC_2021_CPP_PROJECT_CUSTOMER_H


#include "User.h"

class Customer : public User {
public:
    Customer();
    Customer(int a, const string& u, int p, double w, const string& c, double la, double lql, double nv);

    bool Inquiry();
    bool Deposit(double amount);
    bool Withdraw(double amount);
    bool Transfer(Customer* other, double amount);
    bool Loan(double amount);
    double Repayment(double loan_interest);
    bool ChangePassword(int new_password);
    void print();
    string printLine();

    int getAccount() const;
    string getCategory() const;
    int getPassword() const;


private:
    double withdrawable;
    string category;
    double loan_amount;
    double loan_quota_left;
    double net_value;
};


#endif //INC_2021_CPP_PROJECT_CUSTOMER_H
