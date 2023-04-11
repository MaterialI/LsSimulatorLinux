#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <time.h>


static char* test = "/home/vagrant/Documents/CMPT276/project/parabix-devel-master";
//static char* test = "./Test";
// Disc : Opens  a directory for reading and reutnrs null if the file doesn't exist 


typedef void (*flag_func)(DIR* , char*);

DIR* open_Dir(char* dir_path){
        DIR* dir = opendir(dir_path);
    if(!dir){return NULL;}
    return dir;
}



void getUserName(uid_t uid , char* buffer) {
    struct passwd *pw = getpwuid(uid);
    if(pw != NULL){ strcpy(buffer ,  pw->pw_name);}
    else{ strcpy(buffer , "---");}
 
}





void* getGroupName(gid_t grpNum , char* buffer ) {


struct group *grep = getgrgid(grpNum); 
    if(grep != NULL){ strcpy(buffer ,  grep->gr_name);}
    else{ strcpy(buffer , "---");}
}




//Disc : Reads the contents of a file 
void name_Read_Entities(DIR* dir ){
    struct dirent* file_entity;
    file_entity = readdir(dir);
    int i = 1;
     while (file_entity != NULL)
    { 
        if(strcmp(file_entity->d_name , ".") != 0  && strcmp(file_entity->d_name , "..") != 0 ) 
    {  
       
        printf("%-5s  ",   file_entity->d_name );
         if(i%4 == 0){printf("\n" );}
         i++;

    
    }
        
        file_entity = readdir(dir);
    }
    printf("\n");

}





//
void indoe_Read_Entities(DIR* dir){
    int i = 1; 
    struct dirent* file_entity;
    file_entity = readdir(dir);
     while (file_entity != NULL)
    {   if(strcmp(file_entity->d_name , ".") != 0  && strcmp(file_entity->d_name , "..") != 0 ) 
    {  
       
        printf(" %8lu   %-8s  ",  file_entity->d_ino, file_entity->d_name );
         if(i%4 == 0){printf("\n" );}
         i++;

    
    }
        
        file_entity = readdir(dir);
    }
   printf("\n");
}




void permission(char* buffer , int permission){ 
    if(permission == 7){strcpy(buffer,"rwx");} 
    else  if(permission == 6){strcpy(buffer,"rw-");} 
    else  if(permission == 5){strcpy(buffer,"r-x");} 
    else  if(permission == 4){strcpy(buffer,"r--");} 
    else  if(permission == 3){strcpy(buffer,"-wx");} 
    else  if(permission == 2){strcpy(buffer,"-w-");}
     else  if(permission == 1){strcpy(buffer,"--x");}
     else  if(permission == 0){strcpy(buffer,"---");}
}




void L_Read_Entities(DIR* dir , char* path)
{
    struct dirent* file_entity;
    file_entity = readdir(dir);

    while (file_entity != NULL)
    {
    
    
   
    if(strcmp(file_entity->d_name , ".") != 0  && strcmp(file_entity->d_name , "..") != 0 ) {
        char new_path[300] = {0} ; 
    strcpy(new_path , path );
         strcat(new_path, "/");
    strcat(new_path, file_entity->d_name);
    // Get the link file name


         struct stat  s; 
        lstat(new_path , &s);
        
    // Masking out the permission info 
        int owner = ((s.st_mode >> 6) & ((1 << 3) - 1));
        int group = ((s.st_mode >> 3) & ((1 << 3) - 1));
        int other = ((s.st_mode) & ((1 << 3) - 1));

        char owner_per[4];
        permission(owner_per , owner);


         char group_per[4];
        permission(group_per , group);


         char other_per[4];
        permission(other_per , other);
        // 

        // Getting the owners and groups  names 
           char owner_name[300]  ; char groups_name[300];

        getUserName(s.st_uid , owner_name);
        getGroupName(s.st_gid , groups_name);
        // 

// Check for symbolic links 
           char link_buffer[300];
        int n_link = readlink(new_path , link_buffer, 300);
        link_buffer[n_link] = '\0';

        char file_type[2]; 
        if(n_link > 1){strcpy(file_type , "l");}
        else if(file_entity->d_type == 4){strcpy(file_type , "d");}
        else {strcpy(file_type , "-");}


    struct tm lt;
    localtime_r(&(s.st_mtim), &lt);
        char time[300];
        strftime(time, 300, "%b %d %H:%M", &lt );
        //To Do handel the case of prinitng the year instead of minutes and seconds 

        // Handel the cases of links 
            if(n_link > 1){
             printf("%s%s%s%s %s %s  %-5lu %s %s-> %s\n", file_type , owner_per, group_per , other_per , owner_name , groups_name, s.st_size, time, file_entity->d_name , link_buffer);
            }
            else {
                 printf("%s%s%s%s %s %s  %-5lu %s %s\n", file_type , owner_per, group_per , other_per , owner_name , groups_name, s.st_size , time, file_entity->d_name );
            }
       
    }
        file_entity = readdir(dir);
    }
    
}




