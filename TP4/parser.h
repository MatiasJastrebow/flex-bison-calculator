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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    NUM = 258,                     /* NUM  */
    ID = 259,                      /* ID  */
    FUN = 260,                     /* FUN  */
    PR_VAR = 261,                  /* PR_VAR  */
    PR_SALIR = 262,                /* PR_SALIR  */
    MAS = 263,                     /* MAS  */
    MAS_IGUAL = 264,               /* MAS_IGUAL  */
    MENOS = 265,                   /* MENOS  */
    MENOS_IGUAL = 266,             /* MENOS_IGUAL  */
    POR = 267,                     /* POR  */
    POR_IGUAL = 268,               /* POR_IGUAL  */
    DIV = 269,                     /* DIV  */
    DIV_IGUAL = 270,               /* DIV_IGUAL  */
    POT = 271,                     /* POT  */
    IGUAL = 272,                   /* IGUAL  */
    PAR_IZQ = 273,                 /* PAR_IZQ  */
    PAR_DER = 274,                 /* PAR_DER  */
    NL = 275,                      /* NL  */
    NEG = 276                      /* NEG  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
  char MAS;                                /* MAS  */
  char MAS_IGUAL;                          /* MAS_IGUAL  */
  char MENOS;                              /* MENOS  */
  char MENOS_IGUAL;                        /* MENOS_IGUAL  */
  char POR;                                /* POR  */
  char POR_IGUAL;                          /* POR_IGUAL  */
  char DIV;                                /* DIV  */
  char DIV_IGUAL;                          /* DIV_IGUAL  */
  char POT;                                /* POT  */
  char IGUAL;                              /* IGUAL  */
  char PAR_IZQ;                            /* PAR_IZQ  */
  char PAR_DER;                            /* PAR_DER  */
  char NL;                                 /* NL  */
  char* PR_VAR;                            /* PR_VAR  */
  char* PR_SALIR;                          /* PR_SALIR  */
  double NUM;                              /* NUM  */
  double linea;                            /* linea  */
  double expresion;                        /* expresion  */
  double termino;                          /* termino  */
  double primaria;                         /* primaria  */
  struct symrec * ID;                      /* ID  */
  struct symrec * FUN;                     /* FUN  */

#line 108 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);

/* "%code provides" blocks.  */
#line 8 "parser.y"

void yyerror(const char *);

#line 127 "parser.h"

#endif /* !YY_YY_PARSER_H_INCLUDED  */
