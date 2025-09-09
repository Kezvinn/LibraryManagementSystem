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
std::string Member::getUserID() {
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
void Member::borrowBook(Library &lib) {
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
         std::cout << "Selected book is not available. Please choose another book.\n";
      }
   }
}
void Member::returnBook(Library &lib){
   printBoxCenter("Return Book", 30);
   if (this->issuedBooksID.empty()) {
      std::cout << "No books to return.\n";
      return;
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
      std::cout << "[INFO] Book returned successfully.\n";
   } else {
      std::cout << "[ERROR] Book not found in library.\n";
   }
}

int Member::setIssueBooksIDs(std::vector<std::string> issuedBooks_i){
   this->issuedBooksID = issuedBooks_i;
   return 0;
}

bool Member::logout(Library &lib){
   // Member *mem();
   for (auto &member : lib.getMembers()) {
      if (member->getUserID() == this->userID) {
         member->setIssueBooksIDs(this->issuedBooksID);
         break;
      }
   }
   printBoxCenter("Logged Out", 30);
   return true;
}