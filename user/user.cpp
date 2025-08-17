#include "user.h"

// Constructor
User::User(){}
User::User(std::string usrname, std::string pwd):username(usrname), password(pwd){}

std::string User::getUsername(){
   return this->username;
}
std::string User::getPassword(){
   return this->password;
}

