//
// Created by 14472 on 2021/12/25.
//

#include "Manager.h"

Manager::Manager() : User() {
    this->borrowable_amount = 0;
    this->total_deposits = 0;
    this->loan_interest_personal = 0;
    this->loan_interest_enterprise = 0;
}

Manager::Manager(int a, const string &u, int p, double ba, double td, double lip, double lie) : User(a, u, p) {
    this->borrowable_amount = ba;
    this->total_deposits = td;
    this->loan_interest_personal = lip;
    this->loan_interest_enterprise = lie;
}

double Manager::getLoanPersonal() const {
    return this->loan_interest_personal;
}

double Manager::getLoanEnterprise() const {
    return this->loan_interest_enterprise;
}

bool Manager::IsBorrowable(double amount) const {
    return amount <= this->borrowable_amount;
}

void Manager::Deposit(double amount) {
    this->total_deposits += amount;
}

void Manager::Withdraw(double amount) {
    this->total_deposits -= amount;
}

void Manager::Loan(double amount) {
    this->borrowable_amount -= amount;
}

void Manager::Repay(double amount) {
    this->borrowable_amount += amount;
}

double Manager::getBorrowableAmount() const {
    return this->borrowable_amount;
}

double Manager::getTotalDeposits() const {
    return this->total_deposits;
}

string Manager::printLine() {
    string ss = to_string(this->account)
                + "    " + this->username
                + "    " + to_string(this->password)
                + "    " + to_string(this->borrowable_amount)
                + "    " + to_string(this->total_deposits)
                + "    " + to_string(this->loan_interest_personal)
                + "    " + to_string(this->loan_interest_enterprise);
    return ss;
}


