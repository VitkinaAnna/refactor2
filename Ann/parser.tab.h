/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SET = 258,                     /* SET  */
    IS = 259,                      /* IS  */
    OWNER = 260,                   /* OWNER  */
    SINGLE = 261,                  /* SINGLE  */
    MEMBER = 262,                  /* MEMBER  */
    UNIQUE = 263,                  /* UNIQUE  */
    ATTRIBUTE = 264,               /* ATTRIBUTE  */
    REVERSE = 265,                 /* REVERSE  */
    LEFT_PAREN = 266,              /* LEFT_PAREN  */
    RIGHT_PAREN = 267,             /* RIGHT_PAREN  */
    COMMA = 268,                   /* COMMA  */
    SEMICOLON = 269,               /* SEMICOLON  */
    INTEGER = 270,                 /* INTEGER  */
    FLOAT = 271,                   /* FLOAT  */
    DOUBLE = 272,                  /* DOUBLE  */
    CHAR = 273,                    /* CHAR  */
    ERROR = 274,                   /* ERROR  */
    IDENTIFIER = 275,              /* IDENTIFIER  */
    NUMBER = 276                   /* NUMBER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
  bool optional_single;                    /* optional_single  */
  char * IDENTIFIER;                       /* IDENTIFIER  */
  char * optional_reverse;                 /* optional_reverse  */
  long NUMBER;                             /* NUMBER  */
  struct attribute attribute;              /* attribute  */
  struct attribute_list * optional_attributes; /* optional_attributes  */
  struct attribute_list * attribute_list;  /* attribute_list  */
  struct attribute_list * dangling_comma_attribute_list; /* dangling_comma_attribute_list  */
  struct attribute_name_list * optional_unique; /* optional_unique  */
  struct attribute_name_list * attribute_name_list; /* attribute_name_list  */
  struct attribute_type attribute_type;    /* attribute_type  */
  struct dataset dataset;                  /* dataset  */
  struct dataset_list * dataset_list;      /* dataset_list  */

#line 99 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (struct dataset_list **result);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
