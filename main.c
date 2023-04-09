#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>




int main(int argc, char ** argv) {


    
    if(argc < 2){
        // Just the ls command 
        printf("To Do : implement the ls\n ");
    }
    else if (argc ==2){
        // Do somehting with the flags 

    }

    else {
        printf("Bad input : too many commands\n");
    }



    return 0 ; 
}