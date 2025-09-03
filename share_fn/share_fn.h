#ifndef SHARE_FN_H
#define SHARE_FN_H

#include <bits/stdc++.h>

#include "../admin/admin.h"
#include "../member/member.h"
#include "../library/library.h"

class Admin;
class Library;
// Support
std::string randID(char);
int getInputInRange(int, int);

// Menu
void mainMenu(Library& lib, Admin* ad, Member* mem);
void memberMenu(Member* mem, Library& lib);
void adminMenu(Admin* ad, Library& lib);

// regex function
bool isValidInt(const std::string &);
bool isValidName(const std::string &input);

#endif