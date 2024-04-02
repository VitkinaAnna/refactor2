set -ue

bison -d parser.y
flex lexer.l
gcc -lfl lex.yy.c yyerror.c parser.tab.c SyntInsertDS.c print.c main.c -o main
