#include "member.h"

// Constructors
Member::Member(){}
Member::Member(std::string userID_i, std::string pwd_i, 
               std::string name_i, std::string email_i, 
               std::vector<std::string> issueBooks_i):
               User(userID_i,pwd_i), userID(userID_i), 
               name(name_i), email(email_i), issuedBooksID(issueBooks_i){}
Member::Member(std::string userID_i, std::string pwd_i, 
               std::string name_i, std::string email_i):
               User(userID_i, pwd_i), userID(userID_i),
               name(name_i), email(email_i){}