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

void mainMenu() {
   while (true){
      std::cout << "+" << std::string(30, '-') << "+" << std::endl;
      std::cout << "|" << "Main Menu" << std::string(30 - 10, ' ') << "|" << std::endl;
      std::cout << "+" << std::string(30, '-') << "+" << std::endl;
      std::cout << "1. Member Login" << std::endl;
      std::cout << "2. Admin Login" << std::endl;
      std::cout << "3. Exit" << std::endl;

      int choice = getInputInRange(1,3);

      switch (choice) {
         case 1:
            memberMenu(Library &lib);
            break;
         case 2:
            adminMenu();
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
void memberMenu(Library &lib){

}
void adminMenu(Admin *ad, Library &lib){

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
