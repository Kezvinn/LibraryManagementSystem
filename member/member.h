#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>
#include <iostream>

#include "../user/user.h"

class Member : public User {
   private:
      std::string userID;
      std::string name;
      std::string email;
      std::vector<std::string> issuedBooksID;
   public:
   
   // Constructor
      Member();
      Member(std::string, std::string, std::string, std::string, std::vector<std::string>); // ->load from file
      Member(std::string, std::string, std::string, std::string); // -> new member
      
   // Methods
      std::vector<std::string> getUserInfo();
      void displayUserInfo();

      std::vector<std::string> getIssuedBookIDs();
      void displayIssuedBookIDs();

      void borrowBook();
      void returnBook();
   
      int logout();
      bool login();
   };



#endif
