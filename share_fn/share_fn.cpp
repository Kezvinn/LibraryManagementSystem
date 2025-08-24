#include "share_fn.h"

std::string randID(char type) {
// Seed the random generator once (not every call!)
   static bool seeded = false;
   if (!seeded) {
      std::srand(static_cast<unsigned>(std::time(nullptr)));
      seeded = true;
   }
   int number = std::rand() % 900 + 100; // random 3-digit number (100–999)\

   return type + std::to_string(number);
}
int getInputInRange(int min, int max){
   int value;
   std::string input;
   while (true) {
      std::cout << "Enter a number (" << min << " - " << max << "): ";
      std::getline(std::cin, input);
      if (isValidInt(input)) {
         value = std::stoi(input);
         if (value >= min && value <= max) {
            return value;  // ✅ valid input
         } else {
            std::cout << "❌ Out of range. Please try again.\n";
         }
      } else {
         std::cout << "❌ Invalid input. Please enter a number.\n";
         std::cin.clear(); // clear error state
      }
      // discard bad input from buffer
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   }
}

void mainMenu(Library& lib, Admin *ad, Member *mem) {
   while (true){
      std::cout << "+" << std::string(30, '-') << "+" << std::endl;
      std::cout << "|" << "Main Menu" << std::string(30 - 10, ' ') << "|" << std::endl;
      std::cout << "+" << std::string(30, '-') << "+" << std::endl;
      std::cout << "Login as:\n";
      std::cout << "1. Member." << std::endl;
      std::cout << "2. Admin." << std::endl;
      std::cout << "3. Exit" << std::endl;

      int choice = getInputInRange(1,3);

      switch (choice) {
         case 1:
            memberMenu(mem, lib);
            break;
         case 2:
            adminMenu(ad, lib);
            break;
         case 3:
            std::cout << "+" << std::string(30,'-') << "+"; 
            std::cout << "| Goodbye!\t|\n";
            std::cout << "+" << std::string(30,'-') << "+";  
            break;
         default:
            break;
      }
   }
}
void memberMenu(Member *mem, Library &lib){
   // login first
   int loginStatus = mem->login();
   if (loginStatus == true) {
      while (true) {
         std::cout << "+" << std::string(30, '-') << "+" << std::endl;
         std::cout << "|" << "Member Menu" << std::string(30 - 12, ' ') << "|" << std::endl;
         std::cout << "+" << std::string(30, '-') << "+" << std::endl;
         std::cout << "1. View User Info\n";
         std::cout << "2. View Issued Books\n";
         std::cout << "3. Borrow Book\n";
         std::cout << "4. Return Book\n";
         std::cout << "5. Logout\n";

         int choice = getInputInRange(1, 5);

         switch (choice) {
            case 1:
               mem->displayUserInfo();
               break;
            case 2:
               mem->displayIssuedBookIDs();
               break;
            case 3:
               mem->borrowBook();
               break;
            case 4:
               mem->returnBook();
               break;
            case 5:
               mem->logout();
               return; // Exit member menu
            default:
               break;
         }
      }

   } else {
      std::cout << "Login failed. Please try again.\n";
   }
}
void adminMenu(Admin *ad, Library &lib){
   // login first
   bool loginStatus = ad->login();
   if (loginStatus == true) {
      while (true) {
         std::cout << "+" << std::string(30, '-') << "+" << std::endl;
         std::cout << "|" << "Admin Menu" << std::string(30 - 11, ' ') << "|" << std::endl;
         std::cout << "+" << std::string(30, '-') << "+" << std::endl;
         std::cout << "1. Add User\n";
         std::cout << "2. Remove User\n";
         std::cout << "3. View All Users\n";
         std::cout << "4. Add Book\n";
         std::cout << "5. Remove Book\n";
         std::cout << "6. Edit Book Info\n";
         std::cout << "7. View All Books\n";
         std::cout << "8. Logout\n";

         int choice = getInputInRange(1, 8);

         switch (choice) {
            case 1:
               ad->addUser();
               break;
            case 2:
               ad->removeUser();
               break;
            case 3:
               ad->viewAllUsers();
               break;
            case 4:
               ad->addBook(lib);
               break;
            case 5:
               ad->removeBook(lib);
               break;
            case 6:
               ad->editBookInfo(lib);
               break;
            case 7:
               ad->viewAllBooks(lib);
               break;
            case 8:
               ad->logout();
               return; // Exit admin menu
            default:
               break;
         }
      }   
   }
   else {
      std::cout << "Login failed. Please try again.\n";
   }
}


// Regex functions
bool isValidName(const std::string &input){
   std::regex pattern(R"(^[A-Za-z0-9\s'.,:-]+$)");
   return std::regex_match(input, pattern);
}

bool isValidInt(const std::string &input){
   std::regex pattern(R"(^\d+$)");
   return std::regex_match(input, pattern);
}
