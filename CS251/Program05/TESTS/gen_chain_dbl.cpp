
#include <iostream>
#include <time.h>


int main(int argc, char *argv[]){
  int i, n;

  n = 10;

  srand(time(NULL));

  if(argc == 2) {
    n = atoi(argv[1]);
  }

  for(i=1; i<=n; i++) {
    unsigned wt;

    int delta = 1;
    int dst;
    while(i+delta <= n) {
      dst = i+delta;
      wt = 1 + rand() % 999;
      std::cout << "v" << i << " v" << dst << " " << wt << "\n";
      delta *= 2;
    }

  }
  return 0;
}

