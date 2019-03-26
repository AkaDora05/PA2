//Eunjun Kim
//exk170230
//CS3371.0W1
//03/04/19
//Nhut Nguyen

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

//Function prototype
void getNumberRecursive(char *directName, int *numBytes, int *numDirect, int *numPlain);

int main(int argc, char **argv) {
    //Initialize variables
    int numBytes=0;
    int numDirectories=0;
    int numPlainFiles=0;
	
	displayVersion();
	
    //stop if argc is not equal to 2
    //call the recursive function
    if (argc != 2) return 0;
    getNumberRecursive(argv[1], &numBytes, &numDirectories, &numPlainFiles);

    //print out the number of directories, plain files, and bytes occupied in directory
    printf("The total number of directories in %s is: %i\n", argv[1], numDirectories);
    printf("The total number of files in %s is: %i\n", argv[1], numPlainFiles);
    printf("The total number of bytes occupied by all files in %s is: %i\n", argv[1], numBytes);
    return 0;
}

//recursively get the number of directories, plain files, and bytes
void getNumberRecursive(char *directName, int *numBytes, int *numDirect, int *numPlain) {
    //pointers initialized
    DIR *dirPtr = opendir(directName);
    struct dirent *direntPtr;

    //if the pointer points to null, just return
    if (dirPtr == NULL) {
        return;
    }

    //while the pointer is not pointing at null, do the following
    while ((direntPtr=readdir(dirPtr)) != NULL) {
        //make a space for the new string
        char buffer[1000];
        snprintf(buffer, 1000, "%s/%s", directName, direntPtr->d_name);

        //if the pointer is poiting at the directory, do the following
        if (direntPtr->d_type == DT_DIR) {
            //continue as long as the directory name is not . or ..
            //then increment the number of directory
            if (!strcmp(direntPtr->d_name, ".") || !strcmp(direntPtr->d_name, "..")) continue;
            (*numDirect)++;

            //call the recursive function back
            getNumberRecursive(buffer, numBytes, numDirect, numPlain);
        }
        //if the pointer is not pointing at the directory
        //do the following
        else if (direntPtr->d_type != DT_DIR) {
            //increment the number of plain files
            (*numPlain)++;
            struct stat fileStat;
            stat(buffer, &fileStat);
            //get the total amount of bytes occupied in directory
            (*numBytes) = *numBytes + fileStat.st_size;
        }
    }
    //close at the end
    closedir(dirPtr);
    return;
}


