#include <stdio.h>
#include <stdlib.h>
#include "byson.h"
#include "definitions.h"
#include "string.h"
#include "hashTable.h"
#include "math.h"


void addFunctions();
void addConstants();

int main() {
    printf("Use  help for information about this calculator and exit to go out.\n");
    printf("Example operation 3+2; .\n");
    printf("Calculator: \n");
    initTable(100);
/*    while (1){
        beginFlex();
    }*/
    addFunctions();
    addConstants();
    begin();
    display();
    return 0;
}

void addConstants(){
    entrytable *s;
    s = (entrytable*)malloc(sizeof(entrytable));
    s->lexema = (char*)malloc(sizeof(char)*255);
    s->lexicalComponent = CONSTANT;

    strcpy(s->lexema,"pi");
    s->var = M_PI;
    insertItem(*s);

    strcpy(s->lexema,"E");
    s->var = E;
    insertItem(*s);
}

void addFunctions(){
    entrytable *s;
    s = (entrytable*)malloc(sizeof(entrytable));
    s->lexema = (char*)malloc(sizeof(char)*255);
    s->lexicalComponent = FUNCTION;

    s->fnctptr = cos;
    strcpy(s->lexema,"cos");
    insertItem(*s);

    s->fnctptr = sin;
    strcpy(s->lexema,"sin");
    insertItem(*s);

    s->fnctptr = tan;
    strcpy(s->lexema,"tan");
    insertItem(*s);

    s->fnctptr = log;
    strcpy(s->lexema,"log");
    insertItem(*s);

    s->fnctptr = exp;
    strcpy(s->lexema,"exp");
    insertItem(*s);
}

