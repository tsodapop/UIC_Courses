
#include <iostream>
#include <time.h>

void pvtx(int i, int j) {

  std::cout << "v" << i << "_" << j << " ";

}

int inc(int x, int n) {
  return (x+1)%n;
}

int dec(int x, int n) {
  return (x==0 ? (n-1) : x-1);
}

int main(int argc, char *argv[]){
  int i, j, n;
  bool weighted = false;

  n = 10;

  srand(time(NULL));

  if(argc >= 2) {
    n = atoi(argv[1]);
  }
  if(argc == 3 && argv[2][0] == 'w') {
    weighted = true;
  }

  for(i=0; i<n; i++) {

    for(j=0; j<n; j++) {

      // north
      pvtx(i,j);
      pvtx(dec(i, n), j);
      if(weighted) 
        std::cout << 1+(rand() % 999) << "\n";
      else
        std::cout << " 1\n";

      // south
      pvtx(i,j);
      pvtx(inc(i, n), j);
      if(weighted) 
        std::cout << 1+(rand() % 999) << "\n";
      else
        std::cout << " 1\n";

      // east
      pvtx(i,j);
      pvtx(i, inc(j, n));
      if(weighted) 
        std::cout << 1+(rand() % 999) << "\n";
      else
        std::cout << " 1\n";

      // west
      pvtx(i,j);
      pvtx(i, dec(j, n));
      if(weighted) 
        std::cout << 1+(rand() % 999) << "\n";
      else
        std::cout << " 1\n";
    }


  }
  return 0;
}

