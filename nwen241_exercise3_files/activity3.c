#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // (1) Initialize sum to 0.
    int sum = 0;
    // (2) Loop through argv[1], argv[2], ..., argv[argc-1]
    //     and add each integer to sum.
    for(int i = 1; i < argc; i++){
        int num;
        if(sscanf(argv[i], "%d", &num) == 1){
            sum += num;
        }
    }
    // (3) Print the value of sum.
    printf("%d\n", sum);
    return 0;
}