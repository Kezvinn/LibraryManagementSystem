#include "library.h"

Library::Library() {}
Library::Library(std::vector<Member*> members_i, std::vector<Book*> books_i)
               : members_vt(members_i), books_vt(books_i) {}

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

int Library::saveToFile(){
// Save Members Info
   std::ofstream file(MEMBERS_DATA, std::ios::out);
   if (!file.is_open()) {
      std::cerr << "[ERROR] Failed to open member data file for writing." << std::endl;
      return -1;
   }
   for (const auto& member : members_vt) {
      std::vector<std::string> data = member->getUserInfo();
      file << data[0] << "|" << data[1] << "|"
           << data[2] << "|" << data[3] << "|"
           << data[4] << "\n";
   }
   file.close();
   std::cout << "[INFO] Members saved successfully." << std::endl;

// Save Books Info
   file.open(BOOKS_DATA, std::ios::out);
   if (!file.is_open()) {
      std::cerr << "[ERROR] Failed to open book data file for writing." << std::endl;
      return -1;
   }
   for (const auto& book : books_vt) {
      std::vector<std::string> bookInfo = book->getBookInfo();
      file << bookInfo[0] << "|" << bookInfo[1] << "|"
           << bookInfo[2] << "|" << bookInfo[3] << "|"
           << bookInfo[4] << "|" << bookInfo[5] << "\n";
   }
   file.close();
   std::cout << "[INFO] Books saved successfully." << std::endl;

   return 0;
}