void LI_Read_Entities(DIR* dir , char* path)
{
    struct dirent* file_entity;
    file_entity = readdir(dir);

    while (file_entity != NULL)
    {
    
    
   
    if(strcmp(file_entity->d_name , ".") != 0  && strcmp(file_entity->d_name , "..") != 0 ) {
        char new_path[300] = {0} ; 
    strcpy(new_path , path );
         strcat(new_path, "/");
    strcat(new_path, file_entity->d_name);
    // Get the link file name


         struct stat  s; 
        lstat(new_path , &s);
        
    // Masking out the permission info 
        int owner = ((s.st_mode >> 6) & ((1 << 3) - 1));
        int group = ((s.st_mode >> 3) & ((1 << 3) - 1));
        int other = ((s.st_mode) & ((1 << 3) - 1));

        char owner_per[4];
        permission(owner_per , owner);


         char group_per[4];
        permission(group_per , group);


         char other_per[4];
        permission(other_per , other);
        // 

        // Getting the owners and groups  names 
           char owner_name[300]  ; char groups_name[300];

        getUserName(s.st_uid , owner_name);
        getGroupName(s.st_gid , groups_name);
        // 

// Check for symbolic links 
           char link_buffer[300];
        int n_link = readlink(new_path , link_buffer, 300);
        link_buffer[n_link] = '\0';

        char file_type[2]; 
        if(n_link > 1){strcpy(file_type , "l");}
        else if(file_entity->d_type == 4){strcpy(file_type , "d");}
        else {strcpy(file_type , "-");}


    struct tm lt;
    localtime_r(&(s.st_mtim), &lt);
        char time[300];
        strftime(time, 300, "%b %d %H:%M", &lt );
        //To Do handel the case of prinitng the year instead of minutes and seconds 

        // Handel the cases of links 
            if(n_link > 1){
             printf("%-8lu %s%s%s%s %s %s  %-5lu %s %s-> %s\n", s.st_ino, file_type , owner_per, group_per , other_per , owner_name , groups_name, s.st_size, time, file_entity->d_name , link_buffer);
            }
            else {
                 printf("%-8lu %s%s%s%s %s %s  %-5lu %s %s\n", s.st_ino, file_type , owner_per, group_per , other_per , owner_name , groups_name, s.st_size , time, file_entity->d_name );
            }
       
    }
        file_entity = readdir(dir);
    }



}
void R_Read_Entities(DIR* dir, char* aPath, flag_func passedFunc){

    struct dirent* file_entity;
    printf("%s\n", aPath);
    passedFunc(dir , aPath);
    dir = open_Dir(aPath);
    file_entity = readdir(dir);
    
     while (file_entity != NULL)
    {   
        if((strcmp(file_entity->d_name , "..") && strcmp(file_entity->d_name , ".")  ))
        {
             char path[300] = {0};
            if(file_entity->d_type == 4){
                strcat(path, aPath);
                strcat(path, "/");
                strcat(path, file_entity->d_name);
                DIR* dr = opendir(path);
                printf("\n");
                R_Read_Entities(dr, path,passedFunc);
            }  
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
    L_Read_Entities(dir , dir_path);

}


int il_Flag(char* dir_path){
    
   DIR* dir =  opendir(dir_path);

    if(dir == NULL){printf("Bad Input : Cannot open the file \n"); return -1;}
    LI_Read_Entities(dir, dir_path);
}
//Desc opens the given directory and reads it's contents  
// returns -1 if the file DNE 


int i_Flag(char* dir_path){
    
   DIR* dir =  opendir(dir_path);

    if(dir == NULL){printf("Bad Input : Cannot open the file \n"); return -1;}
    indoe_Read_Entities(dir);
}
int R_Flag(char* dir_path, flag_func passedFunc){
    
   DIR* dir =  opendir(dir_path);

    if(dir == NULL){printf("Bad Input : Cannot open the file \n"); return -1;}
    R_Read_Entities(dir, dir_path, passedFunc);
}

void parse_argv1(char* flags, int* ilR)
{
    for(int i =0;flags[i]!='\0';i++)
    {
        if(flags[i] == 'i')
            ilR[0] = 1;
        if(flags[i] == 'l')
            ilR[1] = 1;
        if(flags[i] == 'R')
            ilR[2] = 1;

    }
}

int main(int argc, char ** argv) {

    char* path = ""; 
    char* flags = argv[1];
    int ilR[3];
    if(argc < 2)
    {
        path = ".";
        ilR[0] = 0;
        ilR[1] = 0;
        ilR[2] = 0;
    }
    else if(argc == 2 && argv[1][0] == '-')
    {
        path = ".";
        parse_argv1(flags, &ilR);    
        
    }
    else if(argc == 2 && argv[1][0] != '-')
    {
        path = argv[1];
        ilR[0] = 0;
        ilR[1] = 0;
        ilR[2] = 0;
    }
    else if(argc == 3)
    {
        path = argv[2];
        parse_argv1(flags, &ilR);
    }
    
    //recursive
    if(ilR[2] == 1)
    {
        //i
        if(ilR[0] == 1 && ilR[1] != 1)
        {
            R_Flag(path, indoe_Read_Entities);
        }
        else if(ilR[0] != 1 && ilR[1] == 1)
        {
            R_Flag(path, L_Read_Entities);
        }
        else if(ilR[0] == 1 && ilR[1] == 1)
        {
            R_Flag(path, LI_Read_Entities);
        }
        else
        {
            R_Flag(path, name_Read_Entities);
        }
    }
    else
    {
        if(ilR[0] == 1 && ilR[1] != 1)
        {
            i_Flag(path);
        }
        else if(ilR[0] != 1 && ilR[1] == 1)
        {
            l_Flag(path);
        }
        else if(ilR[0] == 1 && ilR[1] == 1)
        {
            il_Flag(path);
        }
        else
        {
            ls_Default(path);
        }
    }

    return 0 ; 
}