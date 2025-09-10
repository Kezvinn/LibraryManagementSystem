#include "member.h"

// Constructors
Member::Member(){}
Member::Member(std::string userID_i, std::string pwd_i, 
               std::string name_i, std::string email_i, 
               std::vector<std::string> issueBooks_i)
               :
               User(userID_i, pwd_i), userID(userID_i), 
               name(name_i), email(email_i), issuedBooksID(issueBooks_i){}
Member::Member(std::string userID_i, std::string pwd_i, 
               std::string name_i, std::string email_i)
               :
               User(userID_i, pwd_i), userID(userID_i),
               name(name_i), email(email_i){}

std::vector<std::string> Member::getMemberInfo(){
   std::vector<std::string> userInfo;

   userInfo.push_back(this->userID);
   userInfo.push_back(this->getPassword());
   userInfo.push_back(this->name);
   userInfo.push_back(this->email);
   std::string issuedBooksStr;
   if (this->issuedBooksID.empty()) {
      issuedBooksStr = "None";
   } else {
      for (auto item : this->issuedBooksID){
         issuedBooksStr += item + " ";
      }
   }
   userInfo.push_back(issuedBooksStr);
   
   return userInfo;
}

std::vector<std::string> Member::getIssuedBookIDs() {
   return this->issuedBooksID;
}
std::string Member::getMemberID() {
   return this->userID;
}
std::string Member::getName() {
   return this->name;
}
std::string Member::getEmail() {
   return this->email;
}

// bool Member::login(){
//    std::string username, password;
//    printBoxCenter("Member Login", 30);
//    std::cout << "Enter Username: ";
//    std::getline(std::cin, username);
//    std::cout << "Enter Password: ";
//    std::getline(std::cin, password);

//    if (username == this->getUsername() && password == this->getPassword()){
//       std::cout << "[INFO] Login successful!\n";
//       return true;
//    } else {
//       std::cout << "[ERROR] Login failed! Incorrect username or password.\n";
//       std::cout << "username: " << username<< "\n";
//       std::cout << "password: " << password<< "\n";
   
//       return false;
//    }
// }

void Member::displayIssuedBookIDs(){
   int i = 1;
   printBoxCenter("Issued Book IDs", 30);
   for (const auto& bookID : this->issuedBooksID){
      std::cout  << i << ". " << bookID << "\n";
      i++;
   }
}
void Member::displayMemberInfo(){
   std::vector<std::string> title = {"UserID", "Password", "Name", "Email", "Issued Book IDs"};
   printBoxCenter("Member Information", 30);

   std::vector<std::string> info = this->getMemberInfo();
   printBox(title, info, 28);
   // if (this->issuedBooksID.empty()) {
   //    std::cout << "None\n";
   // } else {
   //    for (const auto& bookID : this->issuedBooksID) {
   //       std::cout << bookID << ", ";
   //    }
   //    std::cout << "\n";
   // }
}
int Member::borrowBook(Library &lib) {
   std::vector<std::string> title = {"BookID", "Title", "Author", "Publisher", "Total Copies", "Available Copies"};
   printBoxCenter("Borrow Book", 30);
   
   while (true) {
      int i = 1;
      for (const auto& book : lib.getBooks()) {
         std::vector<std::string> bookinfo = book->getBookInfo();
         printBox(title, bookinfo,28);
         i++;
      }
      int choice = getInputInRange(1, i-1);
      Book* selectedBook = lib.getBooks()[choice - 1];
      if (selectedBook->isAvailable()) {                                         
         selectedBook->borrowBook();
         this->issuedBooksID.push_back(selectedBook->getBookID()); // Add BookID to issuedBooksID
         break;
      } else {
         std::cout << "\033[31m[ERROR] Selected book is not available. Please choose another book.\033[0m\n";
      }
   }
   return 0;
}
int Member::returnBook(Library &lib){
   printBoxCenter("Return Book", 30);
   if (this->issuedBooksID.empty()) {
      std::cout << "\033[31m[ERROR] No books to return.\033[0m\n";
      return -1;
   }

   int i = 1;
   for (const auto& bookID : this->issuedBooksID) {
      std::cout << i << ". " << bookID << "\n";
      i++;
   }

   int choice = getInputInRange(1, i-1);
   std::string selectedBookID = this->issuedBooksID[choice - 1];
   Book* book = lib.findBookByID(selectedBookID);
   if (book) {
      book->returnBook();
      this->issuedBooksID.erase(this->issuedBooksID.begin() + (choice - 1));
      std::cout << "\033[32m[INFO] Book returned successfully.\033[0m\n";
   } else {
      std::cout << "\033[31m[ERROR] Book not found in library.\033[0m\n";
   }
   return 0;
}

