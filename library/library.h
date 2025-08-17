#ifndef LIBRARY_H
#define LIBRARY_H

#include "../book/book.h"
#include "../member/member.h"

#include <fstream>

#define MEMBERS_DATA "../data/members.txt"
#define BOOKS_DATA "../data/books.txt"
class Library {
   private:
      std::vector<Member*> members_vt;
      std::vector<Book*> books_vt;
   public:
      Library();
      Library(std::vector<Member*>, std::vector<Book*>);

   // Methods
      // File Handling
      int loadFromFile();  // load user and book
      int saveToFile();

      Book* searchBookByTitle(std::string);
      Book* searchBookByAuthor(std::string);
      
      Member findUserByID(std::string);

      int addBook(Book*);
      int addMember(Member*);
};


#endif