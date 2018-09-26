#include <stdio.h>

int main (int argc, const char * argv[]) {
	printf("Please input the long int\n");
	int firstNibble, secondNibble;
	long int x;
	//intake user input for the nibbles they are interested in
	scanf("%lx", &x);
	printf("Please input the two nibble indexes to swap\n");
	scanf("%i%i", &firstNibble, &secondNibble);
	long int y = 0x0;
	long int z = 0x0;
	long int firstMask = 0x0F;
	long int secondMask = 0x0F;
	long int mainMask = 0x0;
	//spits out the original hex value
	printf("The original hex value is:    0x%lx\n", x);
	//this gets you the first nibble of interest and places it in the new location
	y = ((x >> (firstNibble + firstNibble + firstNibble + firstNibble)) & 0x0F);
	y = y << ( (secondNibble + secondNibble + secondNibble + secondNibble));
	//this gets you the second nibble of interest and places it in the new location
	z = ((x >> (secondNibble + secondNibble + secondNibble + secondNibble)) & 0x0F);
	z = z << ( (firstNibble + firstNibble + firstNibble + firstNibble ));
	//this concatenates the first and second nibbles with 0's in the remaining spots
	y = y | z;
	//this will get a 1111 in the first nibble's index
	firstMask = (firstMask << (firstNibble + firstNibble + firstNibble + firstNibble));
	//this will get a 1111 in the second nibble's index
	secondMask = (secondMask << (secondNibble + secondNibble + secondNibble + secondNibble));
	//this will concatenate the first and second masks and then invert it
	mainMask = (mainMask | firstMask);
	mainMask = (mainMask | secondMask);
	mainMask = (mainMask ^ 0xFFFFFFFFFFFFFFFF);
	//we then do an and operator to retain all values except where the main mask had 0's
	//the main mask had 0's where we wanted to update the values
	mainMask = (mainMask & x);
	//finally, we do an or operator with y and the main mask to update the 0 values inside
	//the main mask to be the newly updated values from y, giving us the updated 64 bit int
	y = (y | mainMask);
	printf("The updated hex value is now: 0x%lx\n", y);
 	return 0;
}