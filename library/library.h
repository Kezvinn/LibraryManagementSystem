#ifndef LIBRARY_H
#define LIBRARY_H

#include <fstream>
#include <vector>
#include <algorithm>

#include "../book/book.h"
#include "../member/member.h"

#define MEMBERS_DATA "./data/members.txt"
#define BOOKS_DATA "./data/books.txt"

class Member;
class Book;

class Library {
   private:
      std::vector<Member*> members_vt;
      std::vector<Book*> books_vt;
   public:
      Library();
      Library(std::vector<Member*>, std::vector<Book*>);
   
   // File Handling
      int loadFromFile();  // load user and book
      int saveToFile();    // save user and book
   
   // Getter
      std::vector<Member*> getMembers() const;
      std::vector<Book*> getBooks() const;
   
   // Books Methods
      Book* searchBookByTitle(std::string);  // Title 
      Book* searchBookByAuthor(std::string); // Author
      Book* findBookByID(std::string);     // Book ID   
   
   // Member Methods
      Member* findUserByID(std::string);
   
      // Add & Remove
      bool addBook(Book*);
      bool addMember(Member*);

      bool removeBook(std::string); // Book ID
      bool removeMember(std::string); // User ID
};

#endif