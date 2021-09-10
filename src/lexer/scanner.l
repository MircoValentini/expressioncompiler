/* scanner for a toy Pascal-like language */
/*
  {DIGIT}+"."{DIGIT}* {
ID       [a-z][a-z0-9]*

*/


%{
/* need this for the call to atof() below */
#include <math.h>
#include "Cfg.h"
#include "Utils.h"
#include "Ast.h"
#include "SymbolTable.h"
#include "Parser.h"

#define YY_DECL int yylex \
               (YYSTYPE * yylval_param, YYLTYPE * yylloc_param , HashTable_t** symbolTable, int line, yyscan_t yyscanner)

#define YYLTYPE DOUBLE_LTYPE
#define YYSTYPE DOUBLE_STYPE

%}


%option prefix="test"
%option noinput
%option nounput
%option 8bit 
%option nodefault                                 
%option yylineno
%option bison-bridge
%option bison-locations
%option reentrant
%option noyywrap
%option header-file="lexer.h"

UCN (\\u[0-9a-fA-F]{4}|\\U[0-9a-fA-F]{8})
EXP      ([Ee][-+]?[0-9]+)
DIGIT    [0-9]
ID  ([_a-zA-Z]|{UCN})([_a-zA-Z0-9]|{UCN})*
ILEN ([Uu](L|l|LL|ll)?|(L|l|LL|ll)[Uu]?)

%%

[1-9][0-9]*{ILEN}?  {
    /* Logging */
    __debug_printf__( "An float: %s (%d)\n", yytext, atoi( yytext ) ); 

    /* Handle position 
    (*yylloc).lo = (*yylloc).hi + 1;
    (*yylloc).hi = (*yylloc).lo + strlen(yytext) - 1;*/

    /* Encapsulate output */
    (*yylval).val = atof( yytext );

    /* Return the token type */
    return NUM;
  };

({DIGIT}+"."{DIGIT}*|{DIGIT}*\.{DIGIT}+|{DIGIT}+\.){EXP}?[flFL]?|{DIGIT}+{EXP}[flFL]? {
    __debug_printf__( "A float: %s (%g)\n", yytext, atof( yytext ) );  
    /*
    (*yylloc).lo = (*yylloc).hi + 1;
    (*yylloc).hi = (*yylloc).lo + strlen(yytext) - 1;*/
    (*yylval).val = atof( yytext );
    return NUM;
  };

{ID}  { 
    __debug_printf__( "An identifier: %s\n", yytext );  
    /*(*yylloc).lo = (*yylloc).hi + 1;
    (*yylloc).hi = (*yylloc).lo + strlen(yytext) - 1;
    (*yylval).val = VAR;              */

    __debug_printf__( "Number of nodes in the queue %d\n", HASH_COUNT( (*symbolTable)->hash) );
    SymbolTableEntry_t* s = GetSymbolTableNode( *symbolTable, yytext );
    if (s == 0)
    {
      SymbolTableData_t* data;
      data = (SymbolTableData_t*) malloc(sizeof(SymbolTableData_t)); 
      size_t len = strlen(yytext);
      data->name = (char*) malloc( len+1 );
      memset( data->name, 0, len+1 );
      memcpy( data->name, yytext, len );
      data->val.data_d = 0.0;
      data->type = ST_VAR_E;
      __debug_printf__( "Chiave :: %s\n", yytext );
      s = AddSymbolTableNode( *symbolTable, yytext, data );
    }
    (*yylval).tptr = s;


    if ( s->data->type == ST_VAR_E ) {
      return VAR;
    }
    else if ( s->data->type == ST_CONST_E ){
      return CONST;
    }
    else if ( s->data->type == ST_FUNC_00_E ){
      return ZERO;
    }
    else{
      return MANY;
    }

  };

"+"|"-"|"*"|"/"|"^"|"%"|"="|"("|")"|","  { 
    __debug_printf__( "An operator: %s\n", yytext ); 
    /*(*yylloc).lo = (*yylloc).hi + 1;
    (*yylloc).hi = (*yylloc).lo + strlen(yytext) - 1; */
    (*yylval).val = (int)yytext[0];
    return (int)yytext[0];
  };


\n  {
    __debug_printf__( "End of line \n" ); 
    /*printf( "EOL at : %d ;\n", (*yylloc).bl );  
     (*yylloc).lo = (*yylloc).hi + 1;
    (*yylloc).hi = (*yylloc).lo + strlen(yytext) - 1; */
    (*yylval).val = (int)yytext[0];
    return (int)yytext[0];
  } /* eat up whitespace */


" "|"\t"

. {
    __debug_printf__( "unknown: ||%s||\n", yytext ); 
    /* printf( "Unrecognized character: %s, %d\n", yytext, (*yylloc).bl ); */
    (*yylval).val = -1;              
    return -1;   
  };
%%


