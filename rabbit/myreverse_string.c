#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char* reverse_string(char* str)
{

    char tmp_char;
    size_t len = strlen(str);
    size_t i;

    for (i = 0; i < len / 2; i++)
    {
        tmp_char = str[len -1 -i];
        // The last character equals the first character
        str[len -1 -i] = str[i];
        // The first character equals the last character
        str[i] = tmp_char;
    }

    return str;
}


int main()
{

    char init_str[] = "cat";
    printf("Reversed string is %s", reverse_string(init_str));

    return 0;
}
