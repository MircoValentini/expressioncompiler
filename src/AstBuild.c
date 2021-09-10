#include "Ast.h"


ast_node_t* 
AstAddNum( double val )
{

  __enter_function__( )

  ast_node_t* tmp = (ast_node_t*)malloc( sizeof(ast_node_t) );
  ast_node_number_t* loc_payload = (ast_node_number_t*)malloc( sizeof(ast_node_number_t) );
  tmp->node_idx = ++node_idx;
  loc_payload->number = val;
  tmp->Payload = (void*)loc_payload;
  tmp->PayloadType = NUM_E;
  tmp->left=NULL;
  tmp->right=NULL;

  __debug_printf__( "Insert number %f, node idx %d\n", (float)val, tmp->node_idx )
  __exit_function__( )

  return tmp;

} /* AstAddNum */



ast_node_t* 
AstAddConst( double val )
{

  __enter_function__( )

  ast_node_t* tmp = (ast_node_t*)malloc( sizeof(ast_node_t) );
  ast_node_constant_t* loc_payload = (ast_node_constant_t*)malloc( sizeof(ast_node_constant_t) );
  tmp->node_idx = ++node_idx;
  loc_payload->constant = val;
  tmp->Payload = (void*)loc_payload;
  tmp->PayloadType = CONST_E;
  tmp->left=NULL;
  tmp->right=NULL;

  __debug_printf__( "Insert constant %f, node idx %d\n", (float)val, tmp->node_idx )
  __exit_function__( )

  return tmp;

} /* AstAddConst */



ast_node_t* 
AstAddVar( SymbolTableEntry_t *tptr )
{

  __enter_function__( )

  ast_node_t* tmp = (ast_node_t*)malloc( sizeof(ast_node_t) );
  ast_node_variable_t* loc_payload = (ast_node_variable_t*)malloc( sizeof(ast_node_variable_t) );
  tmp->node_idx = ++node_idx;
  tmp->Payload = (void*)loc_payload;
  tmp->PayloadType = VARIABLE_E;
  loc_payload->tptr = tptr->data;
  tmp->left=NULL;
  tmp->right=NULL;

  __debug_printf__( "Insert variable %s, node idx %d\n", loc_payload->tptr->name, tmp->node_idx )
  __exit_function__( )

  return tmp;

} /* AstAddVar */



ast_node_t*
AstAddFcnPtr( SymbolTableEntry_t *tptr )
{

  __enter_function__( )

  ast_node_t* tmp = (ast_node_t*)malloc( sizeof(ast_node_t) );
  ast_node_fcn_ptr_t* loc_payload = (ast_node_fcn_ptr_t*)malloc( sizeof(ast_node_fcn_ptr_t) );
  tmp->node_idx = ++node_idx;
  tmp->Payload = (void*)loc_payload;
  tmp->PayloadType = FUNCTION_PTR_E;
  loc_payload->tptr = tptr->data;
  tmp->left=NULL;
  tmp->right=NULL;

  __exit_function__( )

  return tmp;

} /* AstAddFcnPtr */


ast_node_t*
AstAddFcnPtr02( SymbolTableData_t *data )
{

  __enter_function__( )

  ast_node_t* tmp = (ast_node_t*)malloc( sizeof(ast_node_t) );
  ast_node_fcn_ptr_t* loc_payload = (ast_node_fcn_ptr_t*)malloc( sizeof(ast_node_fcn_ptr_t) );
  tmp->node_idx = ++node_idx;
  tmp->Payload = (void*)loc_payload;
  tmp->PayloadType = FUNCTION_PTR_E;
  loc_payload->tptr = data;
  tmp->left=NULL;
  tmp->right=NULL;

  __exit_function__( )

  return tmp;

} /* AstAddFcnPtr */



