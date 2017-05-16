/* Calculadora de notación infija--calc */
%{
#include <math.h>
#include "hashTable.h"
#include "byson.h"
int yyerror(const char *msg);


%}

/* Declaraciones de BISON */

%union {
    entrytable *sym;
    double val;
}

%error-verbose

%token <val> NUM
%token <sym> VAR FUN CONST
%type <val> exp

%right '='
%left '-' '+'
%left '*' '/'
%left NEG   /* negación--menos unario */
%right '^'  /* exponenciación */




/* A continuación la gramática */
%%
input:          /* cadena vacı́a */
                | input line

line:           ';'
                | exp ';' { printf ("\t%.10g\n", $1); }
                | error ';' { yyerrok; }
                ;

exp:            NUM             { $$ = $1; }
                | VAR           {  $$ = $1->var; }
                | VAR '=' exp   {  $$ = $3; $1->var = $3;  }
                | CONST         {  $$ = $1->var; }
                | FUN '(' exp ')' { $$ = (*($1->fnctptr))($3); }
                | exp '+' exp   { $$ = $1 + $3; }
                | exp '-' exp   { $$ = $1 - $3; }
                | exp '*' exp   { $$ = $1 * $3; }
                | exp '/' exp   { $$ = $1 / $3; }
                | '-' exp %prec NEG { $$ = -$2; }
                | exp '^' exp { $$ = pow ( $1, $3 ); }
                | '(' exp ')'   { $$ = $2 ; }
;
%%


void begin(){
    yyparse();
}