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
    { 
        if(strcmp(file_entity->d_name , ".") != 0  && strcmp(file_entity->d_name , "..") != 0 ) {  printf("%s\n",   file_entity->d_name );}
        
        file_entity = readdir(dir);
}

}






void indoe_Read_Entities(DIR* dir){
    int i = 3; 
    struct dirent* file_entity;
    file_entity = readdir(dir);
     while (file_entity != NULL)
    {   if(strcmp(file_entity->d_name , ".") != 0  && strcmp(file_entity->d_name , "..") != 0 ) 
    {  
        if(i%2 == 0){printf(" %-5lu %-5s\n",  file_entity->d_ino, file_entity->d_name );}
        else {printf(" %-5lu %-5s  ",  file_entity->d_ino, file_entity->d_name );}
        
    
    }
        
        file_entity = readdir(dir);
        i++;
    }
    printf("\n");
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



    char* test = "/home/vagrant/Desktop/OS300/Assign4/Assign4_300/test_file";
    i_Flag(test);


    return 0 ; 
}