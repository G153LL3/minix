#include <dirent.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define DIR_TYPE 4

int prof = 0;

void print(char *ruta);
void print_spaces(void);
void dfs(char *ruta);


void print(char *ruta)
{
    for (unsigned i = 0; i < strlen(ruta); i++)
    {
        printf("%c", ruta[i]);
    }   
}
void print_spaces()
{
    for (int i = 0 ; i < prof; i++)
    {
        printf("  ");
    }
}
void dfs(char *ruta)
{
    DIR* dir = opendir(ruta);
    if (dir == NULL)
    {
        printf("No access to ruta: \n");
        print(ruta);    
        printf("\n");
        return;
    }
    struct dirent* files = readdir(dir);
    while(files != NULL)
    {

        if (strcmp(files->d_name, ".") == 0 || strcmp(files->d_name, "..") == 0)
            goto cont;

        print_spaces();
        print(files->d_name);
        printf("\n");
        
        if (files->d_type == DIR_TYPE)
        {
            char tmp[4096];
            strcpy(tmp, ruta);
            strcat(tmp, "/");
            strcat(tmp, files->d_name);
            prof++;
            dfs(tmp);
            prof--;
        }
        cont:
            files = readdir(dir);
    }

    closedir(dir);
}

int main(int c_arg, char **args)
{
    char ruta[4096];
    if (c_arg == 1)
    {
        strcpy(ruta,"./");
        c_arg ++;
    } else {
        strcpy(ruta, args[1]);
    }
    if (c_arg != 2)
    {
        printf("Invalid tree usage: tree <ruta>");
        return 1;
    }
    print(ruta);
    dfs(ruta);
}

