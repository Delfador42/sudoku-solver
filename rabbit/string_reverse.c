#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// A void function returns no value
char* str_reverse(char *str_in)
{
  char tmp;
  
  size_t ii = 0;
  size_t len = strlen(str_in); // `strlen()` is part of the c standard library
                               // NOTE: length returned by `strlen` DOESN'T
                               //       include the terminating NULL byte ('\0')
                               
  // in C99 and newer versions, you can directly declare loop control variables
  // in the loop's parentheses. e.g., `for (size_t ii = 0; ...`
  for (ii = 0; ii < len / 2; ii++) {
    // tmp equals the first character in the string
    tmp = str_in[ii];
    // The first character equals the last character
    str_in[ii] = str_in[len - ii - 1]; // ii-th char from end
    // the last character equals the first character
    str_in[len - ii - 1] = tmp;
  }

  return str_in;
}


int main() {
    // This is a char array and is mutable
    // If the string is an array then it is mutable
    char init_str[] = "cat";
    // Declare a char array
    // +1 for the null byte
    //char reversed_string[strlen(init_str) + 1];
    //strcpy(reversed_string, str_reverse(init_str));

    // Declare a pointer-to-char, a pointer to the first element of the array
    // It's good practice to use const char* when referring to a string
    // literal, since string literals cannot be modified
    const char* reversed_string = str_reverse(init_str);
    printf("The string reversed is %s", reversed_string);
}
