#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
class User {
   private:
      std::string userID;
      std::string name;
      std::string email;
      std::vector<std::string> issuedBooksID;
   public:
   
   // Constructor
      User();
      User(std::string, std::string, std::string,std::vector<std::string>);
   // Methods
      std::vector<std::string> getUserInfo();
      void displayUserInfo();

   };



#endif
