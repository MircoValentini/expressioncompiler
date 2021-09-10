#include "FrontEnd.h"

void FrontEndInit( FrontEndData_t* PData )
{

  /* Local variables */
  int scanner_init_res;

  __enter_function__( )

  /* Pointer initiolization */
  PData->ps=NULL;
  PData->scanner=(yyscan_t*)malloc(sizeof(yyscan_t));
  PData->ast = NULL;
  PData->sym_table = (HashTable_t*)malloc(sizeof(HashTable_t));
  TableInit( PData->sym_table );
  AddIntrinsics( PData->sym_table );
  __debug_printf__( "Number of nodes in the queue %d\n", HASH_COUNT( PData->sym_table->hash) );
  /* Call initialization routines */
  PData->ps = double_pstate_new ();
  scanner_init_res = testlex_init ( PData->scanner );

  __debug_printf__( "Scanner init result %d\n", scanner_init_res )

  __exit_function__( )

  return;

} /* FrontEndInit */



void 
FrontEndAnalyzeInput( FrontEndData_t* PData, const char* input, int input_len )
{

  /* Local data declaration */
  DOUBLE_LTYPE lloc;
  DOUBLE_STYPE lval;
  DOUBLE_LTYPE lloc01;
  DOUBLE_STYPE lval01;

  // YY_BUFFER_STATE bstate;

  int lex;
  int status;
  int changed;
  char* loc_input;

  __enter_function__( )

  loc_input = NULL;
  loc_input = (char*)malloc( input_len+1 );
  memset( loc_input, 0, input_len );
  memcpy( loc_input, input, input_len );

  /* Put the string in the buffer to be readed */
  __debug_printf__( "Inserimento stringa nello scanner\n" )
  // bstate = test_scan_string ( input, PData->scanner );
  __debug_printf__( "Number of nodes in the queue %d\n", HASH_COUNT( PData->sym_table->hash) );
  test_scan_string ( loc_input, *(PData->scanner) );

  /* Scan the string*/
  __debug_printf__( "Number of nodes in the queue %d\n", HASH_COUNT( PData->sym_table->hash) );
  __debug_printf__( "Estrazione di un token dalla stringa\n" )
  /* testset_debug( 1, PData->scanner ); */
  __debug_printf__( "Number of nodes in the queue %d\n", HASH_COUNT( PData->sym_table->hash) );
  lex = testlex ( &lval, &lloc, &(PData->sym_table), 1, *(PData->scanner) );
  __debug_printf__( "Token letto dallo scanner %d\n", lex )

  /* Parsing loop */
  do {

    /* Print the string  */
    __debug_printf__( "STRING :: %s", input )

    /* Parse the tokens */
    lloc01=lloc;
    lval01=lval;
    status = double_push_parse( PData->ps, lex, &lval01, &lloc01, &(PData->ast), &changed );
    __debug_printf__( "Stato del parser %d\n", status )

    /* Print the string  */
    __debug_printf__( "STRING :: %s", input )

    /* Scan the string*/
    __debug_printf__( "Leggo il nuovo Token\n" )
    __debug_printf__( "Number of nodes in the queue %d\n", HASH_COUNT( PData->sym_table->hash) );
    lex = testlex ( &lval, &lloc, &(PData->sym_table), 1, *(PData->scanner) );
    __debug_printf__( "Token letto dallo scanner %d\n", lex )


  } while(  lex != 10 && lex != -1 ); 


  lloc01=lloc;
  lval01=lval;
  status = double_push_parse( PData->ps, lex, &lval01, &lloc01, &(PData->ast), &changed );
  __debug_printf__( "Stato del parser %d\n", status )

  if ( loc_input != NULL ) free(loc_input);

  /* Exit from front end routine */
  __exit_function__( )

  /* Exit point */
  return;

} /* FrontEndAnalyzeInput */



double FrontEndEval( FrontEndData_t* PData )
{

  __enter_function__( )

  /* return AstEval( PData->ast ); */

  __exit_function__( )

  /* Exit point */
  return 0.0;

} /* FrontEndEval */



void FrontEndFree( FrontEndData_t* PData )
{

  __enter_function__( )
  TableFree( PData->sym_table );
  free( PData->sym_table );
  double_pstate_delete( PData->ps );
  testlex_destroy ( *(PData->scanner) );
  free( PData->scanner );
  AstDeleteTree( PData->ast );

  __exit_function__( )

  return;

} /* FrontEndFree */


