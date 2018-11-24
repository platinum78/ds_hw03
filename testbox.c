#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int num = 10;
    int* npNum = &num;
    int nPointer = (int)npNum;
    printf("%d \n", nPointer);
    int* convert = (int*)nPointer;
    printf("%d \n", *convert);
    

    return 0;
}