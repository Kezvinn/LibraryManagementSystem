#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>

class Book{
   private:
      std::string bookID;
      std::string title;
      std::string author;
      std::string publisher;
      int total__copies;
      int available_copies;

   public:
   // Constructor
      Book();
      Book(std::string, std::string,std::string, std::string, int, int);

   // Methods
      std::vector<std::string> getBookInfo();
      void displayBookInfo();
      bool isAvailable();
      void borrowBook();
      void returnBook();

};  


#endif