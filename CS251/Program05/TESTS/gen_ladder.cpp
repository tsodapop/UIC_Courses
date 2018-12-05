
#include <iostream>
#include <time.h>


int main(int argc, char *argv[]){
  int i, n;

  n = 10;

  srand(time(NULL));

  if(argc == 2) {
    n = atoi(argv[1]);
  }

  for(i=1; i<n; i++) {
    unsigned wt;

    wt = 1 + rand() % 999;
    std::cout << "a" << i << " a" << i+1 << " " << wt << "\n";
    wt = 1 + rand() % 999;
    std::cout << "a" << i << " b" << i+1 << " " << wt << "\n";

    wt = 1 + rand() % 999;
    std::cout << "b" << i << " b" << i+1 << " " << wt << "\n";
    wt = 1 + rand() % 999;
    std::cout << "b" << i << " a" << i+1 << " " << wt << "\n";

  }
  return 0;
}

