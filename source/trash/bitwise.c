#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	
	printf("hola\n");
	
	char a = 0b1001;
	printf("a: %d\n", a);
	printf("a: %d\n", a >> 1);
	printf("a: %d\n", a >> 2);
	printf("a: %d\n", a >> 3);
	printf("a: %d\n", a >> 4);
	printf("a: %d\n", a >> 5);
	printf("a: %d\n", a % 2);
	printf("a: %d\n", a % 0b0010);
	
	return 0;
// int CountOnesFromInteger(unsigned int value) {
    // int count;
    // for (count = 0; value != 0; count++, value &= value-1);
    // return count;
// }
}

