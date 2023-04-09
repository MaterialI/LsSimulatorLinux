#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>


// Disc : Opens  a directory for reading and reutnrs null if the file doesn't exist 

DIR* open_Dir(char* dir_path){
        DIR* dir = opendir(dir_path);
    if(!dir){return NULL;}
    return dir;
}


//Disc : Reads the contents of a file 
void name_Read_Entities(DIR* dir ){
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








void indoe_Read_Entities(DIR* dir){
    struct dirent* file_entity;
    file_entity = readdir(dir);
    struct stat s;
     while (file_entity != NULL)
    {   if((strcmp(file_entity->d_name , "..") && strcmp(file_entity->d_name , ".")  ))
        {   
            stat("/README.md" , &s);
             printf(" File ID is : %lu  File name is : %s\n ", s.st_ino  , file_entity->d_name);
            file_entity = readdir(dir);
        }
        else {break;}
    }
}



//Desc opens the given directory and reads it's contents  
// returns -1 if the file DNE 

int ls_Default(char* dir_path){
    
   DIR* dir =  opendir(dir_path);

    if(dir == NULL){printf("Bad Input : Cannot open the file \n"); return -1;}
    name_Read_Entities(dir);
}



//Desc opens the given directory and reads it's contents  
// returns -1 if the file DNE 

int i_Flag(char* dir_path){
    
   DIR* dir =  opendir(dir_path);

    if(dir == NULL){printf("Bad Input : Cannot open the file \n"); return -1;}
    indoe_Read_Entities(dir);
}




int main(int argc, char ** argv) {



    char* test = "/home/vagrant/Desktop/OS300/Assign4/Assign4_300/test_file1";
    i_Flag(test);


    return 0 ; 
}