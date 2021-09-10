/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_DOUBLE_INC_PARSER_H_INCLUDED
# define YY_DOUBLE_INC_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef DOUBLE_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define DOUBLE_DEBUG 1
#  else
#   define DOUBLE_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define DOUBLE_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined DOUBLE_DEBUG */
#if DOUBLE_DEBUG
extern int double_debug;
#endif

/* Token type.  */
#ifndef DOUBLE_TOKENTYPE
# define DOUBLE_TOKENTYPE
  enum double_tokentype
  {
    NUM = 258,
    CONST = 259,
    VAR = 260,
    ZERO = 261,
    MANY = 262,
    NEG = 263
  };
#endif

/* Value type.  */
#if ! defined DOUBLE_STYPE && ! defined DOUBLE_STYPE_IS_DECLARED

union DOUBLE_STYPE
{
#line 43 "src/parser/parser.y" /* yacc.c:1909  */

	double val;			/* For returning numbers. */
	SymbolTableEntry_t *tptr;	/* For returning symbol-table pointers. */
	ast_node_t* node;		/*  */
	ast_node_t* argrec;		/*  */
	float f[1000];			/*  */

#line 79 "./inc/Parser.h" /* yacc.c:1909  */
};

typedef union DOUBLE_STYPE DOUBLE_STYPE;
# define DOUBLE_STYPE_IS_TRIVIAL 1
# define DOUBLE_STYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined DOUBLE_LTYPE && ! defined DOUBLE_LTYPE_IS_DECLARED
typedef struct DOUBLE_LTYPE DOUBLE_LTYPE;
struct DOUBLE_LTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define DOUBLE_LTYPE_IS_DECLARED 1
# define DOUBLE_LTYPE_IS_TRIVIAL 1
#endif



#ifndef YYPUSH_MORE_DEFINED
# define YYPUSH_MORE_DEFINED
enum { YYPUSH_MORE = 4 };
#endif

typedef struct double_pstate double_pstate;

int double_push_parse (double_pstate *ps, int pushed_char, DOUBLE_STYPE const *pushed_val, DOUBLE_LTYPE *pushed_loc, ast_node_t** ast, int* changed);

double_pstate * double_pstate_new (void);
void double_pstate_delete (double_pstate *ps);

#endif /* !YY_DOUBLE_INC_PARSER_H_INCLUDED  */
