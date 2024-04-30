//
// Created by 14472 on 2021/12/25.
//

#ifndef INC_2021_CPP_PROJECT_MANAGER_H
#define INC_2021_CPP_PROJECT_MANAGER_H


#include "User.h"

class Manager : public User {
public:
    Manager();
    Manager(int a, const string& u, int p, double ba, double td, double lip, double lie);

    double getLoanPersonal() const;
    double getLoanEnterprise() const;
    double getBorrowableAmount() const;
    double getTotalDeposits() const;

    bool IsBorrowable(double amount) const;
    void Deposit(double amount);
    void Withdraw(double amount);
    void Loan(double amount);
    void Repay(double amount);

    string printLine();


private:
    double borrowable_amount;
    double total_deposits;
    double loan_interest_personal;
    double loan_interest_enterprise;
};


#endif //INC_2021_CPP_PROJECT_MANAGER_H
