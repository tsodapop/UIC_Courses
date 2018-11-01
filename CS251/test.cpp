#include <iostream>
using namespace std;

struct lnode {
    char lastname[20];
    char firstname[20];
    int *next;
}

int main() {
    int x = sizeof(lnode);
    print(x);
    return 0;
}