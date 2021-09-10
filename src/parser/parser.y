

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    *                                                                 *
    *   mfcalc 2.0, Extended GNU Bison Example #3                     *
    *   Copyright 2005 Sebastian Pipping <webmaster@hartwork.org>   *
    *                                                                 *
    *   --> http://www.hartwork.org                                   *
    *                                                                 *
    *                                                                 *
    *   This source code is released under GPL.                       *
    *   See GPL.txt for details.                         2005-02-23   *
    *                                                                 *
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



%{

#include <math.h>
#include <tgmath.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <malloc.h>
#include "SymbolTable.h"
#include "Ast.h"
#include "Parser.h"

/* 
#include "LexerIface.h"
#define YY_DECL int doublelex \
               (DOUBLE_STYPE * yylval_param, DOUBLE_LTYPE * yylloc_param , symrec** symbolTable, int line, yyscan_t yyscanner)
extern int doublelex(DOUBLE_STYPE * yylval_param, DOUBLE_LTYPE * yylloc_param , symrec** symbolTable, int line, yyscan_t yyscanner);
 */ 
void yyerror (DOUBLE_LTYPE* loc, ast_node_t** boo, int* changed, char const *);

%}


%union {
	double val;			/* For returning numbers. */
	SymbolTableEntry_t *tptr;	/* For returning symbol-table pointers. */
	ast_node_t* node;		/*  */
	ast_node_t* argrec;		/*  */
	float f[1000];			/*  */
}

%parse-param       {ast_node_t** ast}
%parse-param       {int* changed }
%token <val> NUM				/* Simple double precision number. */
%token <tptr> CONST VAR			/* Variables and constants. */
%token <tptr> ZERO MANY			/* Functions. */
%type <node> exp
%type <argrec> args

%define api.pure full
%define api.push-pull push
%define api.prefix {double_}
%right '='
%left '-' '+'
%left '*' '/' '%'
%left NEG		/* negation--unary minus */
%right '^'		/* exponentiation */




%%		/* The grammar follows. */

input:
		/* empty */
	|	input line
;

line:	'\n'
	|	exp '\n'				{ *ast=$1; /*AstPrintTree( $1 ); int dep = AstCheckDependency( $1, "x"  );*/ *changed=1; /* printf("Check dipendenze :: %d\n", dep);*/ __debug_printf__("Guardia: %f\n",yyval.f[0]); }
	|	error '\n'				{ yyerrok;__debug_printf__("Guardia: %lf\n",yyval.f[0]); }
;

exp:	NUM									{ $$ = AstAddNum( $1 );__debug_printf__("%d\n",@1.first_line); __debug_printf__("Guardia: %f\n",yyval.f[0]); }
	|	CONST								{ $$ = AstAddConst( $1->data->val.data_d ); __debug_printf__("Guardia: %f\n",yyval.f[0]); }
	|	VAR									{ $$ = AstAddVar( $1 ); __debug_printf__("Guardia: %f\n",yyval.f[0]); }
	|	VAR '=' exp							{ $$ = AstAddBinOp( ASSIGNMENT_E, AstAddVar( $1 ), $3 );__debug_printf__("Guardia: %f\n",yyval.f[0]); }
	|	ZERO								{ $$ = AstAddFcnCall( AstAddFcnPtr( $1 ), NULL ); __debug_printf__("Guardia: %f\n",yyval.f[0]);}
	|	ZERO '(' ')'						{ $$ = AstAddFcnCall( AstAddFcnPtr( $1 ), NULL ); __debug_printf__("Guardia: %f\n",yyval.f[0]);}
	|	MANY '(' args ')'					{ $$ = AstAddFcnCall( AstAddFcnPtr( $1 ), $3 ); __debug_printf__("Guardia: %f\n",yyval.f[0]);}
	|	exp '+' exp							{ $$ = AstAddBinOp( SUM_E, $1, $3 ); __debug_printf__("Guardia: %f\n",yyval.f[0]); }
	|	exp '-' exp							{ $$ = AstAddBinOp( SUB_E, $1, $3 ); __debug_printf__("Guardia: %f\n",yyval.f[0]); }
	|	exp '*' exp							{ $$ = AstAddBinOp( MUL_E, $1, $3 ); __debug_printf__("Guardia: %f\n",yyval.f[0]); }
	|	exp '/' exp							{ $$ = AstAddBinOp( DIV_E, $1, $3 ); __debug_printf__("Guardia: %f\n",yyval.f[0]); }
	|	exp '%' exp							{ $$ = AstAddBinOp( MOD_E, $1, $3 ); __debug_printf__("Guardia: %f\n",yyval.f[0]); }
	|	'-' exp %prec NEG 					{ $$ = AstAddUnaryOp( NEG_E, $2 ); __debug_printf__("Guardia: %f\n",yyval.f[0]); }
	|	exp '^' exp							{ $$ = AstAddBinOp( POW_E, $1, $3 ); __debug_printf__("Guardia: %f\n",yyval.f[0]); }
	|	'(' exp ')'							{ $$ = AstAddParen( $2 ); __debug_printf__("Guardia: %f\n",yyval.f[0]); }
;

args:	exp									{ $$ = AstAddFcnLastArg( $1 ); __debug_printf__("Guardia: %f\n",yyval.f[0]);}
	|	exp ',' args						{ $$ = AstAddFcnPrevArg( $1, $3 );  __debug_printf__("Guardia: %f\n",yyval.f[0]);}
;

%%		/* End of grammar. */


/* --------------------------------------------------- */
/* Called by yyparse on error. */
void
yyerror (DOUBLE_LTYPE* loc, ast_node_t** boo, int* changed, char const *s)
{

  *changed = -1;
  printf ("\tERROR: %s\n\n", s);
}
/* --------------------------------------------------- */



