#include "admin.h" 
// Constructor
Admin::Admin():User("admin","admin123"){}
Admin::Admin(std::string adname, std::string adpwd):User(adname, adpwd){}

int Admin::addBook(Library &lib){
   printBoxCenter("Add Book", 30);
   std::string data;
   std::string booktitle, bookauthor, bookpublisher;
   std::string temp;
   int tt_copies, avail_copies;

   do {
      std::cout << "Enter Book Title: ";
      std::getline(std::cin, booktitle);
      if (!isValidName(booktitle)) {
         std::cout << "\033[31m[ERROR] Invalid input! Please enter a valid Title using letters, digits, spaces, or allowed characters only.\033[0m\n";
      }
   } while(!isValidName(booktitle));

   do {
      std::cout << "Enter Book Author: ";
      std::getline(std::cin, bookauthor);
      if (!isValidName(bookauthor)) {
         std::cout << "\033[31m[ERROR] Invalid input! Please enter a valid Author using letters, digits, spaces, or allowed characters only.\033[0m\n";
      }
   } while (!isValidName(bookauthor));
   do {
      std::cout << "Enter Book Publisher: ";
      std::getline(std::cin, bookpublisher);
      if (!isValidName(bookpublisher)) {
         std::cout << "\033[31m[ERROR] Invalid input! Please enter a valid Publisher using letters, digits, spaces, or allowed characters only.\033[0m\n";
      }
   } while (!isValidName(bookpublisher));

   do {
      std::cout << "Enter Total Copies: ";
      std::getline(std::cin, temp);
      if (!isValidInt(temp) || std::stoi(temp) <= 0) {
         std::cout << "\033[31m[ERROR] Invalid input! Please enter a positive integer for total copies.\033[0m\n";
      }
   } while(!isValidInt(temp));

   tt_copies = std::stoi(temp);
   avail_copies = tt_copies;
   temp = randID('B');
   
   Book *newbook = new Book(temp, booktitle, bookauthor, bookpublisher, tt_copies, avail_copies);
   // Book newbook(temp, booktitle, bookauthor, bookpublisher, tt_copies, avail_copies);
   lib.addBook(newbook);
   std::cout << "\033[32m[INFO] Book added successfully!\033[0m\n";
   return 0;
}
int Admin::removeBook(Library &lib){
   printBoxCenter("Remove Book", 30);
   std::vector<std::string> validID;

   for (const auto& book : lib.getBooks()) {
      validID.push_back(book->getBookID());
   }

   std::vector<std::string> title = {"Book ID", "Title", "Author", "Publisher", "Total Copies", "Available Copies"};
   std::vector<std::vector<std::string>> bookinfo;
   for (const auto& book : lib.getBooks()) {
      bookinfo.push_back(book->getBookInfo());
   }
   printTable(title, bookinfo);

   std::string bookID;
   do{
      std::cout << "Enter Book ID to remove: ";
      std::getline(std::cin, bookID);
      if (bookID.empty() || std::find(validID.begin(), validID.end(), bookID) == validID.end()) {
         std::cout << "\033[31m[ERROR] Invalid Book ID. Please enter a valid Book ID from the list above.\033[0m\n";
      }
   } while (bookID.empty() || std::find(validID.begin(), validID.end(), bookID) == validID.end());
   
   //Call the library's removeBook method
   if (lib.removeBook(bookID)) {
      std::cout << "\033[32m[INFO] Book removed successfully!\033[0m" << std::endl;
   } else {
      std::cout << "\033[31m[ERROR] Book not found!\033[0m" << std::endl;
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
      std::cout << "\033[32m[INFO] Login successful!\033[0m\n";
      return true; // Successful login
   } else {
      std::cout << "\033[31m[ERROR] Invalid username or password.\033[0m\n";
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
         std::cout << "\033[31m[ERROR] Invalid input! Please enter a valid name using letters and spaces only.\033[0m\n";
      }
   } while (!isValidName(name));
   // email
   do {
      std::cout << "Enter Email: ";
      std::getline(std::cin, email);
      if (!isValidEmail(email)) {
         std::cout << "\033[31m[ERROR] Invalid input! Please enter a valid Email format.\033[0m\n";
      }
   } while (!isValidEmail(email));
   // password
   do {
      std::cout << "Enter Password: ";
      std::getline(std::cin, pwd);
      if (!isValidPassword(pwd)) {
         std::cout << "\033[31m[ERROR] Invalid input! Password must be at least 8 characters long, "
                      "include uppercase and lowercase letters, a digit, and a special character.\033[0m\n";
      }
   } while (!isValidPassword(pwd));   
   std::string newID = randID('M');
   Member *newMember = new Member(newID, pwd, name, email);
   printBoxCenter("\033[32m[INFO] Member Added Successfully!\033[0m", 30);
   // Add the new member to the library (assuming you have a Library instance)
   lib.addMember(newMember);
   return 0;
}
int Admin::removeMember(Library &lib){
   printBoxCenter("Remove Member", 30);
   std::vector<std::vector<std::string>> memberinfo;
   for (const auto& member : lib.getMembers()) {
      // member->getMemberInfo();
      memberinfo.push_back(member->getMemberInfo()); // only need userID
   }
   std::vector<std::string> title = {"UserID", "Password", "Name", "Email", "Issued Book IDs"};
   printTable(title, memberinfo);
   
   std::vector<std::string> validID;
   for (const auto& member : lib.getMembers()) {
      validID.push_back(member->getMemberID());
   }
   std::string userID;   
   do {
      std::cout << "Enter User ID to remove: ";
      std::getline(std::cin, userID);
      if (userID.empty() || std::find(validID.begin(), validID.end(), userID) == validID.end()) {
         std::cout << "\033[31m[ERROR] Invalid User ID. Please enter a valid User ID from the list above.\033[0m\n";
      }
   } while (userID.empty() || std::find(validID.begin(), validID.end(), userID) == validID.end());

   // std::string userID;
   // std::cout << "Enter User ID to remove: ";
   // std::getline(std::cin, userID);

   // Call the library's removeMember method
   if (lib.removeMember(userID)) {
      std::cout << "\033[32m[INFO] Member removed successfully!\033[0m" << std::endl;
   } else {
      std::cout << "\033[31m[ERROR] Member not found!\033[0m" << std::endl;
   }
   return 0;
}
int Admin::viewAllMembers(Library &lib){
   printBoxCenter("All Members", 30);

   std::vector<std::vector<std::string>> memberinfo;
   for (const auto& member : lib.getMembers()) {
      // member->getMemberInfo();
      memberinfo.push_back(member->getMemberInfo()); // only need userID
   }
   std::vector<std::string> title = {"UserID", "Password", "Name", "Email", "Issued Book IDs"};
   printTable(title, memberinfo);
   // for (const auto& member : lib.getMembers()) {
   //    member->displayMemberInfo();
   //    std::cout << std::string(50, '-') << "\n";
   // }
   return 0;
}
int Admin::viewAllBooks(Library &lib){
   printBoxCenter("All Books", 30);
   std::vector<std::vector<std::string>> bookinfo;
   for (const auto& book : lib.getBooks()) {
      bookinfo.push_back(book->getBookInfo());
   }
   std::vector<std::string> title = {"Book ID", "Title", "Author", "Publisher", "Total Copies", "Available Copies"};
   printTable(title, bookinfo);
   // int i = 0;
   // for (const auto& book : lib.getBooks()) {
   //    std::cout << i << ". ";
   //    book->displayBookInfo('h');
   //    i++;
   //    // std::cout << std::string(30, '-') << "\n";
   // }
   return 0;
}

