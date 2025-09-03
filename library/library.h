#ifndef LIBRARY_H
#define LIBRARY_H

#include "../book/book.h"
#include "../member/member.h"

#include <fstream>
#include <vector>
#include <algorithm>
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

      std::vector<Member*> getMembers() const;
      std::vector<Book*> getBooks() const;

      Book* searchBookByTitle(std::string);  // Title 
      Book* searchBookByAuthor(std::string); // Author
      
      Member* findUserByID(std::string);

      bool addBook(Book*);
      bool addMember(Member*);

      bool removeBook(std::string); // Book ID
      bool removeMember(std::string); // User ID
};


#endif