ast_node_t* 
AstAddFcnCall( ast_node_t* fcn_ptr, ast_node_t* fcn_args )
{

  __enter_function__( )

  /* Local variable declaration */
  ast_node_t* curr;
  int cnt;

  /* Create the function structure */
  ast_node_t* tmp = (ast_node_t*)malloc( sizeof(ast_node_t) );
  ast_node_fcn_eval_t* loc_payload = (ast_node_fcn_eval_t*)malloc( sizeof(ast_node_fcn_eval_t) );

  /* Set the number of input arguments */
  loc_payload->numArgs = 0;
  if ( fcn_args != NULL ) {
    curr = fcn_args;
    cnt = 0;
    while ( curr != NULL ){
      cnt++;
      ((ast_node_fcn_arg_t*)(curr->Payload))->argIdx = cnt;
      curr = curr->right;
    }
    loc_payload->numArgs = cnt;
  }

  tmp->node_idx = ++node_idx;
  tmp->Payload = (void*)loc_payload;
  tmp->PayloadType = FUNCTION_CALL_E;
  tmp->left  = fcn_ptr;
  tmp->right = fcn_args;
  fcn_ptr->parent  = tmp;
  if ( fcn_args != NULL ) {
    fcn_args->parent = tmp;
  }

  __debug_printf__( "Insert variable %s, node idx %d\n", loc_payload->tptr->name, tmp->node_idx )
  __exit_function__( )

  return tmp;

} /* AstAddFcnCall */


ast_node_t* 
AstAddFcnLastArg( ast_node_t* fcn_arg )
{
  __enter_function__( )


  /* Create the node structure */
  ast_node_t* tmp = (ast_node_t*)malloc( sizeof(ast_node_t) );
  ast_node_fcn_arg_t* loc_payload = (ast_node_fcn_arg_t*)malloc( sizeof(ast_node_fcn_arg_t) );

  tmp->node_idx = ++node_idx;
  tmp->PayloadType = FUNCTION_ARG_E;
  tmp->Payload = (void*) loc_payload;
  tmp->left  = fcn_arg;
  tmp->right = NULL;
  fcn_arg->parent  = tmp;

  __debug_printf__( "Insert variable %s, node idx %d\n", loc_payload->tptr->name, tmp->node_idx )
  __exit_function__( )

  return tmp;

} /* AstAddFcnLastArg */


ast_node_t* 
AstAddFcnPrevArg( ast_node_t* fcn_arg, ast_node_t* fcn_args )
{
  __enter_function__( )

  ast_node_t* tmp = (ast_node_t*)malloc( sizeof(ast_node_t) );
  ast_node_fcn_arg_t* loc_payload = (ast_node_fcn_arg_t*)malloc( sizeof(ast_node_fcn_arg_t) );

  tmp->node_idx = ++node_idx;
  tmp->PayloadType = FUNCTION_ARG_E;
  tmp->Payload = (void*) loc_payload;
  tmp->left  = fcn_arg;
  tmp->right = fcn_args;
  fcn_arg->parent  = tmp;
  fcn_args->parent  = tmp;

  __exit_function__( )

  return tmp;

} /* AstAddFcnNextArg */


ast_node_t* 
AstAddBinOp( binop_type_t optype, ast_node_t* left_op, ast_node_t* right_op )
{

  __enter_function__( )

  ast_node_t* tmp = (ast_node_t*)malloc( sizeof(ast_node_t) );
  ast_node_binaryop_t* loc_payload = (ast_node_binaryop_t*)malloc( sizeof(ast_node_binaryop_t) );

  tmp->node_idx = ++node_idx;
  tmp->PayloadType = BINARY_OPERATION_E;
  loc_payload->BinaryOperationType = optype;
  tmp->Payload = (void*) loc_payload;
  tmp->left  = left_op;
  tmp->right = right_op;
  left_op->parent  = tmp;
  right_op->parent = tmp;

#ifdef __AST_DEBUG__
  AstPrintBinaryOpType( optype, left_op, right_op );
#endif

  __exit_function__( )

  return tmp;

} /* AstAddBinOp */


ast_node_t* 
AstAddUnaryOp( unaryop_type_t optype, ast_node_t* op )
{

  __enter_function__( )

  ast_node_t* tmp = (ast_node_t*)malloc( sizeof(ast_node_t) );
  ast_node_unaryop_t* loc_payload = (ast_node_unaryop_t*)malloc( sizeof(ast_node_unaryop_t) );

  tmp->node_idx = ++node_idx;
  tmp->PayloadType = UNARY_OPERATION_E;
  loc_payload->UnaryOperationType = optype;
  tmp->Payload = (void*) loc_payload;
  tmp->left  = NULL;
  tmp->right = op;
  op->parent = tmp;

#ifdef __AST_DEBUG__
  AstPrintUnaryOpType( optype, op );
#endif

  __exit_function__( )

  return tmp;

} /* AstAddUnaryOp */


ast_node_t* 
AstAddParen( ast_node_t* node )
{

  __enter_function__( )

  __exit_function__( )

  return node;

} /* AstAddParen */




