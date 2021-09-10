#ifndef __FRONTEND_H__
#define __FRONTEND_H__

typedef void* yyscan_t;
/* Define the lexer to avoid standard lexer definitrion */
#define YY_DECL

#include <time.h>
#include "SymbolTable.h"
#include "Ast.h"
#include "Parser.h"
#include "Scanner.h"
#include "Lexer.h"

/* Undef the lexer to avoid standard lexer definition */
#undef YY_DECL

#include "LexerIface.h"
#include "Intrinsics.h"




struct FrontEndData
{
  yyscan_t          *scanner;
  ast_node_t        *ast;
  HashTable_t       *sym_table;
  double_pstate     *ps;
};

typedef struct FrontEndData FrontEndData_t;

void FrontEndInit( FrontEndData_t* PData );
void FrontEndAnalyzeInput( FrontEndData_t* PData, const char* string, int input_len );
double FrontEndEval( FrontEndData_t* PData );
void FrontEndFree( FrontEndData_t* PData );


#endif // __FRONTEND_H__
