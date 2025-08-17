#include "admin.h"

Admin::Admin(){}
Admin::Admin(std::string adname="admin", std::string adpwd="admin123"):User(adname, adpwd){}

int Admin::addBook(Library &lib){
   std::cout << "+" << std::string(50, '-') << "+\n";
   std::cout << "\tAdd Book\t";
   std::cout << "+" << std::string(50, '-') << "+\n";
   std::string data;
   std::string booktitle, bookauthor, bookpublisher;
   std::string temp;
   int tt_copies, avail_copies;

   do {
      std::cout << "Enter Book Title: ";
      std::getline(std::cin, booktitle);
      if (!isValidName(booktitle)) {
         std::cout << "Invalid input! Please enter a valid Title using letters, digits, spaces, or allowed characters only.\n";
      }
   } while(!isValidName(booktitle));

   do {
      std::cout << "Enter Book Author: ";
      std::getline(std::cin, bookauthor);
      if (!isValidName(bookauthor)) {
         std::cout << "Invalid input! Please enter a valid Author using letters, digits, spaces, or allowed characters only.\n";
      }
   } while (!isValidName(bookauthor));
   do {
      std::cout << "Enter Book Publisher: ";
      std::getline(std::cin, bookpublisher);
      if (!isValidName(bookpublisher)) {
         std::cout << "Invalid input! Please enter a valid Publisher using letters, digits, spaces, or allowed characters only.\n";
      }
   } while (!isValidName(bookpublisher));

   do {
      std::cout << "Enter Total Copies: ";
      std::getline(std::cin, temp);
   } while(!isValidInt(temp));

   tt_copies = std::stoi(temp);
   avail_copies = tt_copies;
   temp = randID('B');
   
   Book *newbook = new Book(temp, booktitle, bookauthor, bookpublisher, tt_copies, avail_copies);
   // Book newbook(temp, booktitle, bookauthor, bookpublisher, tt_copies, avail_copies);
   lib.addBook(newbook);
   return 0;
}
int Admin::removeBook(Library &lib){
   std::cout << "+" << std::string(50, '-') << "+\n";
   std::cout << "\tRemove Book\t";
   std::cout << "+" << std::string(50, '-') << "+\n";
   std::string bookID;

   std::cout << "Enter Book ID to remove: ";
   std::getline(std::cin, bookID);

   // Call the library's removeBook method
   if (lib.removeBook(bookID)) {
      std::cout << "Book removed successfully!" << std::endl;
   } else {
      std::cout << "Book not found!" << std::endl;
   }
   return 0;
}