#include <bits/stdc++.h>
#include "share_fn/share_fn.h"

int main(int argc, char const *argv[]) {
   Library lib;
   lib.loadFromFile();
   // library.login(admin) -> 1. admin 2. member 3. exit 
   Admin* ad = new Admin();
   Member* mem = new Member();

   mainMenu(lib, ad, mem);

   delete ad;
   delete mem;
   return 0;
}
