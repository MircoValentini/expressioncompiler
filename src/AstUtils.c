#include "Ast.h"


void 
AstPrintBinaryOpType( binop_type_t optype, ast_node_t* left_op, ast_node_t* right_op )
{

  switch (optype)
  {
  case ASSIGNMENT_E:
    printf( "Inserimento operazione (%d):: assegnamento\n", node_idx );
    printf( "assegnamento %d = %d\n\n\n", left_op->node_idx, right_op->node_idx );
    break;
  case SUM_E:
    printf( "Inserimento operazione (%d):: somma\n", node_idx );
    printf( "assegnamento %d + %d\n\n\n", left_op->node_idx, right_op->node_idx );
    break;
  case SUB_E:
    printf( "Inserimento operazione (%d):: sottrazione\n", node_idx );
    printf( "assegnamento %d - %d\n\n\n", left_op->node_idx, right_op->node_idx );
    break;
  case MUL_E:
    printf( "Inserimento operazione (%d):: moltiplicazione\n", node_idx );
    printf( "assegnamento %d * %d\n\n\n", left_op->node_idx, right_op->node_idx );
    break;
  case DIV_E:
    printf( "Inserimento operazione (%d):: divisione\n", node_idx );
    printf( "assegnamento %d / %d\n\n\n", left_op->node_idx, right_op->node_idx );
    break;
  case MOD_E:
    printf( "Inserimento operazione (%d):: modulo\n", node_idx );
    printf( "assegnamento %d mod %d\n\n\n", left_op->node_idx, right_op->node_idx );
    break;
  case POW_E:
    printf( "Inserimento operazione (%d):: potenza\n", node_idx );
    printf( "assegnamento %d ^ %d\n\n\n", left_op->node_idx, right_op->node_idx );
    break;
  }

  return;

} /* AstPrintBinaryOpTye */


void 
AstPrintUnaryOpType( unaryop_type_t optype, ast_node_t* op )
{

  switch (optype)
  {
  case NEG_E:
    printf( "Inserimento operazione (%d):: unary neg\n", node_idx );
    printf( "negazione unaria -%d\n\n\n", op->node_idx );
    break;
  }

  return;

} /* AstPrintUnaryOpTye */


void
AstPrintTree( ast_node_t* op, const char* fname )
{

  __enter_function__( )

  FILE* fid = fopen( fname, "w" );

  fprintf( fid, "digraph Ast {\n" );

  AstPrintTreeNodes( fid, op );

  fprintf( fid, "\n\n" );

  AstPrintTreeConnections( fid, op );

  fprintf( fid, "}\n\n" );

  fclose(fid);

  __exit_function__( )

  return;

}



void 
AstPrintNumberGraph( FILE* fid, ast_node_t* op )
{

  fprintf( fid, "%d [label=\"%2.2f\"]\n", op->node_idx, (float)((ast_node_number_t*)op->Payload)->number );
  return;

}


void 
AstPrintConstantGraph( FILE* fid, ast_node_t* op )
{

  fprintf( fid, "%d [label=\"%2.2f\"]\n", op->node_idx, (float)((ast_node_constant_t*)op->Payload)->constant );
  return;

}


void 
AstPrintVariableGraph( FILE* fid, ast_node_t* op )
{

  fprintf( fid, "%d [label=\"%s\"]\n", op->node_idx, ((ast_node_variable_t*)op->Payload)->tptr->name );
  return;

}

void 
AstPrintFunctionPtrGraph( FILE* fid, ast_node_t* op )
{

  fprintf( fid, "%d [label=\"%s\"]\n", op->node_idx, ((ast_node_fcn_ptr_t*)op->Payload)->tptr->name );
  return;

}

void 
AstPrintFunctionArgGraph( FILE* fid, ast_node_t* op )
{

  fprintf( fid, "%d [label=\"#%d\", style=filled, color=lightgrey]\n", op->node_idx, ((ast_node_fcn_arg_t*)op->Payload)->argIdx );
  return;

}


void 
AstPrintFunctionCallGraph( FILE* fid, ast_node_t* op )
{

  fprintf( fid, "%d [label=\"@%d\", style=filled, color=lightgrey]\n", op->node_idx, ((ast_node_fcn_eval_t*)(op->Payload))->numArgs );
  return;

}

