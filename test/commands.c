#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Field {
    char* name;
    char* type;
};

struct Table {
    char* name;
    struct Field* fields;
};

struct Database {
    char* name;
    int use;
    char* tables;
};

int menu();
void createDatabase(char* name);

struct Database* database;

int main(){
    char command[] = "mkdir something";
    // system(command);
    int option = 0;
    printf("Bienvenido a IrkenDB:\n");
    
    while(option >= 0){
        option = menu();
    }
    return 0;
}

int menu(){
    int option;
    char command[100];
    scanf("%[^\n]%*c", command);
    if(0 == memcmp(command, "help", 4)){
        option = 1;
        printf("Help text");
    }
    if(0 == memcmp(command, "create database", sizeof("create database"))){
        option = 2;
        printf("Write the name of the database: ");
        char database_name[50];
        scanf("%s", database_name);
        printf("Creating database %s... ", database_name);
        database->name = database_name;
    }
    if(0 == memcmp(command, "use", 3)){
        option = 3;
        char database_name[100];
        printf("Write the name of the database to use: ");
        scanf("%s", database_name);
        printf("Using database %s...", database_name);
    }
    return option;
}

void createDatabase(char* name){
    FILE *database;
    database = fopen("./database/database.c", "w");
    fprintf(database, "#include<stdio.h>\n");
    fprintf(database, "#include<stdlib.h>\n");
    fprintf(database, "int main(){\n");
    fprintf(database, "}\n");
}