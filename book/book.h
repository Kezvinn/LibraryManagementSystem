#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

class Book { 
   private:
      std::string bookID;
      std::string title;
      std::string author;
      std::string publisher;
      int total_copies;
      int available_copies;

   public:
   // Constructor
      Book();
      Book(std::string, std::string, std::string, std::string, int, int);

   // Methods
      std::vector<std::string> getBookInfo();
      void displayBookInfo(char);      // v-> vertical h-> horizontal
      bool isAvailable();
      void borrowBook();
      void returnBook();
   
      // Setter
      int setTitle(std::string);
      int setAuthor(std::string);
      int setPublisher(std::string);
      int setTotalCopies(int);
      int setAvailableCopies(int);

      // Getter
      std::string getBookID();
      std::string getTitle();
      std::string getAuthor();
      std::string getPublisher();
      int getTotalCopies();
      int getAvailableCopies();
};

#endif