void 
AstPrintBinaryOpGraph( FILE* fid, ast_node_t* op )
{


  binop_type_t sel = ((ast_node_binaryop_t*)op->Payload)->BinaryOperationType;
  switch ( sel )
  {
    case ASSIGNMENT_E:
      fprintf( fid, "%d [label=\"=\",shape=diamond,color=blue, style=filled, color=lightgrey]\n",  op->node_idx );
      break;
    case SUM_E:
      fprintf( fid, "%d [label=\"+\",shape=diamond,color=blue, style=filled, color=lightgrey]\n",  op->node_idx );
      break;
    case SUB_E:
      fprintf( fid, "%d [label=\"-\",shape=diamond,color=blue, style=filled, color=lightgrey]\n",  op->node_idx );
      break;
    case MUL_E:
      fprintf( fid, "%d [label=\"*\",shape=diamond,color=blue, style=filled, color=lightgrey]\n",  op->node_idx );
      break;
    case DIV_E:
      fprintf( fid, "%d [label=\"/\",shape=diamond,color=blue, style=filled, color=lightgrey]\n",  op->node_idx );
      break;
    case MOD_E:
      fprintf( fid, "%d [label=\"%%\",shape=diamond,color=blue, style=filled, color=lightgrey]\n",  op->node_idx );
      break;
    case POW_E:
      fprintf( fid, "%d [label=\"^\",shape=diamond,color=blue, style=filled, color=lightgrey]\n",  op->node_idx );
      break;
    default:
      printf( "ERROR\n" );
  }

  return;

}



void 
AstPrintUnaryOpGraph( FILE* fid, ast_node_t* op )
{


  unaryop_type_t sel = ((ast_node_unaryop_t*)op->Payload)->UnaryOperationType;
  switch ( sel )
  {
    case NEG_E:
      fprintf( fid, "%d [label=\"-\",shape=diamond,color=blue, style=filled, color=lightgrey]\n",  op->node_idx );
      break;
    default:
      printf( "ERROR\n" );
  }

  return;

}



void 
AstPrintTreeNodes( FILE* fid, ast_node_t* op )
{

  __enter_function__( )

  /* Recursive call to the left node */
  if ( op->left != NULL )
  {
    AstPrintTreeNodes( fid, op->left );
  }

  /* Recursive call to the right node */
  if ( op->right != NULL )
  {
    AstPrintTreeNodes( fid, op->right );
  }


  /* Sccording to the payload type print the correct node */
  node_type_t sel = op->PayloadType;
  switch ( sel )
  {
    case NUM_E:
      AstPrintNumberGraph( fid, op );
      break;
    case CONST_E:
      AstPrintConstantGraph( fid, op );
      break;
    case VARIABLE_E:
      AstPrintVariableGraph( fid, op );
      break;
    case FUNCTION_PTR_E:
      AstPrintFunctionPtrGraph( fid, op );
      break;
    case FUNCTION_ARG_E:
      AstPrintFunctionArgGraph( fid, op );
      break;
    case BINARY_OPERATION_E:
      AstPrintBinaryOpGraph( fid, op );
      break;
    case UNARY_OPERATION_E:
      AstPrintUnaryOpGraph( fid, op );
      break;
    case FUNCTION_CALL_E:
      AstPrintFunctionCallGraph( fid, op );
      break;
    default:
      printf( "ERROR" );
  }

  __exit_function__( )

  return;

}


void 
AstPrintTreeConnections( FILE* fid, ast_node_t* op )
{


  int bl, br;
  int  il, ir;


  __enter_function__( )

  // printf( "Node Idx :: %d\n", op->node_idx );

  bl=0;
  br=0;
  il=0;
  ir=0;
  if ( op->left != NULL )
  {
    bl=1;
    il=op->left->node_idx;
    AstPrintTreeConnections( fid, op->left );
  }
  if ( op->right != NULL )
  {
    br=1;
    ir=op->right->node_idx;
    AstPrintTreeConnections( fid, op->right );
  }

  // print connections
  if ( bl==1 & br==0 )
  {
    fprintf( fid, "%d -> %d\n", op->node_idx, il );
  }

  if ( bl==0 & br==1 )
  {
    fprintf( fid, "%d -> %d\n", op->node_idx, ir );
  }

  if ( bl==1 & br==1 )
  {
    fprintf( fid, "%d -> %d\n", op->node_idx, il );
    fprintf( fid, "%d -> %d\n", op->node_idx, ir );
  }

  __exit_function__( )

  return;

}


