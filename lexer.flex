%{
#include "hashTable.h"
#include "byson.tab.c"
#include "definitions.h"
#include "string.h"

char * lexema;
entrytable *s;
double getNumberDouble(char * string);
void readFromTerminal();
void readFile(char * fileName);
void help();
%}

DIGITO [0-9]
IDENTIFIER [_a-zA-Z][_a-zA-Z0-9]*
%option noyywrap
%%

"load"+.*                                           readFile(yytext); readFromTerminal(); display(); printf("Calculadora:\n");
"show"                                              display();
"help"                                              help();
"exit"                                              display();exit(0);

{DIGITO}+"e"+[-|+]?{DIGITO}*                        yylval.val = getNumberDouble(yytext); return NUM;
{DIGITO}+"."{DIGITO}*+"e"+[-|+]?{DIGITO}*           yylval.val = getNumberDouble(yytext); return NUM;
{DIGITO}+"."{DIGITO}*                               yylval.val = atof(yytext);  return NUM;
{DIGITO}*                                           yylval.val = atof(yytext);  return NUM;

{IDENTIFIER} {
    s = search(yytext);
    // New identifier
    if(s==NULL){
        s = (entrytable*)malloc(sizeof(entrytable));
        s->lexema = (char*)malloc(sizeof(char)*255);
        strcpy(s->lexema,yytext);
        s->lexicalComponent = IDENTIFIER;
        insertItem(*s);
        free(s->lexema);
        free(s);
        s = search(yytext);
        yylval.sym = s;
        return  VAR;
    }
    else{
        s = search(yytext);
        yylval.sym = s;
        if(s->lexicalComponent == IDENTIFIER){
            return VAR;
        }
        if(s->lexicalComponent == FUNCTION){
            return FUN;
        }
        if(s->lexicalComponent == CONSTANT){
            return CONST;
        }
    }

}





"("                                             return '(';
")"                                             return ')';
"="                                             return '=';


"+"                                              return  '+';
"-"                                              return  '-';
"*"                                              return  '*';
"/"                                              return '/';
"<"                                              return  '<';
">"                                              return  '>';
"^"                                              return  '^';

";"                                              return  ';';

"."                                              return  '.';
"\\n"                                            return  '\n';
"\\0"                                            return  '\0';


%%

int yyerror(const char *msg) {
    display();
    printf("Error: %s \n", msg);
    return -1;
}

void beginFlex(){
    yylex();
}

double getNumberDouble(char * string){
    double val = 0;
    char *part1 = strtok(string,"e");
    if(part1!=NULL){
        double init = atof(part1);
        part1 = strtok(NULL,"e");
        if(part1!=NULL){
            double exp = atof(part1);
            val = init * pow(10,exp);
        }
    }

return val;
}

void help(){
    printf("help: Show some examples and syntax \n");
    printf("show: Show the symbol table\n");
    printf("load nameOfFile: Load a file\n");
    printf("exit: Exit of the program\n");
    printf("Note: The file should be in the same path as the executable\n");
    printf("Allowed functions: sin, cos, tan , log exp\n");
    printf("Constants: pi; E;\n\n");
    printf("Examples\n");
    printf("3+2; 5-2; 3e-2+3; 53*3; cos(37);\n\n\n");
    printf("Calculadora\n");
}

void readFile(char* filename){

    char *part1 = strtok(filename," ");

    part1 = strtok(NULL," ");


    printf("Reading file %s\n",part1);
    yyin = fopen(part1, "r" );

    yyrestart(yyin);

    if (yyin == NULL) {
        perror("Error with file loading\n");
    }
    else{
        printf("FILE loaded\n");
    }
    begin(INITIAL);

}


void readFromTerminal(){
    yyin = stdin;
    yyrestart(yyin);
}