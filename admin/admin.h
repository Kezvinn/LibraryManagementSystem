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
      int addMember(Library&);
      int removeMember(Library&);
      int viewAllMembers(Library&);

      int addBook(Library&);
      int removeBook(Library&);
      int editBookInfo(Library&);
      int viewAllBooks(Library&);
      
      // int logout();
      bool login();
};


# endif