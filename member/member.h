#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>
#include <iostream>

#include "../library/library.h"
#include "../user/user.h"
#include "../share_fn/share_fn.h"

class Library;

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
      void displayMemberInfo();

      std::vector<std::string> getIssuedBookIDs();
      void displayIssuedBookIDs();

      void borrowBook(Library &lib);
      void returnBook(Library &lib);
   
      // bool logout();
      // bool login();
   };



#endif
