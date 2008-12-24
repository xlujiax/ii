// Maciej Pacut
// lista 8 zad 1

#include <stdio.h>
#include <stdlib.h>

int ungets(char* str, FILE* stream) {
   if (!str || !stream) return -1;
   size_t len = strlen(str);
   int i;
   for (i=len-1; i>=0; i--) if (ungetc(str[i], stream) == EOF) return -1;
   return len;
}

int matches(char* text, char* pattern, int len)
{
    int i;
    for(i = 0; i < len; ++i)
    {
        if(pattern[i] == '?')
            continue;
        else if(pattern[i] != text[i])
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("usage: pattern.exe file pattern\n");
        return 0;
    }
    char* filename = argv[1];
    char* pattern = argv[2];
    int pattern_len = strlen(pattern);
    
    char* text = malloc(sizeof(char) * pattern_len);
    
    char* last = malloc(sizeof(char) * pattern_len);
    
    FILE* file = fopen(filename, "r");
    while(!feof(file))
    {
        fgets(text, pattern_len + 1, file);
        if(matches(text, pattern, pattern_len))
        {
            strcpy(last, text);
        }
        ungets(text + 1, file);
    }
    
    printf("%s\n", last);
    
    return 0;
}