int Admin::editBookInfo(Library &lib){
   printBoxCenter("Edit Book Info", 30);

   // Retrieve all the books from lib
   std::vector<std::string> title = {"Book ID", "Title", "Author", "Publisher", "Total Copies", "Available Copies"};
   std::vector<std::vector<std::string>> bookinfo;
   
   for (const auto& book : lib.getBooks()) {
      bookinfo.push_back(book->getBookInfo());
   }
   printTable(title, bookinfo);

   // int choice = getInputInRange(1, (int)lib.getBooks().size());
   std::vector<std::string> validID;
   for (const auto& book : lib.getBooks()) {
      validID.push_back(book->getBookID());
   }
   std::string bookID;   
   do {
      std::cout << "Enter Book ID to remove: ";
      std::getline(std::cin, bookID);
      if (bookID.empty() || std::find(validID.begin(), validID.end(), bookID) == validID.end()) {
         std::cout << "\033[31m[ERROR] Invalid Book ID. Please enter a valid Book ID from the list above.\033[0m\n";
      }
   } while (bookID.empty() || std::find(validID.begin(), validID.end(), bookID) == validID.end());


   Book* book_to_edit = lib.findBookByID(bookID);
   std::cout << "Edit Options:\n";
   std::cout << "1. Book Title.\n";
   std::cout << "2. Book Author.\n";
   std::cout << "3. Book Publisher.\n";
   std::cout << "4. Total Copies.\n";
   std::cout << "5. Available Copies.\n";
   
   int edit_choice = getInputInRange(1, 5);
   std::string new_value;
   
   switch (edit_choice) {
      case 1:  //Title
         do{
            std::cout << "Enter new Title: ";
            std::getline(std::cin, new_value);
            if (!isValidName(new_value)) {
               std::cout << "\033[31m [ERROR] Invalid input! Please enter a valid Title using letters, digits, spaces, or allowed characters only.\033[0m\n";
            } else {
               book_to_edit->setTitle(new_value);
            }
         } while (!isValidName(new_value));
         std::cout << "\033[32m[INFO] New title updated successfully!\033[0m\n";
         break;
      case 2:  // Author
         do { 
            std::cout << "Enter new Book Author: ";
            std::getline(std::cin, new_value);
            if (!isValidName(new_value)) {
               std::cout << "\033[31m [ERROR] Invalid input! Please enter a valid Author using letters, digits, spaces, or allowed characters only.\033[0m \n";
            } else {
               book_to_edit->setAuthor(new_value);
            }
         } while (!isValidName(new_value));
         std::cout << "\033[32m[INFO] New author updated successfully!\033[0m\n";
         break;
      case 3:  // Publisher
         do {
            std::cout << "Enter new Book Publisher: ";
            std::getline(std::cin, new_value);
            if (!isValidName(new_value)) {
               std::cout << "\033[31m [ERROR] Invalid input! Please enter a valid Publisher using letters, digits, spaces, or allowed characters only.\033[0m\n";
            } else {
               book_to_edit->setPublisher(new_value);
            }
         } while (!isValidName(new_value));
         std::cout << "\033[32m[INFO] New publisher updated successfully!\033[0m\n";
         break;
      case 4:  // Total copies
         do {
            std::cout << "Enter Total Copies: ";
            std::getline(std::cin, new_value);
            if (!isValidInt(new_value)) {
               std::cout << "\033[31m[ERROR] Invalid input! Please enter a valid number.\033[0m\n";
            } else {
               book_to_edit->setTotalCopies(std::stoi(new_value));
               std::cout << "\033[32m[INFO] New total copies updated successfully!\033[0m\n";
            }
         } while(!isValidInt(new_value));
         break;
      case 5:  // Available copies
         do {
            std::cout << "Enter Available Copies (< " << book_to_edit->getTotalCopies() << "): ";
            std::getline(std::cin, new_value);
            if ((!isValidInt(new_value)) || (std::stoi(new_value) > book_to_edit->getTotalCopies())) {
               std::cout << "\033[31m [ERROR] Invalid input! Please enter a valid number not exceeding total copies (" << book_to_edit->getTotalCopies() << ").\033[0m\n";
            } else {
               book_to_edit->setAvailableCopies(std::stoi(new_value));
               std::cout << "\033[32m[INFO] New available copies updated successfully!\033[0m\n";
            }
         } while((!isValidInt(new_value)) || (std::stoi(new_value) > book_to_edit->getTotalCopies()));
         break;
      default:
         break;
   }
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
         std::cout << "\033[32m[INFO] Login successful!\033[0m\n";
         mem = *member;
         return true;
      }
   }
   std::cout << "\033[31m[ERROR] Login failed! Incorrect username or password.\033[0m\n";
   return false;
}
// int Admin::editMemberInfo(Library& lib){
//    printBoxCenter("Edit Member Info", 30);
//    // Retrieve all the members from lib
//    std::vector<std::vector<std::string>> memberinfo;
//    for (const auto& member : lib.getMembers()) {
//       memberinfo.push_back(member->getMemberInfo()); // only need userID
//    }
//    std::vector<std::string> title = {"UserID", "Password", "Name", "Email", "Issued Book IDs"};
//    printTable(title, memberinfo);
//    std::vector<std::string> validID;
//    for (const auto& member : lib.getMembers()) {
//       validID.push_back(member->getMemberID());
//    }
//    std::string memberID;
//    do {
//       std::cout << "Enter Member ID to edit: ";
//       std::getline(std::cin, memberID);
//       if (memberID.empty() || std::find(validID.begin(), validID.end(), memberID) == validID.end()) {
//          std::cout << "\033[31m[ERROR] Invalid Member ID. Please enter a valid Member ID from the list above.\033[0m\n";
//       }
//    } while (memberID.empty() || std::find(validID.begin(), validID.end(), memberID) == validID.end());
//    Member* member_to_edit = lib.findUserByID(memberID);
//    std::cout << "Edit Options:\n";
//    std::cout << "1. Member Name.\n";
//    std::cout << "2. Email.\n";
//    std::cout << "3. Password.\n";
//    std::cout << "4. Issued Book IDs.\n";
//    int edit_choice = getInputInRange(1, 4);
//    switch (edit_choice) {
//       case 1:
//          // Edit Name
//          break;
//       case 2:
//          // Edit Email
//          break;
//       case 3:
//          // Edit Password
//          break;
//       case 4:
//          // Edit Issued Book IDs
//          break;
//       default:
//          break;
//    }
//    return 0;
// }
