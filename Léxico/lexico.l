DIGITO	[0-9]
LETRA	[a-zA-Z]
DELIM   [ \t\n]
ID	{LETRA}({LETRA}|{DIGITO}|_)*	
NUMERO  {DIGITO}+
EB      {DELIM}+
%%
class                   { printf("Palavra reservada: %s\n",yytext); }  
public                  { printf("Palavra reservada: %s\n",yytext); }
static                  { printf("Palavra reservada: %s\n",yytext); }
void                    { printf("Palavra reservada: %s\n",yytext); }
main                    { printf("Palavra reservada: %s\n",yytext); }
String                  { printf("Palavra reservada: %s\n",yytext); }
extends                 { printf("Palavra reservada: %s\n",yytext); }
return                  { printf("Palavra reservada: %s\n",yytext); }
int                     { printf("Palavra reservada: %s\n",yytext); }
boolean                 { printf("Palavra reservada: %s\n",yytext); }
if                      { printf("Palavra reservada: %s\n",yytext); }
else                    { printf("Palavra reservada: %s\n",yytext); }
while                   { printf("Palavra reservada: %s\n",yytext); }
System.out.println      { printf("Palavra reservada: %s\n",yytext); }
length                  { printf("Palavra reservada: %s\n",yytext); }
true                    { printf("Palavra reservada: %s\n",yytext); }
false                   { printf("Palavra reservada: %s\n",yytext); }
this                    { printf("Palavra reservada: %s\n",yytext); }
new                     { printf("Palavra reservada: %s\n",yytext); } 
{ID}			{ printf("Identificador: %s\n",yytext); }
{NUMERO}                { printf("Número: %s\n",yytext); }
{EB}                    { /* Não faz nada */}
"{"                     { printf("Abre chaves: %s\n",yytext); }
"}"                     { printf("Fecha chaves: %s\n",yytext); }
"("                     { printf("Abre parenteses: %s\n",yytext); }
")"                     { printf("Fecha parenteses: %s\n",yytext); }
"["                     { printf("Abre colchetes: %s\n",yytext); }
"]"                     { printf("Fecha colchetes: %s\n",yytext); }
";"                     { printf("Ponto e vírgula: %s\n",yytext); }
","                     { printf("Vírgula: %s\n",yytext); }
"="                     { printf("Atribuição: %s\n",yytext); }
"&&"                    { printf("And: %s\n",yytext); }
"<"                     { printf("Menor do que: %s\n",yytext); }
"+"                     { printf("Adição: %s\n",yytext); }
"-"                     { printf("Subtração: %s\n",yytext); }
"*"                     { printf("Produto: %s\n",yytext); }
"."                     { printf("Ponto: %s\n",yytext); }
"!"                     { printf("Not: %s\n",yytext); }
%%
int yywrap();

main(){
  yylex();
}

int yywrap(){
 return 1;
}
