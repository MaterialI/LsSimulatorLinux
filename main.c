#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>


// Opens 

DIR* open_Dir(char* dir_path){
        DIR* dir = opendir(dir_path);
    if(!dir){return NULL;}
    return dir;
}

void read_Entities(DIR* dir ){
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




//Desc 
int ls_Default(char* dir_path){
    
   DIR* dir =  opendir(dir_path);

    if(dir == NULL){printf("Bad Input : Cannot open the file \n"); return -1;}
    read_Entities(dir);    
}








int main(int argc, char ** argv) {



    char* test = "/home/vagrant/Desktop/OS300/Assign4/Assign4_300/test_file1";
    ls_Default(test);



    return 0 ; 
}