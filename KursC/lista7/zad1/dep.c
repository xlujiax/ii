#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dfs(char* filename);

typedef struct Self
{
    char* file;
    struct Self* next;
} List;

List* concat(char* file, List* old)
{
    List* head = malloc(sizeof(List));
    head->file = file;
    head->next = old;
    return head;
}

int contains(char* file, List* lst)
{
    List* i = lst;
    while(i)
    {
        if(0 == strcmp(file, i->file))
            return 1;
        i = i->next;
    }
    return 0;
}

int is_include(char* line, const int sz)
{
    char inc[sz];
    sscanf(line, "%s", &inc);
    if(0 == strcmp("#include", inc))
        return 1;
    return 0;
}

char* match_include(char* line, int sz)
{
    char file[sz];
     // %*s => pomija "#include"
     // \" => czyta "
     // %[^\"] => pomija z nastepnego ci¹gu znaków "
     // %s => czyta w³aœciw¹ nazwê pliku
    sscanf(line, "%*s \"%[^\"]%s", &file);
    char* copy = strcpy(malloc(sizeof(char) * sz), file); 
    return copy;
}

// dwie funkcje wzajemnie rekurencyjne - includes i dfs

void includes(char* filename)
{
    FILE* file;
    file = fopen (filename,"r");
    if(!file)
        {
            printf("plik o nazwie %s nie istnieje\n", filename);
            system("PAUSE");
            exit(0);
            return;
        }
    
    const int sz = 200;
    char line[sz];
        
    while(1)
    {
        fgets(line, sz, file);
        if(feof(file))
            break;
        if(is_include(line, sz))
        {
            char* copy = strcpy(malloc(sizeof(char) * sz), line); 
            
            dfs(match_include(copy,sz));
        }
        else
            printf("%s", line);
    }
    
    fclose(file);
}

List* visited = 0;

void dfs(char* filename)
{
    if(contains(filename, visited))
    {
        printf("wystêpuje cykl: %s\n", filename);
        system("PAUSE");
        exit(0);
        return;
    }
    
    char* copy = strcpy(malloc(sizeof(char) * 200), filename); 
    visited = concat(copy, visited);
    
    includes(filename);
}

int main(int argc, char *argv[])
{
    dfs("sample.txt");
    
    system("PAUSE");	
    return 0;
}
