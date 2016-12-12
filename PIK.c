#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char buff[100000];

void readFromFile(char *file_name){
    FILE *f;
    char line[300];

    strcpy(buff, "");

    f = fopen(file_name, "r");
    if(f == NULL){
        perror("File not found");
    }
    while (fgets(line, 300, f)!=NULL){
        strcat(buff, line);
    }
    fclose(f);
}

void writeToFile(char *file_name){
    int empty_lines;
    int operators;
    FILE *f;

    f = fopen(file_name, "w");

    if(f == NULL){
        perror("File not found");
    }
    empty_lines = lineCheck();
    operators = operatorCheck();
    fprintf(f, "Empty lines:%d\n", empty_lines);
    fprintf(f, "Operators:%d", operators);
}

void readFromCommandLine(){
    int i = 0;
    char c;
    char cl[50];
    while((c = getchar()) != EOF){
        cl[i] = c;
        i++;
    }
    printf("%s", cl);
}

int lineCheck(){
    int counter = 0;
    int empty_lines = 0;
    while(counter < strlen(buff)){
        if(buff[counter] == '\n' && buff[counter + 1] == '\n'){
            empty_lines++;
        }else if(buff[counter] == '\n' && buff[counter + 1] == '\0'){
            empty_lines++;
        }
        counter++;
    }
    return empty_lines;
}

int operatorCheck(){
    int counter = 0;
    int operators = 0;
    while(counter < strlen(buff)){    
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
    printf("Operators:%d\n" ,operators);
    return operators;
}

int main(){
    char i[30];
    scanf("%s", &i);
	/*int menu_selection = 0;

	printf("file to file        : [1]\n");
	printf("file to terminal    : [2]\n");
	printf("terminal to file    : [3]\n");
	printf("terminal to terminweal: [4]\n");
	scanf("%d", &menu_selection);
	
    switch(menu_selection){
        case 1:
            readFromFile("test.txt");
            writeToFile("test1.txt");
            break;
        case 2:
            readFromFile("test.txt");
            lineCheck();
            operatorCheck();
            break;
        case 3:
            readFromCommandLine();
            writeToFile("test1.txt");
            break;
        case 4:
            readFromCommandLine();
            lineCheck();
            operatorCheck();
            break;
    }*/
    readFromFile(i);
    operatorCheck();
    return 0;
}