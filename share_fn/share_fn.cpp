#include "share_fn.h"
void printBoxCenter(std::string text, int width) {
   // Top border
   std::cout << "+" << std::string(width, '-') << "+" << std::endl;

   // Calculate padding
   int totalPadding = width - static_cast<int>(text.size());
   if (totalPadding < 0) totalPadding = 0; // text longer than width
   int leftPadding = totalPadding / 2;
   int rightPadding = totalPadding - leftPadding;

   // Print line with centered text
   std::cout << "|"
            << std::string(leftPadding, ' ')
            << text
            << std::string(rightPadding, ' ')
            << "|" << std::endl;

   // Bottom border
   std::cout << "+" << std::string(width, '-') << "+" << std::endl;
}
void printBox(const std::vector<std::string>& titles,
              const std::vector<std::string>& lines,
              int width) {
    if (titles.size() != lines.size()) {
        std::cerr << "Error: titles and lines must have the same number of elements.\n";
        return;
    }
    if (titles.empty() || width <= 0) return;

    // Top border
    std::cout << "+" << std::string(width + 2, '-') << "+" << std::endl;

    for (size_t i = 0; i < titles.size(); ++i) {
        std::string label = titles[i] + ": ";
        std::string text = lines[i];

        bool firstLine = true;

        while (!text.empty() || firstLine) {
            std::string part;
            if (firstLine) {
                // Title goes on the first line
                if (label.size() + text.size() > static_cast<size_t>(width)) {
                    size_t avail = width - label.size();
                    part = label + text.substr(0, avail);
                    text = text.substr(avail);
                } else {
                    part = label + text;
                    text.clear();
                }
            } else {
                // Wrapped lines aligned under the value, not under the border
                size_t avail = width - label.size();
                std::string wrapPrefix(label.size(), ' '); // spaces to align
                if (text.size() > avail) {
                    part = wrapPrefix + text.substr(0, avail);
                    text = text.substr(avail);
                } else {
                    part = wrapPrefix + text;
                    text.clear();
                }
            }

            // Padding
            size_t padding = width - part.size();
            std::cout << "| " << part << std::string(padding, ' ') << " |" << std::endl;

            firstLine = false;
        }
    }

    // Bottom border
    std::cout << "+" << std::string(width + 2, '-') << "+" << std::endl;
}
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
   // int value;
   std::string input;
   
   while (true) {
      std::cout << "Enter a number (" << min << " - " << max << "): ";
      std::getline(std::cin, input);


      if (isValidInt(input)) {
         int value = std::stoi(input);
         if (value >= min && value <= max) {
            return value;  // ✅ valid input
         } else {
            std::cout << "Out of range. Please try again.\n";
            continue;
         }
      } else {
         std::cout << "Invalid input. Please enter a number.\n";
         std::cin.clear(); // clear error state
      }
      // discard bad input from buffer
      // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   }
   return -1; // should never reach here
}

void mainMenu(Library& lib, Admin *ad, Member *mem) {
   while (true){
      printBoxCenter("E-Library System", 30);
      printBoxCenter("Main Menu", 30);
      std::cout << "Login as:\n";
      std::cout << "1. Member." << std::endl;
      std::cout << "2. Admin." << std::endl;
      std::cout << "3. Exit" << std::endl;

      int choice = getInputInRange(1,3);

      switch (choice) {
         case 1:
            memberMenu(mem, lib, ad);
            break;
         case 2:
            adminMenu(ad, lib);
            break;
         case 3: 
            lib.saveToFile();
            printBoxCenter("Goodbye", 30);
            return;
         default:
            break;
      }
   }
}
void memberMenu(Member *mem, Library &lib, Admin *ad){
   if (ad->authenticate(lib, *mem) == true) {
      while (true) {
         printBoxCenter("Member Menu", 30);
         std::cout << "1. View User Info\n";
         std::cout << "2. View Issued Books\n";
         std::cout << "3. Borrow Book\n";
         std::cout << "4. Return Book\n";
         std::cout << "5. Logout\n";

         int choice = getInputInRange(1, 5);

         switch (choice) {
            case 1:
               mem->displayMemberInfo();
               if (returnPrompt()){
                  break;
               } 
            case 2:
               mem->displayIssuedBookIDs();
               if (returnPrompt()) {
                  break;
               }               
            case 3:
               mem->borrowBook(lib);
               break;
            case 4:
               mem->returnBook(lib);
               break;
            case 5:
               // mem->logout();
               return; // Exit member menu
            default:
               break;
         }
      }

   } else {
      // std::cout << "Login failed. Please try again.\n";
   }
}
void adminMenu(Admin *ad, Library &lib){
   // login first
   bool loginStatus = ad->login();
   if (loginStatus == true) {
      while (true) {
         printBoxCenter("Admin Menu", 30);
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
               ad->addMember(lib);
               break;
            case 2:
               ad->removeMember(lib);
               break;
            case 3:
               ad->viewAllMembers(lib);
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
               // ad->logout();
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

bool isValidEmail(const std::string &input) {
   std::regex pattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))");
   return std::regex_match(input, pattern);
}
bool isValidPassword(const std::string &input) {
   // At least 8 characters, one uppercase, one lowercase, one digit, one special character
   std::regex pattern(R"((?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,})");
   return std::regex_match(input, pattern);
}

bool returnPrompt(){
   while (true) {
      std::cout << "Return? (y): ";
      char choice;
      std::cin.clear(); // clear error state
      std::cin >> choice;
      if (choice == 'y' || choice == 'Y') {
         std::cin.clear(); // clear error state
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
         return true; // User wants to return
      } else {
         std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
      }
   }
}