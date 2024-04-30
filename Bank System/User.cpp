//
// Created by 14472 on 2021/12/25.
//

#include "User.h"

#include <utility>

User::User() {
    this->account = 0;
    this->username = "";
    this->password = 0;
}

User::User(int a, const string& u, int p) {
    this->account = a;
    this->username = u;
    this->password = p;
}

bool User::login(int a, int p) const {
    if (this->account == a && this->password == p) {
        return true;
    } else return false;
}

