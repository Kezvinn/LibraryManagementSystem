#include "admin.h" 
// Constructor
Admin::Admin():User("admin","admin123"){}
Admin::Admin(std::string adname, std::string adpwd):User(adname, adpwd){}

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
   printBoxCenter("Admin Login", 30);

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
   printBoxCenter("Add Member",30);
   std::string name, email, pwd;
   // name
   do {
      std::cout << "Enter your name: ";
      std::getline(std::cin, name);
      if (!isValidName(name)) {
         std::cout << "Invalid input! Please enter a valid name using letters and spaces only.\n";
      }
   } while (!isValidName(name));
   // email
   do {
      std::cout << "Enter Email: ";
      std::getline(std::cin, email);
      if (!isValidEmail(email)) {
         std::cout << "Invalid input! Please enter a valid Email format.\n";
      }
   } while (!isValidEmail(email));
   // password
   do {
      std::cout << "Enter Password: ";
      std::getline(std::cin, pwd);
      if (!isValidPassword(pwd)) {
         std::cout << "Invalid input! Password must be at least 8 characters long, "
                      "include uppercase and lowercase letters, a digit, and a special character.\n";
      }
   } while (!isValidPassword(pwd));   
   std::string newID = randID('M');
   Member *newMember = new Member(newID, pwd, name, email);
   // Add the new member to the library (assuming you have a Library instance)
   lib.addMember(newMember);
   return 0;
}
int Admin::removeMember(Library &lib){
   printBoxCenter("Remove Member", 30);
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
   printBoxCenter("All Members", 30);

   for (const auto& member : lib.getMembers()) {
      member->displayMemberInfo();
      std::cout << std::string(50, '-') << "\n";
   }
   return 0;
}
int Admin::viewAllBooks(Library &lib){
   printBoxCenter("All Books", 30);
   int i = 0;
   for (const auto& book : lib.getBooks()) {
      std::cout << i << ". ";
      book->displayBookInfo('h');
      i++;
      // std::cout << std::string(30, '-') << "\n";
   }
   return 0;
}

int Admin::editBookInfo(Library &lib){
   printBoxCenter("Edit Book Info", 30);

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
   
   int edit_choice = getInputInRange(1, 5);
   std::string new_value;

   return 0;

}

bool Admin::authenticate(Library& lib, Member &mem){
   std::string username, password;
   printBoxCenter("Member Login", 30);
   std::cout << "Enter Username: ";
   std::getline(std::cin, username);
   std::cout << "Enter Password: ";
   std::getline(std::cin, password);

   for (const auto& member : lib.getMembers()) {
      if (member->getUsername() == username && member->getPassword() == password) {
         std::cout << "[INFO] Login successful!\n";
         mem = *member;
         return true;
      }
   }
   std::cout << "[ERROR] Login failed! Incorrect username or password.\n";
   std::cout << "username: " << username<< "\n";
   std::cout << "password: " << password<< "\n";
   return false;
}