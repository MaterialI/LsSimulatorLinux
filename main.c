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
int ls_Default(char* dir_path){
    
    DIR* dir = opendir(dir_path);
    if(dir == NULL){printf("File cannot be open\n"); return -1;}
    struct dirent* file_entity;
    file_entity = readdir(dir);

     while (file_entity != NULL)
    {   if((strcmp(file_entity->d_name , "..") && strcmp(file_entity->d_name , ".")  ))
        {
             printf(" file name is : %s\n", file_entity->d_name);
            file_entity = readdir(dir);
        }
        else {break;}
      
    }
    
}




int main(int argc, char ** argv) {



    char* test = ".";
    ls_Default(test);



    return 0 ; 
}