//
// Created by 14472 on 2021/12/25.
//

#include "Customer.h"

Customer::Customer() : User() {
    this->withdrawable = 0;
    this->category = "";
    this->loan_amount = 0;
    this->loan_quota_left = 0;
    this->net_value = 0;
}

Customer::Customer(int a, const string& u, int p, double w, const string& c, double la, double lql, double nv)
        : User(a, u, p) {
    this->withdrawable = w;
    this->category = c;
    this->loan_amount = la;
    this->loan_quota_left = lql;
    this->net_value = nv;
}

bool Customer::Inquiry() {
    cout << "Dear " << this->username << ", your balance is " << this->withdrawable << endl;
    return true;
}

bool Customer::Deposit(double amount) {
    this->withdrawable += amount;
    this->net_value = this->withdrawable - this->loan_amount;
    cout << "Dear " << this->username << ",  your balance has been updated to " << this->withdrawable << endl;
    return true;
}

bool Customer::Withdraw(double amount) {
    if ((this->category == "personal" && amount > 2000) ||
        (this->category == "enterprise" && amount > 5000)) {
        cout << "Warning: withdraw amount is too high" << endl;
        return false;
    }
    if (this->withdrawable < amount) {
        cout << "Warning: insufficient withdrawable";
        return false;
    } else {
        this->withdrawable -= amount;
        this->net_value = this->withdrawable - this->loan_amount;
        cout << "Dear " << this->username << ",  your balance has been updated to " << this->withdrawable << endl;
        return true;
    }
}

bool Customer::Transfer(Customer *other, double amount) {
    if (this->withdrawable < amount) {
        cout << "Warning: insufficient withdrawable";
        return false;
    } else {
        this->withdrawable -= amount;
        other->withdrawable += amount;
        this->net_value = this->withdrawable - this->loan_amount;
        other->net_value = other->withdrawable - other->loan_amount;
        cout << "Transfer success! Your withdrawable amount has been updated to " << this->withdrawable << endl;
        return true;
    }
}

bool Customer::Loan(double amount) {
    if (amount > this->loan_quota_left) {
        cout << "Warning: insufficient loan quota left" << endl;
        return false;
    } else {
        this->withdrawable += amount;
        this->loan_quota_left -= amount;
        this->loan_amount += amount;
        this->net_value = this->withdrawable - this->loan_amount;
        cout << "Your loan quota left is " << this->loan_quota_left << endl;
        return true;
    }
}

double Customer::Repayment(double loan_interest) {
    if (this->loan_amount * (loan_interest + 1) > this->withdrawable) {
        cout << "Warning: insufficient withdrawable" << endl;
        return -1;
    } else {
        double amount = this->loan_amount;
        this->withdrawable -= this->loan_amount * (loan_interest + 1);
        this->loan_quota_left += this->loan_amount;
        this->loan_amount = 0;
        this->net_value = this->withdrawable - this->loan_amount;
        cout << "Cheers! Your loan amount now is " << this->loan_amount << ". Your loan quota now is " << this->loan_quota_left << endl;
        cout << "Your withdrawable amount has been updated to " << this->withdrawable << endl;
        return amount;
    }
}

bool Customer::ChangePassword(int new_password) {
    this->password = new_password;
    cout << "Update password successfully." << endl;
    return true;
}

void Customer::print() {
    cout << "account: " << this->account << endl;
    cout << "username: " << this->username << endl;
    cout << "password: " << this->password << endl;
    cout << "withdrawable: " << this->withdrawable << endl;
    cout << "category: " << this->category << endl;
    cout << "loan_amount: " << this->loan_amount << endl;
    cout << "loan_quota_left: " << this->loan_quota_left << endl;
    cout << "net_value: " << this->net_value << endl;
}

int Customer::getAccount() const {
    return this->account;
}

string Customer::getCategory() const {
    return this->category;
}

int Customer::getPassword() const {
    return this->password;
}

string Customer::printLine() {
    string ss = to_string(this->account)
                + "    " + this->username
                + "    " + to_string(this->password)
                + "    " + to_string(this->withdrawable)
                + "    " + this->category
                + "    " + to_string(this->loan_amount)
                + "    " + to_string(this->loan_quota_left)
                + "    " + to_string(net_value);
    return ss;
}











