//
// Created by 14472 on 2021/12/25.
//

#ifndef INC_2021_CPP_PROJECT_USER_H
#define INC_2021_CPP_PROJECT_USER_H

#include <iostream>

using namespace std;

class User {
public:
    User();
    User(int a, const string& u, int p);
    bool login(int a, int p) const;
protected:
    int account;
    string username;
    int password;
};


#endif //INC_2021_CPP_PROJECT_USER_H