int
AstCheckDependency( ast_node_t* op, char* VarName  )
{


  __enter_function__( )

  int dep_left;
  int dep_right;
  int dep_loc;
  int dep;

  dep_left  = 0;
  dep_right = 0;
  dep_loc   = 0;

  /* Recursive call to the left subtree */
  if ( op->left != NULL )
  {
    dep_left = AstCheckDependency( op->left, VarName );
    __debug_printf__( "Ramo sinistro :: %d\n", dep_left );
  }

  /* Recursive call to the right subtree */
  if ( op->right != NULL )
  {
    dep_right = AstCheckDependency( op->right, VarName );
    __debug_printf__( "Ramo destro :: %d\n", dep_right );
  }

  /* Chec dependency on the current node */
  node_type_t sel = op->PayloadType;
  if ( sel == VARIABLE_E ){
    __debug_printf__( "Il nodo è una variabile e si chiama: %s\n", ((ast_node_variable_t*)op->Payload)->tptr->name );
    __debug_printf__( "Il nodo è una variabile e il risultato del check è: %d\n", strcmp( ((ast_node_variable_t*)op->Payload)->tptr->name, VarName ) );
    if ( strcmp( ((ast_node_variable_t*)op->Payload)->tptr->name, VarName ) == 0 ) {
      dep_loc = 1;
    }
    else {
      dep_loc = 0;
    }
  } 
  else {
     dep_loc = 0;
  }
  __debug_printf__( "Nodo corrente :: %d\n", dep_loc );

  /* generate the dependency of the subtree */
  if ( dep_left || dep_right || dep_loc ){
    __debug_printf__( "Ho trovato una dipendenza: %d, %d, %d\n", dep_left, dep_right, dep_loc );
    dep = 1;
  }
  else {
    dep = 0;
  }

  __exit_function__( )

  return dep;

}




ast_node_t* AstCopyNode( ast_node_t* inp_node )
{

  __enter_function__( )

  ast_node_t* tmp = (ast_node_t*)malloc( sizeof(ast_node_t) );

  /* Copy the context specific data */
  switch (inp_node->PayloadType)
  {
    case NUM_E: {
      ast_node_number_t* loc_payload = (ast_node_number_t*)malloc( sizeof(ast_node_number_t) );
      loc_payload->number = ((ast_node_number_t*)inp_node->Payload)->number;
      tmp->Payload = (void*)loc_payload;
      break;
      }
    case CONST_E: {
      ast_node_constant_t* loc_payload = (ast_node_constant_t*)malloc( sizeof(ast_node_constant_t) );
      loc_payload->constant = ((ast_node_constant_t*)inp_node->Payload)->constant;
      tmp->Payload = (void*)loc_payload;
      break;
      }
    case VARIABLE_E: {
      ast_node_variable_t* loc_payload = (ast_node_variable_t*)malloc( sizeof(ast_node_variable_t) );
      loc_payload->tptr = ((ast_node_variable_t*)inp_node->Payload)->tptr;
      tmp->Payload = (void*)loc_payload;
      break;
      }
    case FUNCTION_CALL_E: {
      ast_node_fcn_eval_t* loc_payload = (ast_node_fcn_eval_t*)malloc( sizeof(ast_node_fcn_eval_t) );
      loc_payload->numArgs = ((ast_node_fcn_eval_t*)inp_node->Payload)->numArgs;
      tmp->Payload = (void*)loc_payload;
      break;
      }
    case FUNCTION_PTR_E: {
      ast_node_fcn_ptr_t* loc_payload = (ast_node_fcn_ptr_t*)malloc( sizeof(ast_node_fcn_ptr_t) );
      loc_payload->tptr = ((ast_node_fcn_ptr_t*)inp_node->Payload)->tptr;
      tmp->Payload = (void*)loc_payload;
      break;
      }
    case FUNCTION_ARG_E: {
      ast_node_fcn_arg_t* loc_payload = (ast_node_fcn_arg_t*)malloc( sizeof(ast_node_fcn_arg_t) );
      loc_payload->argIdx = ((ast_node_fcn_arg_t*)inp_node->Payload)->argIdx;
      tmp->Payload = (void*)loc_payload;
      break;
      }
    case BINARY_OPERATION_E: {
      ast_node_binaryop_t* loc_payload = (ast_node_binaryop_t*)malloc( sizeof(ast_node_binaryop_t) );
      loc_payload->BinaryOperationType = ((ast_node_binaryop_t*)inp_node->Payload)->BinaryOperationType;
      tmp->Payload = (void*)loc_payload;
      break;
      }
    case UNARY_OPERATION_E: {
      ast_node_unaryop_t* loc_payload = (ast_node_unaryop_t*)malloc( sizeof(ast_node_unaryop_t) );
      loc_payload->UnaryOperationType = ((ast_node_unaryop_t*)inp_node->Payload)->UnaryOperationType;
      tmp->Payload = (void*)loc_payload;
      break;
      }
    default:
      printf( "ERROR" );
  }

  /* Local variables in each node */
  tmp->node_idx = inp_node->node_idx;
  tmp->PayloadType = inp_node->PayloadType;

  /* Reset connectivity */
  tmp->left = NULL;
  tmp->right = NULL;
  tmp->parent = NULL;

  __exit_function__( )

  return tmp;

}


