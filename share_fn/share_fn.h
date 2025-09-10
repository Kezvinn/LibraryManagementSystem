#ifndef SHARE_FN_H
#define SHARE_FN_H

#include <bits/stdc++.h>

#include "../admin/admin.h"
#include "../member/member.h"
#include "../library/library.h"

class Admin;
class Library;
class Member;

// Support
std::string randID(char);
int getInputInRange(int, int);

// Menu
void mainMenu(Library& lib, Admin* ad, Member* mem);
void memberMenu(Member* mem, Library& lib, Admin* ad);
void adminMenu(Admin* ad, Library& lib);

// Regex function
bool isValidInt(const std::string &);
bool isValidName(const std::string &);
bool isValidEmail(const std::string &);
bool isValidPassword(const std::string &);

// Display functions
void printBoxCenter(std::string, int);
void printBox(const std::vector<std::string>& titles, const std::vector<std::string>& lines, int width);
std::vector<std::string> splitToChunks(const std::string& s, int width);
void printTable(const std::vector<std::string>& Titles, std::vector<std::vector<std::string>>& Data);

// Prompt functions
bool returnPrompt();

#endif