#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE* input = fopen("./input.txt", "r");
    int nKeyBuf[2] = { 0, 0 };
    char cCharBuf[10];
    int nLineLen = 0;
    int nBuf = 0;

    while (fscanf(input, "%[^\n]", cCharBuf))
    {
        nBuf = atoi(cCharBuf);
        printf("Read: %d \n", nBuf);
        // fgetc(input);
    }
    

    return 0;
}