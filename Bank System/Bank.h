//
// Created by 14472 on 2021/12/25.
//

#ifndef INC_2021_CPP_PROJECT_BANK_H
#define INC_2021_CPP_PROJECT_BANK_H


#include "Customer.h"
#include "Manager.h"
#include <vector>
#include <fstream>

class Bank {
public:
    Bank();
    Bank(vector<Customer*>& cs, Manager* m, const string& ap, const string& bp);
    void Login();

private:
    vector<Customer*> customers;
    Manager* manager;
    string account_path;
    string bank_path;

    void CustomerInterface(Customer*);
    void ManagerInterface(Manager*);

    void CustomerInquiry(Customer*);
    void CustomerDeposit(Customer*, Manager*);
    void CustomerWithdraw(Customer*, Manager*);
    void CustomerTransfer(Customer*);
    void CustomerLoan(Customer*, Manager*);
    void CustomerRepayment(Customer*, Manager*);
    void CustomerChangePassword(Customer*);

    void CreateAccount();
    void CheckBorrowable();
    void CheckTotalDeposits();
    void CheckInfo();
    void ResetPassword();

    void WriteFile();

    vector<string>split(const string& s);

};


#endif //INC_2021_CPP_PROJECT_BANK_H
