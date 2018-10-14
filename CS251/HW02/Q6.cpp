#include <stdio.h>
#include <iostream>
using namespace std;

int minimax(double f[], double g[], int n) {
    int lowIndex = 0;
    int highIndex = n-1;
    int val = (lowIndex + highIndex)/2;

    if (n <= 0) {
        return 0;
    }
    while (lowIndex <= highIndex) {

        if (f[val] == g[val]) {
            return val; //they are both equal, and this is the minimized of the maximum
        }

        else if (f[val] < g[val]) {
            lowIndex = val + 1;
        }

        else if (f[val] > g[val]) {
            highIndex = val - 1;
        }
        val = (lowIndex + highIndex)/2;
    }

    return val;
}

int main() {
    double arr1[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 8, 9};
    double arr2[10] = {18,17,16,15,14,13,12,11,10, 9};

    int x = minimax(arr1,arr2, 10);
    cout << x << endl;
    
    return 0;
}