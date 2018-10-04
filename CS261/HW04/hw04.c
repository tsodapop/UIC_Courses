#define SIZE 16
struct lnode {
 char str[SIZE];
 struct lnode *next;
};

struct lnode A[3][4][5];

struct lnode B;

int store_ele(int h, int i, int j, struct lnode dest) {
 A[h][i][j] = dest;
 return sizeof(A);
}

int main() {
    store_ele(3,4,5, B);
    return 0;
}
// int R = 3;
// int S = 4;
// int T = 5;

