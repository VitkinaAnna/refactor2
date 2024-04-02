%{
  #include <stdlib.h>
  #include "dataset.h"
  #include "parser.tab.h"
%}

%option caseless

%%

[ \t\n]+ {
}
"set" {
  return SET;
}
"is" {
  return IS;
}
"owner" {
  return OWNER;
}
"single" {
  return SINGLE;
}
"member" {
  return MEMBER;
}
"unique" {
  return UNIQUE;
}
"attribute" {
  return ATTRIBUTE;
}
"reverse" {
  return REVERSE;
}
"(" {
  return LEFT_PAREN;
}
")" {
  return RIGHT_PAREN;
}
"," {
  return COMMA;
}
";" {
  return SEMICOLON;
}
"integer" {
  return INTEGER;
}
"float" {
  return FLOAT;
}
"double" {
  return DOUBLE;
}
"char" {
  return CHAR;
}
[a-z#_]+ {
  yylval.IDENTIFIER = strdup(yytext);
  return IDENTIFIER;
}
[0-9]+ {
  yylval.NUMBER = strtol(yytext, NULL, 0);
  return NUMBER;
}
. {
  return ERROR;
}

%%
