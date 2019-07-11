#include <stdio.h>

int main()
{
    {
        char str[] = "abcd efgh ijkl mnor";
        FILE *fp = fopen("data.txt", "w+");
        fputs(str, fp);
        fclose(fp);
    }

    {
        char str[10];
        FILE *fp = fopen("data.txt", "r+");
        fgets(str, sizeof(str), fp);
        fputs(str, fp);
        fclose(fp);
    }
}