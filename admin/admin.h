# ifndef ADMIN_H
# define ADMIN_H

#include "../user/user.h"
#include "../book/book.h"

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

      void addBook();
      void removeBook();
      void editBookInfo();
      void viewAllBooks();


};


# endif