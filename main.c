#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>


//Desc 
int ls_Defult(char* dir_path){
    DIR* dir = opendir(dir_path);
    if(dir == NULL){printf("File cannot be open\n"); return -1;}
    struct dirent* file_entity;
    file_entity = readdir(dir);

    while (file_entity != NULL)
    {   
        printf(" file name is : %c\n", file_entity->d_type);
        file_entity = readdir(dir);
    }
    
}


int main(int argc, char ** argv) {



    char* test = ".";
    ls_Defult(test);



    return 0 ; 
}