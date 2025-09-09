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
   
   // Getters
      std::vector<std::string> getMemberInfo();   // get all 
      std::vector<std::string> getIssuedBookIDs();
      std::string getUserID();
      std::string getName();
      std::string getEmail();
   
   // Setters 
      int setIssueBooksIDs(std::vector<std::string>);
   
   // Display
      void displayIssuedBookIDs();
      void displayMemberInfo();
   // Methods
      void borrowBook(Library &lib);
      void returnBook(Library &lib);
      bool logout(Library &lib); // save current member infor into library data
   };

#endif
