#include "ExpressionCompiler.h"


int ExpressionCompiler( char* expression, int nVars, char** Vars, int nFcns, char** Fcns, int verbose, AstTreeDims_t* MEPdim, t_mep_chromosome* chromosome )
{

  /* Local variables */
  int err = 0;

  /* Setup the input expression */
  int formula_len = strlen(expression);
  char* formula = (char*)malloc( formula_len+3 );
  memset( formula,  0, formula_len+2 );
  memset( formula, 10, formula_len+1 );
  memcpy( formula, expression, formula_len );

  if (verbose>1) printf( "Expression: %s \n", formula );

  /* Parser data initialization */
  FrontEndData_t PData;

  /* Initialize parser state */
  FrontEndInit( &PData );

  /* Parse string */
  FrontEndAnalyzeInput( &PData, formula, formula_len+2 );

  /* Print the tree */
  if (verbose>1) AstPrintTree( PData.ast, "ExpressionTree.dot" );

  /* Create output mep table */
  AstCreateMepTable( PData.ast, chromosome, MEPdim, nVars, Vars, nFcns, Fcns );

  /* Delete the tree */
  FrontEndFree( &PData );
  free(formula);

  /* Exit point */
  return err;

}


