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

   //Call the library's removeBook method
   if (lib.removeBook(bookID)) {
      std::cout << "Book removed successfully!" << std::endl;
   } else {
      std::cout << "Book not found!" << std::endl;
   }
   return 0;
}

bool Admin::login(){
   std::string uname, pwd;
   std::cout << "+" << std::string(30, '-') << "+\n";
   std::cout << "\tAdmin Login\t";
   std::cout << "+" << std::string(30, '-') << "+\n";

   std::cout << "Enter Username: ";
   std::getline(std::cin, uname);

   std::cout << "Enter Password: ";
   std::getline(std::cin, pwd);

   if (uname == this->getUsername() && pwd == this->getPassword()) {
      std::cout << "Login successful!\n";
      return true; // Successful login
   } else {
      std::cout << "Invalid username or password.\n";
      return false; // Failed login
   }
   return false;
}

int Admin::addMember(Library &lib){
   std::cout << "+" << std::string(30, '-') << "+\n";
   std::cout << "\tAdd Member\t";
   std::cout << "+" << std::string(30, '-') << "+\n";
   std::string name, email, phone, address;

   std::cout << "Enter Name: ";
   std::getline(std::cin, name);
   std::cout << "Enter Email: ";
   std::getline(std::cin, email);
   std::cout << "Enter Phone: ";
   std::getline(std::cin, phone);
   std::cout << "Enter Address: ";
   std::getline(std::cin, address);

   Member *newMember = new Member(name, email, phone, address);
   // Add the new member to the library (assuming you have a Library instance)
   lib.addMember(newMember);
   return 0;
}
int Admin::removeMember(Library &lib){
   std::cout << "+" << std::string(30, '-') << "+\n";
   std::cout << "\tRemove Member\t";
   std::cout << "+" << std::string(30, '-') << "+\n";
   std::string userID;

   std::cout << "Enter User ID to remove: ";
   std::getline(std::cin, userID);

   // Call the library's removeMember method
   if (lib.removeMember(userID)) {
      std::cout << "Member removed successfully!" << std::endl;
   } else {
      std::cout << "Member not found!" << std::endl;
   }
   return 0;
}
int Admin::viewAllMembers(Library &lib){
   std::cout << "+" << std::string(50, '-') << "+\n";
   std::cout << "\tAll Members\t";
   std::cout << "+" << std::string(50, '-') << "+\n";

   for (const auto& member : lib.getMembers()) {
      member->displayMemberInfo();
      std::cout << std::string(50, '-') << "\n";
   }
   return 0;
}
int Admin::viewAllBooks(Library &lib){
   std::cout << "+" << std::string(30, '-') << "+\n";
   std::cout << "\tAll Books\t";
   std::cout << "+" << std::string(30, '-') << "+\n";
   int i = 0;
   for (const auto& book : lib.getBooks()) {
      std::cout << i << ". ";
      book->displayBookInfo('h');
      i++;
      std::cout << std::string(30, '-') << "\n";
   }
   return 0;
}

int Admin::editBookInfo(Library &lib){
   std::cout << "+" << std::string(30,'-') << "+\n";
   std::cout << "\tEdit Book Info\t";
   std::cout << "+" << std::string(30,'-') << "+\n";

   // Retrieve all the books from lib
   std::vector<Book*> books = lib.getBooks();
   int i = 0;
   for (auto bk : books){
      std::cout << i << ".\t";
      bk->displayBookInfo('h');
      i++;
   }
   std::cout << "Choose book to edit: ";
   int book_choice = getInputInRange(0, i-1);

   Book* book_to_edit = books[book_choice];
   std::cout << "1. Edit Book Title.\n";
   std::cout << "2. Edit Book Author.\n";
   std::cout << "3. Edit Book Publisher.\n";
   std::cout << "4. Edit Total Copies.\n";
   std::cout << "5. Edit Available Copies.\n";
   std::cout << "Choose an option to edit: ";

   int edit_choice = getInputInRange(1, 5);


   return 0;

}