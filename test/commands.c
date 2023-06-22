#include <stdlib.h>
#include <stdio.h>

int menu();

int main(){
    char command[] = "mkdir something";
    // system(command);
    menu();
    return 0;
}

int menu(){
    int option;
    char command[100];
    printf("Bienvenido a IrkenDB:\n");
    scanf("%[^\n]%*c", command);
    
}

void createDatabase(char* name){

}