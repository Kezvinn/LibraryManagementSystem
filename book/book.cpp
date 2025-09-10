#include "book.h"
// Constructors
Book::Book(){}
Book::Book(std::string bookID_i, std::string title_i, std::string author_i, 
           std::string publisher_i, int total_copies_i, int avail_copies_i)
           :bookID(bookID_i), title(title_i), author(author_i),
           publisher(publisher_i), total_copies(total_copies_i),available_copies(avail_copies_i){}

// Methods
std::vector<std::string> Book::getBookInfo(){
   std::vector<std::string> bookInfo;
   bookInfo.push_back(this->bookID);
   bookInfo.push_back(this->title);
   bookInfo.push_back(this->author);
   bookInfo.push_back(this->publisher);
   bookInfo.push_back(std::to_string(this->total_copies));
   bookInfo.push_back(std::to_string(this->available_copies));
   return bookInfo;   
}
void Book::displayBookInfo(char format){
   if (format == 'v'){
      std::cout << "BookID:\t" << this->bookID << std::endl;
      std::cout << "Title:\t" << this->title << std::endl;
      std::cout << "Author:\t" << this->author << std::endl;
      std::cout << "Publisher:\t" << this->publisher << std::endl;
      std::cout << "Total Copies:\t" << this->total_copies << std::endl;
      std::cout << "Available Copies:\t" << this->available_copies << std::endl;
      
   } else if (format == 'h'){
      std::cout << std::left 
                << std::setw(15) << std::setw(20) << this->bookID 
                << std::setw(20) << std::setw(20) << this->title 
                << std::setw(20) << std::setw(20) << this->author 
                << std::setw(20) << std::setw(20) << this->publisher 
                << std::setw(20) << std::setw(20) << this->total_copies 
                << std::setw(20) << this->available_copies 
                << std::endl;
   }
}   
bool Book::isAvailable(){
   return this->available_copies > 0;
}
void Book::borrowBook(){
   if (this->isAvailable()){
      this->available_copies--;
      std::cout << "\033[32m[INFO] Book borrowed successfully!\033[0m" << std::endl;
   } else {
      std::cout << "\033[31m[ERROR] No copies available for borrowing.\033[0m" << std::endl;
   }
}
void Book::returnBook(){
   this->available_copies++;
   // std::cout << "Book returned successfully!" << std::endl;
}

// Setter
int Book::setTitle(std::string title){
   this->title = title;
   return 0;
}
int Book::setAuthor(std::string author){
   this->author = author;
   return 0;
}
int Book::setPublisher(std::string publisher){
   this->publisher = publisher;
   return 0;
}
int Book::setTotalCopies(int total_copies){
   this->total_copies = total_copies;
   return 0;
}
int Book::setAvailableCopies(int available_copies){
   this->available_copies = available_copies;
   return 0;
}
// Getter
std::string Book::getBookID(){
   return this->bookID;
}
std::string Book::getTitle(){
   return this->title;
}
std::string Book::getAuthor(){
   return this->author;
}
std::string Book::getPublisher(){
   return this->publisher;
}
int Book::getTotalCopies(){
   return this->total_copies;
}
int Book::getAvailableCopies(){
   return this->available_copies;
}
