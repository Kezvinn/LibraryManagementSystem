#include "library.h"

Library::Library() {}
Library::Library(std::vector<Member*> members_i, std::vector<Book*> books_i)
               : members_vt(members_i), books_vt(books_i) {}

std::vector<Book*> Library::getBooks() const {
   return books_vt;
}
std::vector<Member*> Library::getMembers() const {
   return members_vt;
}

int Library::loadFromFile() {
// Load Member
   std::ifstream file(MEMBERS_DATA, std::ios::in);
   if (!file.is_open()) {
      std::cerr << "[ERROR] Failed to open member data file." << std::endl;
      return -1;
   }
   std::string data_line;
   while(std::getline(file, data_line)) {
      if (data_line.empty()) continue; // skip blank lines

      std::vector<std::string> sub_str_vt;      // this would contain all the   
      std::string token;
      
      std::istringstream iss(data_line);
      while (std::getline(iss, token, '|')) {
         sub_str_vt.push_back(token);
      }

      std::vector<std::string> issuedBooksID;
      std::istringstream bookIssuedStream(sub_str_vt[4]);
      std::string bookID;
      while(bookIssuedStream >> bookID) {
         if (bookID == "None") break;
         issuedBooksID.push_back(bookID);
      }
      
      Member *mem = new Member(sub_str_vt[0], sub_str_vt[1], 
                               sub_str_vt[2],sub_str_vt[3], 
                               issuedBooksID);
      members_vt.push_back(mem);
   }
   file.close();
   std::cout << "[INFO] Members loaded successfully." << std::endl;

// Load Books
   file.open(BOOKS_DATA, std::ios::in);
   if (!file.is_open()) {
      std::cerr << "[ERROR] Failed to open book data file." << std::endl;
      return -1;
   }
   data_line.clear();
   while (std::getline(file, data_line)) {
      if (data_line.empty()) continue; // skip blank lines

      std::vector<std::string> sub_str_vt;
      std::string token;
      std::istringstream iss(data_line);
      while (std::getline(iss, token, '|')) {
         sub_str_vt.push_back(token);
      }
      Book *book = new Book(sub_str_vt[0], sub_str_vt[1], 
                             sub_str_vt[2], sub_str_vt[3], 
                             std::stoi(sub_str_vt[4]), 
                             std::stoi(sub_str_vt[5]));
      books_vt.push_back(book);        
   }
   file.close();
   std::cout << "[INFO] Books loaded successfully." << std::endl;

   return 0;
}
Book* Library::searchBookByTitle(std::string title) {
   auto it = std::find_if(books_vt.begin(), books_vt.end(),
                        [&title](Book* book) { return book->getBookInfo()[1] == title; });
   if (it != books_vt.end()) {
      return *it; // Book found
   }
   return nullptr; // Book not found
}
Book* Library::searchBookByAuthor(std::string author) {
   auto it = std::find_if(books_vt.begin(), books_vt.end(),
                        [&author](Book* book) { return book->getBookInfo()[2] == author; });
   if (it != books_vt.end()) {
      return *it; // Book found
   }
   return nullptr; // Book not found
}
Book* Library::findBookByID(std::string bookID){
   auto it = std::find_if(books_vt.begin(), books_vt.end(),
                        [&bookID](Book* book) { return book->getBookInfo()[0] == bookID; });
   if (it != books_vt.end()) {
      return *it; // Book found
   }
   return nullptr; // Book not found
}
Member* Library::findUserByID(std::string userID) {
   auto it = std::find_if(members_vt.begin(), members_vt.end(),
                        [&userID](Member* member) { return member->getMemberInfo()[0] == userID; });
   if (it != members_vt.end()) {
      return *it; // Member found
   }
   return nullptr; // Member not found
}

int Library::saveToFile(){
// Save Members Info
   std::ofstream file(MEMBERS_DATA, std::ios::out);
   if (!file.is_open()) {
      std::cerr << "[ERROR] Failed to open member data file for writing." << std::endl;
      return -1;
   }
   for (int i = 0; i < members_vt.size(); i++) {
      std::vector<std::string> data = members_vt[i]->getMemberInfo();
      file << data[0] << "|" << data[1] << "|"
           << data[2] << "|" << data[3] << "|"
           << data[4];
      if (i != members_vt.size() - 1) {
         file << "\n";
      }
   }
   file.close();
   std::cout << "[INFO] Members saved successfully." << std::endl;

// Save Books Info
   file.open(BOOKS_DATA, std::ios::out);
   if (!file.is_open()) {
      std::cerr << "[ERROR] Failed to open book data file for writing." << std::endl;
      return -1;
   }
   for (int i = 0; i < books_vt.size(); i++) {
      std::vector<std::string> bookInfo = books_vt[i]->getBookInfo();
      file << bookInfo[0] << "|" << bookInfo[1] << "|"
           << bookInfo[2] << "|" << bookInfo[3] << "|"
           << bookInfo[4] << "|" << bookInfo[5];
      if(i != books_vt.size() - 1) {
         file << "\n";
      }
   }
   file.close();
   std::cout << "[INFO] Books saved successfully." << std::endl;

   return 0;
}

bool Library::addBook(Book* newBook) {
   books_vt.push_back(newBook);
   return true;
}
bool Library::addMember(Member* newMember) {
   members_vt.push_back(newMember);
   return true;
}

bool Library::removeBook(std::string bookID) {
   auto it = std::find_if(books_vt.begin(), books_vt.end(),
                        [&bookID](Book* book) { return book->getBookInfo()[0] == bookID; });
   if (it != books_vt.end()) {
      delete *it; // Free the memory allocated for the Book object
      books_vt.erase(it);
      return true; // Book found and removed
   }
   return false; // Book not found
}

bool Library::removeMember(std::string memberID) {
   auto it = std::find_if(members_vt.begin(), members_vt.end(),
                        [&memberID](Member* member) { return member->getMemberInfo()[0] == memberID; });
   if (it != members_vt.end()) {
      delete *it; // Free the memory allocated for the Member object
      members_vt.erase(it);
      return true; // Member found and removed
   }
   return false; // Member not found
}