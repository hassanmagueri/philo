#include <string.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char s[7];

    s = "3lamya";
    strcat(s, "-"); 
    printf("%s\n", s);
    return 0;
}

