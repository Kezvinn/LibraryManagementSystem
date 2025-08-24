#include "member.h"

// Constructors
Member::Member(){}
Member::Member(std::string userID_i, std::string pwd_i, 
               std::string name_i, std::string email_i, 
               std::vector<std::string> issueBooks_i):
               User(userID_i,pwd_i), userID(userID_i), 
               name(name_i), email(email_i), issuedBooksID(issueBooks_i){}
Member::Member(std::string userID_i, std::string pwd_i, 
               std::string name_i, std::string email_i):
               User(userID_i, pwd_i), userID(userID_i),
               name(name_i), email(email_i){}

std::vector<std::string> Member::getUserInfo(){
   std::vector<std::string> userInfo;

   userInfo.push_back(this->userID);
   userInfo.push_back(this->getPassword());
   userInfo.push_back(this->name);
   userInfo.push_back(this->email);
   std::string issuedBooksStr;
   for (auto item : this->issuedBooksID){
      issuedBooksStr += item + " ";
   }
   userInfo.push_back(issuedBooksStr);
   
   return userInfo;
}

std::vector<std::string> Member::getIssuedBookIDs(){
   return this->issuedBooksID;
}

bool Member::login(){
   std::string username, password;
   std::cout << "+" << std::string(30, '-') << "+\n";
   std::cout << "\tMember Login\t";
   std::cout << "+" << std::string(30, '-') << "+\n";

   std::cout << "Enter Username: ";
   std::getline(std::cin, username);
   std::cout << "Enter Password: ";
   std::getline(std::cin, password);

   if (username == this->getUsername() && password == this->getPassword()){
      std::cout << "Login successful!\n";
      return true;
   } else {
      std::cout << "Login failed! Incorrect username or password.\n";
      return false;
   }
}
