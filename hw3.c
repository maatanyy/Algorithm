#include <stdio.h>

int main()
{

    FILE *pFile = fopen("input.txt", "r");
    float intTemp = -1;
    int extraNumber = 0;

    // 파일 읽기 성공
    while (!feof(pFile))
    {
        fscanf(pFile, "%f", &intTemp);

        if (intTemp > 5000)
        {
            extraNumber++;
        }
        printf("%f ", intTemp);
    }

    printf("\n");
    printf("number > 5000: %d", extraNumber);
    fclose(pFile); //close file
    return 0;
}
