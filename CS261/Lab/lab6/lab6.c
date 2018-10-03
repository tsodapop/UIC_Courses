#include <stdio.h>
int main(){
short int myArray[10];
int i;
char temp;
printf("Please enter 10 ints that are greater than -32768, but less than 32767:");
for(i=0;i<10;i++){
 scanf("%hd",&(myArray[i]));
 }
scanf("%c",&temp);
printf("press a key to continue:");
scanf("%c",&temp);
short int cube[2][3][4];
printf("Please enter 24 ints that are greater than -32768, but less than 32767:");
short int *myPtr;
myPtr = &(cube[0][0][0]);
for(i=0;i<24;i++){
 scanf("%hd",myPtr);
 myPtr++;
}
scanf("%c",&temp);
printf("press a key to continue:");
scanf("%c",&temp);
return 0;
}