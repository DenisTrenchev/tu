#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

int lineCheck(char* line, size_t length){
    int i = 0;
    while(i < length){
        if (!(isspace(line[i]))){
            return 0;
        }
        i++;
    }
    return 1;
}

int operatorCheck(char* buff, size_t read_bytes){
    int counter = 0;
    int operators = 0;
    while(counter < read_bytes){    
        if(buff[counter] == '+' && buff[counter + 1] == '+'){
            operators++;
            counter++;
        }else if(buff[counter] == '+' && buff[counter + 1] == '='){
            operators++;
            counter++;
        }else if(buff[counter] == '+'){
            operators++;
        }else if(buff[counter] == '-' && buff[counter + 1] == '-'){
            operators++;
            counter++;
        }else if(buff[counter] == '-' && buff[counter + 1] == '='){
            operators++;
            counter++;
        }else if(buff[counter] == '-'){
            operators++;
        }else if(buff[counter] == '*' && buff[counter + 1] == '='){
            operators++;
            counter++;
        }else if(buff[counter] == '*'){
            operators++;
        }else if(buff[counter] == '/' && buff[counter + 1] == '='){
            operators++;
            counter++;
        }else if(buff[counter] == '/'){
            operators++;
        }else if(buff[counter] == '%' && buff[counter + 1] == '='){
            operators++;
            counter++;
        }else if(buff[counter] == '%'){
            operators++;
        }else if(buff[counter] == '<' && buff[counter + 1] == '<' && buff[counter + 2] == '='){
            operators++;
            counter += 2;
        }else if(buff[counter] == '<' && buff[counter + 1] == '<'){
            operators++;
            counter ++;
        }else if(buff[counter] == '<' && buff[counter + 1] == '='){
            operators++;
            counter++;
        }else if(buff[counter] == '<'){
            operators++;
        }else if(buff[counter] == '>' && buff[counter + 1] == '>' && buff[counter + 2] == '='){
            operators++;
            counter += 2;
        }else if(buff[counter] == '>' && buff[counter + 1] == '>'){
            operators++;
            counter ++;
        }else if(buff[counter] == '>' && buff[counter + 1] == '='){
            operators++;
            counter++;
        }else if(buff[counter] == '>'){
            operators++;
        }else if(buff[counter] == '!' && buff[counter + 1] == '='){
            operators++;
            counter++;
        }else if(buff[counter] == '!'){
            operators++;
        }else if(buff[counter] == '&' && buff[counter + 1] == '&'){
            operators++;
            counter++;
        }else if(buff[counter] == '&' && buff[counter + 1] == '='){
            operators++;
            counter++;
        }else if(buff[counter] == '&'){
            operators++;
        }else if(buff[counter] == '|' && buff[counter + 1] == '|'){
            operators++;
            counter++;
        }else if(buff[counter] == '|' && buff[counter + 1] == '='){
            operators++;
            counter++;
        }else if(buff[counter] == '|'){
            operators++;
        }else if(buff[counter] == '^' && buff[counter + 1] == '='){
            operators++;
            counter++;
        }else if(buff[counter] == '^'){
            operators++;
        }else if(buff[counter] == '~'){
            operators++;
        }
        counter++;
    }
    return operators;
}

void blackmagic(FILE *file, FILE *outputfile, int from_file){
    size_t buffer_size = 0;
    size_t read_bytes = 0;
    char* line = NULL;
    int empty_lines = 0;
    int operators = 0;

    read_bytes = getline(&line, &buffer_size, file);
    while(read_bytes != -1){
        if (lineCheck(line, read_bytes)){
            empty_lines++;
        }
        operators += operatorCheck(line, read_bytes);

        read_bytes = getline(&line, &buffer_size, file);
    }
    fprintf(outputfile, "Number of blank lines: %d\n", empty_lines);
    fprintf(outputfile, "Number of operators: %d\n", operators);
    free(line);
}

int main(){
    int option;
    char* read = NULL;
    char* write = NULL;
    size_t read_bytes_read = 0;
    size_t read_bytes_write = 0;
    size_t dummy_variable = 0;
    size_t dummy_variable2 = 0;

    int from_file;

    printf("File to File                : [1]\n");
    printf("File to Command line        : [2]\n");
    printf("Command line to File        : [3]\n");
    printf("Command line to Command line: [4]\n");

    scanf("%d", &option);
    
    FILE *readFile;
    FILE *writeFile;

    getc(stdin);
    switch(option){
        case 1:
            printf("Enter C file to read from:");
            while(1){
                read_bytes_read = getline(&read, &dummy_variable, stdin);
                if(read[read_bytes_read-2] == 'c' && read[read_bytes_read-3] == '.'){
                    break;
                }
                printf("Enter C file:");
            }
            printf("Enter file to write to:");
            read_bytes_write = getline(&write, &dummy_variable2, stdin);
            read[read_bytes_read-1] = '\0';
            write[read_bytes_write-1] = '\0';

            readFile = fopen(read, "r");
            if(!readFile){
                printf("ERROR! %s\n", strerror(errno));
                free(read);
                free(write);
                return -1;
            }
            writeFile = fopen(write, "w");
            if(!writeFile){
                printf("ERROR! %s\n", strerror(errno));
                fclose(readFile);
                free(read);
                free(write);
                return -1;
            }

            blackmagic(readFile, writeFile, from_file = 1);  

            fclose(readFile);
            fclose(writeFile);
            free(read);
            free(write);
            break;
        case 2:
            printf("Enter C file to read from:");
            while(1){
                read_bytes_read = getline(&read, &dummy_variable, stdin);
                if(read[read_bytes_read-2] == 'c' && read[read_bytes_read-3] == '.'){
                    break;
                }
                printf("Enter C file:");
            }
            read[read_bytes_read-1] = '\0';
            readFile = fopen(read, "r");
            if(!readFile){
                printf("ERROR! %s\n", strerror(errno));
                free(read);
                return -1;
            }

            blackmagic(readFile, stdout, from_file = 1);  

            fclose(readFile);
            free(read);
            break;
        case 3:
            printf("Enter file to write to:");
            read_bytes_write = getline(&write, &dummy_variable, stdin);
            printf("Enter text. Press ctrl+D to stop:\n");
            write[read_bytes_write-1] = '\0';
            writeFile = fopen(write, "w");
            if(!writeFile){
                printf("ERROR! %s\n", strerror(errno));
                free(write);
                return -1;
            }

            blackmagic(stdin, writeFile, from_file = 0);  

            fclose(writeFile);
            free(write);
            break;
        case 4:
            printf("Enter text. Press ctrl+D to stop:\n");
            blackmagic(stdin, stdout, from_file = 0);
            break;
    }
    return 0;
}