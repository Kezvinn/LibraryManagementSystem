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
      std::string getMemberID();
      std::string getName();
      std::string getEmail();
   
   // Setters 
      int setIssueBooksIDs(std::vector<std::string>);
      int setName(std::string);
      int setEmail(std::string);
      int setPassword(std::string);

   // Display
      void displayIssuedBookIDs();
      void displayMemberInfo();

   // Methods
      int borrowBook(Library &lib);
      int returnBook(Library &lib);
      int editMemberInfo(Library &lib); // edit name, email, password
      bool logout(Library &lib); // save current member information into library data
   };

#endif
