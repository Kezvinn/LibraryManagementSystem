#ifndef LIBRARY_H
#define LIBRARY_H

#include "./user/user.h"
#include "./book/book.h"


class Library {
   private:
      std::vector<User*> users;
      std::vector<Book*> books;
   public:

};


#endif