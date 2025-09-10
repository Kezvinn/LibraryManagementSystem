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
        std::cerr << "\033[31m [ERROR] titles and lines must have the same number of elements.\033[0m\n";
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
   std::string input;
   
   while (true) {
      std::cout << "Enter a number (" << min << " - " << max << "): ";
      std::getline(std::cin, input);


      if (isValidInt(input)) {
         int value = std::stoi(input);
         if (value >= min && value <= max) {
            return value;  // ✅ valid input
         } else {
            std::cout << "\033[31m[ERROR] Out of range. Please try again.\033[0m\n";
            continue;
         }
      } else {
         std::cout << "\033[31m[ERROR] Invalid input. Please enter a number.\033[0m\n";
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
         std::cout << "1. View Member Info\n";
         std::cout << "2. Edit Member Info\n";
         std::cout << "3. View Issued Books\n";
         std::cout << "4. Borrow Book\n";
         std::cout << "5. Return Book\n";
         std::cout << "6. Logout\n";

         int choice = getInputInRange(1, 6);

         switch (choice) {
            case 1:
               mem->displayMemberInfo();
               if (returnPrompt()){
                  break;
               }
            case 2:
               mem->editMemberInfo(lib);
               if (returnPrompt()){
                  break;
               }
            case 3:
               mem->displayIssuedBookIDs();
               if (returnPrompt()) {
                  break;
               }               
            case 4:
               mem->borrowBook(lib);
               if (returnPrompt()){
                  break;
               }
            case 5:
               mem->returnBook(lib);
               break;
            case 6:
               mem->logout(lib);
               return; // Exit member menu
            default:
               break;
         }
      }

   } 
   // else {
   //    // printBoxCenter("Login Failed", 30);
   //    // std::cout << "Login failed. Please try again.\n";
   // }
}
void adminMenu(Admin *ad, Library &lib){
   // login first
   bool loginStatus = ad->login();
   if (loginStatus == true) {
      while (true) {
         printBoxCenter("Admin Menu", 30);
         std::cout << "1. View All Members.\n";
         std::cout << "2. Add Member.\n";
         std::cout << "3. Remove Member.\n";
         std::cout << "4. View All Books.\n";
         std::cout << "5. Edit Book Info.\n";
         std::cout << "6. Add Book.\n";
         std::cout << "7. Remove Book.\n";
         std::cout << "8. Logout.\n";

         int choice = getInputInRange(1, 8);

         switch (choice) {
            case 1:  // View all members
               ad->viewAllMembers(lib);
               if (returnPrompt()){
                  break;
               }
            case 2:  // Add member
               ad->addMember(lib);
               if (returnPrompt()){
                  break;
               }
            case 3: // Remove member
               ad->removeMember(lib);
               if (returnPrompt()){
                  break;
               }
               
            case 4: // View all books
               ad->viewAllBooks(lib);
               if (returnPrompt()){
                  break;
               }   
               
            case 5:  // Edit book info
               ad->editBookInfo(lib);
               if(returnPrompt()){
                  break;
               }
                              
            case 6: // Add book
               ad->addBook(lib);
               if (returnPrompt()){
                  break;
               }
            case 7: // Remove book
               ad->removeBook(lib);
               if (returnPrompt()) {
                  break;
               }
            case 8: // Logout
               return; // Exit admin menu
            default:
               break;
         }
      }   
   }
   else {
      std::cout << "\033[31m[ERROR] Login failed. Please try again.\033[0m\n";
   }
}


// Regex functions
bool isValidName(const std::string &input){
   std::regex pattern(R"(^[A-Za-z0-9\s'.,:-]+$)");
   return std::regex_match(input, pattern);
}

bool isValidInt(const std::string &input){
   std::regex pattern(R"(^[1-9]\d*$)");
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
         std::cout << "\033[31m[ERROR] Invalid input. Please enter 'y' or 'n'.\033[0m\n";
      }
   }
}

// Helper: split string into chunks of size 'width'
std::vector<std::string> splitToChunks(const std::string& s, int width) {
   std::vector<std::string> chunks;
   for (size_t i = 0; i < s.size(); i += width) {
      chunks.push_back(s.substr(i, width));
   }
   if (chunks.empty()) chunks.push_back(""); // handle empty
   return chunks;
}

void printTable(const std::vector<std::string>& Titles, std::vector<std::vector<std::string>>& Data) {
   int nCols = Titles.size();
   for (const auto& row : Data) {
      if ((int)row.size() != nCols) {
         std::cerr << "\033[31m[ERROR] Each row in Data must have the same number of columns as Titles!\033[0m\n";
         return;
      }
   }

   // Compute column widths
   std::vector<int> colWidths(nCols, 10); // default min width = 10
   for (int c = 0; c < nCols; c++) {
      colWidths[c] = std::max(colWidths[c], (int)Titles[c].size());
      for (const auto& row : Data) {
         int len = row[c].size();
         if (len > colWidths[c]) colWidths[c] = len;
      }
   }

   // Print horizontal line
   auto printLine = [&]() {
      std::cout << "+";
      for (int c = 0; c < nCols; c++) {
         std::cout << std::string(colWidths[c], '-') << "+";
      }
      std::cout << "\n";
   };

   // Print header
   printLine();
   std::cout << "|";
   for (int c = 0; c < nCols; c++) {
      std::cout << std::setw(colWidths[c]) << std::left << Titles[c] << "|";
   }
   std::cout << "\n";
   printLine();

   // Print data rows
   for (const auto& row : Data) {
      // Split each cell into chunks
      std::vector<std::vector<std::string>> rowChunks(nCols);
      size_t maxLines = 0;
      for (int c = 0; c < nCols; c++) {
         rowChunks[c] = splitToChunks(row[c], colWidths[c]);
         if (rowChunks[c].size() > maxLines)
               maxLines = rowChunks[c].size();
      }

      // Print wrapped row
      for (size_t line = 0; line < maxLines; line++) {
         std::cout << "|";
         for (int c = 0; c < nCols; c++) {
               std::string chunk = (line < rowChunks[c].size()) ? rowChunks[c][line] : "";
               std::cout << std::setw(colWidths[c]) << std::left << chunk << "|";
         }
         std::cout << "\n";
      }
      printLine();
   }
}