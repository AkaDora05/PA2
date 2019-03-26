//Eunjun Kim
//exk170230
//CS3371.0W1
//03/04/19
//Nhut Nguyen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char **argv) {
    //if argc is not 2, then output the
    //following error message
    if (argc != 2) {
        printf("Invalid arguments\n");
        return -1;
    }
    char option = 0;

    //validate the following options:
    //directories, files, bytes
    //otherwise print out the error message
    if(!strcmp(argv[1], "-d")) {
        option = 'd';
    } else if (!strcmp(argv[1], "-f")) {
        option = 'f';
    } else if (!strcmp(argv[1], "-b")) {
        option = 'b';
    } else {
        printf("Invalid option\n");
        return -1;
    }

    //loop through while run is true
    bool run = true;
    while (run) {
        //initialize variables
        int stringSize = 0;
        char *line = NULL;
        //get the line and set equal to size
        int size = getline(&line, &stringSize, stdin);
        if (size == -1) break;

        //do the following based on the option
        if ((option == 'd' && strstr(line, "directories")) ||
            (option == 'f' && strstr(line, "files")) ||
            (option == 'b' && strstr(line, "bytes"))) {
            printf("%s", line);
            run = false;
        }
    }

    return 0;
}



