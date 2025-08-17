#ifndef SHARE_FN_H
#define SHARE_FN_H

#include <bits/stdc++.h>

#include "../admin/admin.h"
#include "../library/library.h"

// Support
std::string randID(char);
int getInputInRange(int, int);

// Menu
void mainMenu();
void memberMenu(Library&);
void adminMenu(Admin *ad, Library &lib);

// regex func
bool isValidInt(std::string&);
bool isValidName(std::string&);

#endif