int Member::setIssueBooksIDs(std::vector<std::string> issuedBooks_i){
   this->issuedBooksID = issuedBooks_i;
   return 0;
}
int Member::setName(std::string name_i){
   this->name = name_i;
   return 0;
}
int Member::setEmail(std::string email_i){
   this->email = email_i;
   return 0;
}
int Member::setPassword(std::string pwd_i){
   this->User::setPassword(pwd_i);
   return 0;
}

bool Member::logout(Library &lib){
   // Member *mem();
   for (auto &member : lib.getMembers()) {
      if (member->getMemberID() == this->userID) {
         member->setName(this->name);
         member->setEmail(this->email);
         member->setPassword(this->getPassword());
         member->setIssueBooksIDs(this->issuedBooksID);
         break;
      }
   }
   printBoxCenter("Logged Out", 30);
   return true;
}

int Member::editMemberInfo(Library &lib){
   printBoxCenter("Edit Member Info", 30);
   std::cout << "Edit Options:\n";
   std::cout << "1. Name.\n";
   std::cout << "2. Email.\n";
   std::cout << "3. Password.\n";
   int edit_choice = getInputInRange(1, 3);
   std::string new_value;
   switch (edit_choice) {
      case 1:
         // Edit Name
         do {
            std::cout << "Enter new name: ";
            std::getline(std::cin, new_value);
            if (!isValidName(new_value)) {
               std::cout << "\033[31m[ERROR] Invalid name. Please enter a valid name (only letters and spaces).\033[0m\n";
            } else {
               this->setName(new_value);
               std::cout << "\033[32m[INFO] New name updated successfully!\033[0m\n";
            }
         } while (!isValidName(new_value));
         break;
      case 2:
         // Edit Email
         do {
            std::cout << "Enter new email: ";
            std::getline(std::cin, new_value);
            if (!isValidEmail(new_value)) {
               std::cout << "\033[31m[ERROR] Invalid email format. Please enter a valid email.\033[0m\n";
            } else {
               this->setEmail(new_value);
               std::cout << "\033[32m[INFO] New email updated successfully!\033[0m\n";
            }
         } while (!isValidEmail(new_value));
         break;
      case 3:
         // Edit Password
         do {
            std::cout << "Enter new password (at least 6 characters): ";
            std::getline(std::cin, new_value);
            if (!isValidPassword(new_value)) {
               std::cout << "\033[31m[ERROR] Invalid password. Please enter a valid password (at least 6 characters).\033[0m\n";
            } else {
               this->setPassword(new_value);
               std::cout << "\033[32m[INFO] New password updated successfully!\033[0m\n";
            }
         } while (!isValidPassword(new_value));
         break;
      default:
         break;
   }
   return 0;
}
// std::string Member::getPassword(){
//    return this->User::getPassword();
// }
// int Member::operator= (const Member &other) {
//    if (this != &other) {
//       this->userID = other.userID;
//       this->name = other.name;
//       this->email = other.email;
//       this->issuedBooksID = other.issuedBooksID;
//       std::string pwd = other.getPassword();
//       this->setPassword(pwd);
//    }
//    return 0;
// }