ast_node_t* 
AstCopyTree( ast_node_t* inp_node )
{

  __enter_function__( )

  ast_node_t* tmp;
  ast_node_t* tmp_left;
  ast_node_t* tmp_right;


  tmp = NULL;
  tmp_left = NULL;
  tmp_right = NULL;
  if (inp_node != NULL ){

    if ( inp_node->left != NULL )
    {
      tmp_left = AstCopyTree( inp_node->left );
    }
    else
    {
      tmp_left = NULL;
    }

    /* Recursive call to the right subtree */
    if ( inp_node->right != NULL )
    {
      tmp_right = AstCopyTree( inp_node->right );
    }
    else
    {
      tmp_right = NULL;
    }

    /* Link the new tree */
    tmp = AstCopyNode( inp_node );
    tmp->left = tmp_left;
    tmp->right = tmp_right;
    if ( tmp_left  != NULL ) tmp_left->parent  = tmp;
    if ( tmp_right != NULL ) tmp_right->parent = tmp;

  }

  __exit_function__( )

  return tmp;

}


void AstDeleteNode( ast_node_t* inp_node )
{

  __enter_function__( )

  if ( inp_node != NULL )
  {
    if ( inp_node->Payload != NULL )
    {
      inp_node->PayloadType = -1;
      free( inp_node->Payload );
      inp_node->Payload = NULL;
    }
    free( inp_node );
    inp_node = NULL;
  }

  __exit_function__( )

  return;

}



void AstDeleteTree( ast_node_t* inp_node )
{

  __enter_function__( )

  if (inp_node != NULL ){

    if ( inp_node->left != NULL )
    {
      AstDeleteTree( inp_node->left );
    }


    /* Recursive call to the right subtree */
    if ( inp_node->right != NULL )
    {
      AstDeleteTree( inp_node->right );
    }


    /* Link the new tree */
    AstDeleteNode( inp_node );

  }

  __exit_function__( )

  return;

}



void
AstNodesRenumbering( ast_node_t* inp_tree, int* n )
{

  __enter_function__( )

  /* Recursive call to the left node */
  if ( inp_tree->left != NULL )
  {
    AstNodesRenumbering( inp_tree->left, n );
  }

  /* Recursive call to the right node */
  if ( inp_tree->right != NULL )
  {
    AstNodesRenumbering( inp_tree->right, n );
  }


  /* Sccording to the payload type print the correct node */
  inp_tree->node_idx = ++(*n);

  __exit_function__( )

  return;

}


