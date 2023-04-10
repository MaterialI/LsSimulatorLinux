#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

//static char* test = "/home/vagrant/Documents/CMPT276/project/parabix-devel-master";
static char* test = "./Test";
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
        if(strcmp(file_entity->d_name , ".") != 0  && strcmp(file_entity->d_name , "..") != 0 ) 
        {  
            printf("%s\n",   file_entity->d_name );
        }
        
        file_entity = readdir(dir);
}

}





//
void indoe_Read_Entities(DIR* dir){
    int i = 3; 
    struct dirent* file_entity;
    printf("four\n");
    file_entity = readdir(dir);
     while (file_entity != NULL)
    {   
        if(strcmp(file_entity->d_name , ".") != 0  && strcmp(file_entity->d_name , "..") != 0 ) 
        {  
            if(i%2 == 0)
            {
                printf(" %-5lu %-5s\n",  file_entity->d_ino, file_entity->d_name );
            }
            else {
                printf(" %-5lu %-5s  ",  file_entity->d_ino, file_entity->d_name );
            }
            
        
        }
        
        file_entity = readdir(dir);
        i++;
    }
    printf("\n");
}

void L_Read_Entities(DIR* dir)
{
    struct dirent* file_entity;
    file_entity = readdir(dir);

    struct stat s;
     while (file_entity != NULL)
    {   if((strcmp(file_entity->d_name , "..") && strcmp(file_entity->d_name , ".")  ))
        {   
            stat(file_entity->d_name , &s);
             printf(" File ID is : %lu  File name is : %s\n ", s.st_ino  , file_entity->d_name);
            file_entity = readdir(dir);
        }
        else {break;}
    }
}
void R_Read_Entities(DIR* dir, char* aPath){
   //printf("three\n");
    struct dirent* file_entity;
   // printf("four\n");
    file_entity = readdir(dir);
   // printf("five\n");

    struct stat s;
     while (file_entity != NULL)
    {   
        if((strcmp(file_entity->d_name , "..") && strcmp(file_entity->d_name , ".")  ))
        {
            char path[100] = {0};
            if(file_entity->d_type == 4){
                strcat(path, aPath);
                strcat(path, "/");
                strcat(path, file_entity->d_name);
                //printf("%s", path);
                //printf("one\n");
                DIR* dr = opendir(path);
                //printf("two\n");
                R_Read_Entities(dr, path);
            }
              
            
            stat(path, &s);
             printf("%s\n ", file_entity->d_name);
            
        }
        file_entity = readdir(dir);
    }
}






//Desc opens the given directory and reads it's contents  
// returns -1 if the file DNE 

int ls_Default(char* dir_path){
    
   DIR* dir =  opendir(dir_path);

    if(dir == NULL){printf("Bad Input : Cannot open the file \n"); return -1;}
    name_Read_Entities(dir);
}

int l_Flag(char* dir_path)
{
    DIR* dir =  opendir(dir_path);
    if(dir == NULL){printf("Bad Input : Cannot open the file \n"); return -1;}
    L_Read_Entities(dir);

}



//Desc opens the given directory and reads it's contents  
// returns -1 if the file DNE 

int i_Flag(char* dir_path){
    
   DIR* dir =  opendir(dir_path);

    if(dir == NULL){printf("Bad Input : Cannot open the file \n"); return -1;}
    indoe_Read_Entities(dir);
}
int R_Flag(char* dir_path){
    
   DIR* dir =  opendir(dir_path);

    if(dir == NULL){printf("Bad Input : Cannot open the file \n"); return -1;}
    R_Read_Entities(dir, test);
}



int main(int argc, char ** argv) {



    
    R_Flag(test);


    return 0 ; 
}