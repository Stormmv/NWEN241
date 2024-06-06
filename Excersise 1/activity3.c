#include <stdio.h>

int main(void) {
        printf("Enter a string: ");
    	char input[100];
    	scanf(" %[^\n]", input);
    	printf("%s\n", input);
    	return 0;
}
