#ifndef LIBRARY_H
#define LIBRARY_H

#include "./user/user.h"
#include "./book/book.h"
#include "../member/member.h"

class Library {
   private:
      std::vector<User*> users;
      std::vector<Book*> books;
   public:


   // Methods
      int loadFromFile();  // load user and book
      int saveToFile();
      Book searchBookByTitle(std::string);
      Book searchBookByAuthor(std::string);
      Member findUserByID(std::string);

};


#endif