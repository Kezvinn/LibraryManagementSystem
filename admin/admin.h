# ifndef ADMIN_H
# define ADMIN_H

#include <iostream>

#include "../user/user.h"
#include "../book/book.h"
#include "../library/library.h"
#include "../share_fn/share_fn.h"

class Library;

class Admin : public User {
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
      bool authenticate(Library&, Member&); // ID, Password -> use to verify login from Member
};


# endif