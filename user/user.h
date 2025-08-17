#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
   private:
      std::string username;
      std::string password;
   public:
   // Constructor
      User();
      User(std::string,std::string);

   // Methods
      std::string getUsername();
      std::string getPassword();
   };

#endif
