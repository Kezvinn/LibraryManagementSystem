# ifndef ADMIN_H
# define ADMIN_H

#include "../user/user.h"
#include "../book/book.h"
#include "../library/library.h"
#include "../share_fn/share_fn.h"

#include <iostream>

class Admin : public User {
   private:

   public:
   // Constructor
      Admin();
      Admin(std::string,std::string);
   // Methods
      void addUser();
      void removeUser();
      void viewAllUsers();

      int addBook(Library&);
      int removeBook(Library&);
      void editBookInfo(Library&);
      void viewAllBooks(Library&);
      
      int logout();
      bool login();



};


# endif