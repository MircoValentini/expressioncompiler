#include "AstMEP_BackEnd.h"


void
AstMEPNodesRenumbering00( ast_node_t* inp_tree, int* n )
{

  __enter_function__( )

  /* Recursive call to the left node */
  if ( inp_tree->left != NULL )
  {
    AstMEPNodesRenumbering00( inp_tree->left, n );
  }

  /* Recursive call to the right node */
  if ( inp_tree->right != NULL )
  {
    AstMEPNodesRenumbering00( inp_tree->right, n );
  }

  inp_tree->node_idx = -999;

  if ( inp_tree->PayloadType != FUNCTION_PTR_E &&
       inp_tree->PayloadType != FUNCTION_ARG_E )
  {
    inp_tree->node_idx = ++(*n);
  }

  if ( inp_tree->PayloadType == FUNCTION_CALL_E  )
  {
    int idx = -inp_tree->node_idx;
    inp_tree->left->node_idx = idx;
    ast_node_t* curr_node;
    if ( inp_tree->right != NULL ){
      curr_node = inp_tree->right;
      while ( curr_node != NULL )
      {
        curr_node->node_idx = idx;
        curr_node = curr_node->right;
      }
    }
  }

  __exit_function__( )

  return;

}


void
AstMEPChangeUnaryNeg( ast_node_t* inp_tree )
{

  __enter_function__( )

  /* Recursive call to the left node */
  if ( inp_tree->left != NULL )
  {
    AstMEPChangeUnaryNeg( inp_tree->left );
  }

  /* Recursive call to the right node */
  if ( inp_tree->right != NULL )
  {
    AstMEPChangeUnaryNeg( inp_tree->right );
  }


  if ( inp_tree->PayloadType )
  {
    if ( ((ast_node_unaryop_t*)inp_tree->Payload )->UnaryOperationType == NEG_E )
    {
      inp_tree->PayloadType = BINARY_OPERATION_E;
      free( inp_tree->Payload );
      ast_node_binaryop_t* loc_payload = (ast_node_binaryop_t*)malloc( sizeof(ast_node_binaryop_t) );
      loc_payload->BinaryOperationType = MUL_E;
      inp_tree->Payload = (void*) loc_payload;
      //
      inp_tree->left = (ast_node_t*)malloc( sizeof(ast_node_t) );
      ast_node_number_t* loc_payload0 = (ast_node_number_t*)malloc( sizeof(ast_node_number_t) );
      inp_tree->left->node_idx = ++node_idx;
      loc_payload0->number = -1.0;
      inp_tree->left->Payload = (void*)loc_payload0;
      inp_tree->left->PayloadType = NUM_E;
      inp_tree->left->left=NULL;
      inp_tree->left->right=NULL;
    }
  }

  __exit_function__( )

  return;

}





void
AstMEPPrintID( ast_node_t* inp_tree )
{

  __enter_function__( )

  /* Recursive call to the left node */
  if ( inp_tree->left != NULL )
  {
    AstMEPPrintID( inp_tree->left );
  }

  /* Recursive call to the right node */
  if ( inp_tree->right != NULL )
  {
    AstMEPPrintID( inp_tree->right );
  }


  printf( "ID del nodo :: %d, %d \n", inp_tree->node_idx, (int)(inp_tree->PayloadType) );

  __exit_function__( )

  return;

}


int AstCheckUnaryOp( ast_node_t* inp_tree )
{


  __enter_function__( )

  int res = 0;

  /* Recursive call to the left node */
  if ( inp_tree->left != NULL )
  {
    res += AstCheckUnaryOp( inp_tree->left );
  }

  /* Recursive call to the right node */
  if ( inp_tree->right != NULL )
  {
    res += AstCheckUnaryOp( inp_tree->right );
  }

  if (  inp_tree->PayloadType == UNARY_OPERATION_E ){
    if ( ((ast_node_unaryop_t*)inp_tree->Payload)->UnaryOperationType == NEG_E ) {
      res += 1;
    }
  }

  return res;

}

void AstNumNodesPvt( ast_node_t* inp_tree, AstTreeDims_t* n )
{

  __enter_function__( )

  /* Recursive call to the left node */
  if ( inp_tree->left != NULL )
  {
    AstNumNodesPvt( inp_tree->left, n );
  }

  /* Recursive call to the right node */
  if ( inp_tree->right != NULL )
  {
    AstNumNodesPvt( inp_tree->right, n );
  }

  /* According to the payload type print the correct node */
  if (
    inp_tree->PayloadType == NUM_E              ||
    inp_tree->PayloadType == CONST_E            ||
    inp_tree->PayloadType == VARIABLE_E         ||
    inp_tree->PayloadType == BINARY_OPERATION_E ||
    inp_tree->PayloadType == UNARY_OPERATION_E  ||
    inp_tree->PayloadType == FUNCTION_CALL_E     ) n->NumNodes = n->NumNodes + 1;
  
  if ( inp_tree->PayloadType == NUM_E || inp_tree->PayloadType == CONST_E )   n->NumConstants = n->NumConstants + 1;
  if ( inp_tree->PayloadType == VARIABLE_E ) n->NumVariables = n->NumVariables + 1;

  __exit_function__( )

  return;

}


/* Compute the number of nodes in the tree */
AstTreeDims_t AstNumNodes( ast_node_t* inp_tree )
{

  __enter_function__( )

  /* Local variables */
  AstTreeDims_t n;

  /* Initialization*/
  n.NumNodes = 0;
  n.NumConstants = 0;
  n.NumVariables = 0;

  AstNumNodesPvt( inp_tree, &n );

  __exit_function__( )

  return n;

}


int BinaryOpToBeAdded( ast_node_t** MEP_Table, ast_node_t* node, int MEPpos )
{

  __enter_function__( )


  int cnt;
  int j;
  int ThisNodeAlreadyIn = 0; 
  int LeNodeAlreadyIn = 0; 
  int RiNodeAlreadyIn = 0; 
  for ( cnt=0; cnt<MEPpos; cnt++ ) 
  { 
    if ( node->node_idx == MEP_Table[cnt]->node_idx ) ThisNodeAlreadyIn++;
    if ( node->left  != NULL ) if ( node->left->node_idx  == MEP_Table[cnt]->node_idx ) LeNodeAlreadyIn++;
    if ( node->right != NULL ) if ( node->right->node_idx == MEP_Table[cnt]->node_idx ) RiNodeAlreadyIn++;
  }


  __exit_function__( )

  return ( ThisNodeAlreadyIn==0 && LeNodeAlreadyIn>0 && RiNodeAlreadyIn>0 ) ? 1 : 0;

}



int UnaryOpToBeAdded( ast_node_t** MEP_Table, ast_node_t* node, int MEPpos )
{

  __enter_function__( )


  int cnt;
  int j;
  int ThisNodeAlreadyIn = 0; 
  int LeNodeAlreadyIn = 0; 
  int RiNodeAlreadyIn = 0; 
  for ( cnt=0; cnt<MEPpos; cnt++ ) 
  { 
    if ( node->node_idx == MEP_Table[cnt]->node_idx ) ThisNodeAlreadyIn++;
    if ( node->left  == NULL ) LeNodeAlreadyIn++;
    if ( node->right != NULL ) if ( node->right->node_idx == MEP_Table[cnt]->node_idx ) RiNodeAlreadyIn++;
  }

  __exit_function__( )

  return ( ThisNodeAlreadyIn==0 && LeNodeAlreadyIn>0 && RiNodeAlreadyIn>0 ) ? 1 : 0;

}


int FunctionCallToBeAdded( ast_node_t** MEP_Table, ast_node_t* node, int MEPpos )
{

  __enter_function__( )


  int cnt;
  int j;
  int nArgs;
  int res;
  int ThisNodeAlreadyIn = 0; 
  int LeNodeAlreadyIn = 0;

  ThisNodeAlreadyIn = 0; 
  for ( cnt=0; cnt<MEPpos; cnt++ ) 
  { 
    if ( node->node_idx == MEP_Table[cnt]->node_idx ) ThisNodeAlreadyIn++;
  }

  res = 0;
  nArgs = ((ast_node_fcn_eval_t*)node->Payload)->numArgs;
  ast_node_t* curr_node = node;
  for ( j=0; j<nArgs; j++ )
  {
    LeNodeAlreadyIn = 0;
    if ( curr_node != NULL ){
      curr_node = curr_node->right;
      if ( curr_node != NULL ){
        for ( cnt=0; cnt<MEPpos; cnt++ ) 
        { 
          if ( curr_node->left->node_idx == MEP_Table[cnt]->node_idx ) LeNodeAlreadyIn++;
        }
        res += ( LeNodeAlreadyIn>=1 ) ? 1 : 0;
      }
    }
  }

  __exit_function__( )

  return ( ThisNodeAlreadyIn==0 && res==nArgs ) ? 1 : 0;

}


int NodeToBeAdded( ast_node_t** MEP_Table, ast_node_t* node, int MEPpos )
{

  __enter_function__( )

  int cnt;
  int j;
  int res;
  int ThisNodeAlreadyIn = 0; 
  int LeNodeAlreadyIn = 0; 
  int RiNodeAlreadyIn = 0; 

  res = 0;
  if ( node != NULL ){
    switch (node->PayloadType)
    {
      case FUNCTION_CALL_E: {
        res = FunctionCallToBeAdded( MEP_Table, node, MEPpos );
        break;
        }

      case BINARY_OPERATION_E: {
        res = BinaryOpToBeAdded( MEP_Table, node, MEPpos );
        break;
        }

      case UNARY_OPERATION_E: {
        res = UnaryOpToBeAdded( MEP_Table, node, MEPpos );
        break;
        }
    }
  }

  __exit_function__( )

  return res;

}


void MEPAddVariables( ast_node_t* inp_tree, ast_node_t** MEPtab, int* MEPidx )
{

  __enter_function__( )

  /* Recursive call to the left node */
  if ( inp_tree->left != NULL )
  {
    MEPAddVariables( inp_tree->left, MEPtab, MEPidx );
  }

  /* Recursive call to the right node */
  if ( inp_tree->right != NULL )
  {
    MEPAddVariables( inp_tree->right, MEPtab, MEPidx );
  }

  /* Add variables nodes */
  if ( inp_tree->PayloadType == VARIABLE_E ) 
  {
    MEPtab[*MEPidx] = inp_tree;
    *MEPidx = *MEPidx + 1;
  }

  __exit_function__( )

  return;

}


void MEPAddConstants( ast_node_t* inp_tree, ast_node_t** MEPtab, int* MEPidx )
{

  __enter_function__( )

  /* Recursive call to the left node */
  if ( inp_tree->left != NULL )
  {
    MEPAddConstants( inp_tree->left, MEPtab, MEPidx );
  }

  /* Recursive call to the right node */
  if ( inp_tree->right != NULL )
  {
    MEPAddConstants( inp_tree->right, MEPtab, MEPidx );
  }

  /* Add constants nodes */
  if ( inp_tree->PayloadType == NUM_E || inp_tree->PayloadType == CONST_E ) 
  {
    MEPtab[*MEPidx] = inp_tree;
    *MEPidx = *MEPidx + 1;
  }

  __exit_function__( )

  return;

}


void MEPAddOp( ast_node_t* inp_tree, ast_node_t** MEPtab, int MEPpos, int* MEPidx )
{

  __enter_function__( )

  /* Recursive call to the left node */
  if ( inp_tree->left != NULL )
  {
    MEPAddOp( inp_tree->left, MEPtab, MEPpos, MEPidx );
  }

  /* Recursive call to the right node */
  if ( inp_tree->right != NULL )
  {
    MEPAddOp( inp_tree->right, MEPtab, MEPpos, MEPidx );
  }

  /* Add operations */
  int bValidNode = NodeToBeAdded( MEPtab, inp_tree, MEPpos );
  if ( bValidNode == 1 ) 
  {
    MEPtab[*MEPidx] = inp_tree;
    *MEPidx = *MEPidx + 1;
  }

  __exit_function__( )

  return;

}


void Op2FcnIdx( ast_node_t* op, 
                int nFcns, 
                char** fcns, 
                int* MEPReverseMapping, 
                int* fcn_idx, 
                int* arg1_idx, 
                int* arg2_idx,
                int* err )
{

  *fcn_idx = -999;
  *arg1_idx = -999;
  *arg2_idx = -999;

  int loop=1;
  int i = 0;
  *err = 0;

  switch (op->PayloadType)
  {
    case FUNCTION_CALL_E: {
      loop=1;
      i = 0;
      while (loop == 1 )
      {
        if ( strcmp( ((ast_node_fcn_ptr_t*)op->left->Payload)->tptr->name, fcns[i] ) == 0 ) loop=0;
        if (loop==1) i++;
        if ( i >= nFcns ) loop=-1;
      }
      if ( loop == 0 )
      {
        *fcn_idx = i;
        *arg1_idx = MEPReverseMapping[op->right->left->node_idx];
        *arg2_idx = -1;
      }
      break;
      }
    case BINARY_OPERATION_E: {
      binop_type_t sel = ((ast_node_binaryop_t*)op->Payload)->BinaryOperationType;
      switch ( sel )
      {
        case SUM_E:
          loop=1;
          i = 0;
          while (loop == 1 )
          {
            if ( strcmp( "sum", fcns[i] ) == 0 ) loop=0;
            if (loop==1) i++;
            if ( i >= nFcns ) loop=-1;
          }
          if ( loop == 0 )
          {
            *fcn_idx = i;
            *arg1_idx = MEPReverseMapping[op->left->node_idx];
            *arg2_idx = MEPReverseMapping[op->right->node_idx];
          }
          break;
        case SUB_E:
          loop=1;
          i = 0;
          while (loop == 1 )
          {
            if ( strcmp( "sub", fcns[i] ) == 0 ) loop=0;
            if (loop==1) i++;
            if ( i >= nFcns ) loop=-1;
          }
          if ( loop == 0 )
          {
            *fcn_idx = i;
            *arg1_idx = MEPReverseMapping[op->left->node_idx];
            *arg2_idx = MEPReverseMapping[op->right->node_idx];
          }
          break;
        case MUL_E:
          loop=1;
          i = 0;
          while (loop == 1 )
          {
            if ( strcmp( "mul", fcns[i] ) == 0 ) loop=0;
            if (loop==1) i++;
            if ( i >= nFcns ) loop=-1;
          }
          if ( loop == 0 )
          {
            *fcn_idx = i;
            *arg1_idx = MEPReverseMapping[op->left->node_idx];
            *arg2_idx = MEPReverseMapping[op->right->node_idx];
          }
          break;
        case DIV_E:
          loop=1;
          i = 0;
          while (loop == 1 )
          {
            if ( strcmp( "div", fcns[i] ) == 0 ) loop=0;
            if (loop==1) i++;
            if ( i >= nFcns ) loop=-1;
          }
          if ( loop == 0 )
          {
            *fcn_idx = i;
            *arg1_idx = MEPReverseMapping[op->left->node_idx];
            *arg2_idx = MEPReverseMapping[op->right->node_idx];
          }
          break;
        case MOD_E:
          loop=1;
          i = 0;
          while (loop == 1 )
          {
            if ( strcmp( "mod", fcns[i] ) == 0 ) loop=0;
            if (loop==1) i++;
            if ( i >= nFcns ) loop=-1;
          }
          if ( loop == 0 )
          {
            *fcn_idx = i;
            *arg1_idx = MEPReverseMapping[op->left->node_idx];
            *arg2_idx= MEPReverseMapping[op->right->node_idx];
          }
          break;
        case POW_E:
          loop=1;
          i = 0;
          while (loop == 1 )
          {
            if ( strcmp( "pow", fcns[i] ) == 0 ) loop=0;
            if (loop==1) i++;
            if ( i >= nFcns ) loop=-1;
          }
          if ( loop == 0 )
          {
            *fcn_idx = i;
            *arg1_idx = MEPReverseMapping[op->left->node_idx];
            *arg2_idx = MEPReverseMapping[op->right->node_idx];
          }
          break;
        default:
          *err = 2;
      }
      break;
      }
    default:
      *err = 2;
  }


}


/* Sort nodes into a Abstract MEP Table */
void AstCreateMepTable( 
	ast_node_t* source_tree,
	t_mep_chromosome* chromosome,
	AstTreeDims_t* MEPdim, 
	int nVars, 
	char** vars,
	int nFcns, 
	char** Fcns )
{


  __enter_function__( )

  /* Local variables */
  int cnt;
  int i;
  int MEPidx;
  int MEPpos;
  ast_node_t** MEPtab;
  int* MEPReverseMapping;

  /* Create a local copy of the parsing tree */
  ast_node_t* inp_tree = AstCopyTree( source_tree );

  /* Renumbering the nodes */
  cnt = 0;
  AstMEPChangeUnaryNeg( inp_tree );
  AstMEPNodesRenumbering00( inp_tree, &cnt );

  /* Compute the Dimensions of the MEP Table */
  *MEPdim = AstNumNodes( inp_tree );


  /* Allocate Abstract MEP Table */
  MEPtab            = (ast_node_t**) malloc( MEPdim->NumNodes*sizeof(ast_node_t*) );
  MEPReverseMapping = (int*) malloc( MEPdim->NumNodes*sizeof(int) );

  /* Initialize MEP index */
  MEPidx = 0;
  MEPpos = 0;

  /* Add the variables */
  MEPAddVariables( inp_tree, MEPtab, &MEPidx );

  /* Add the constants */
  MEPAddConstants( inp_tree, MEPtab, &MEPidx );


  /* Add Operations to the MEP Table */
  int ii=0;
  while ( MEPidx < MEPdim->NumNodes && ii<MEPdim->NumNodes )
  {
    ii++;
    MEPpos = MEPidx;
    MEPAddOp( inp_tree, MEPtab, MEPpos, &MEPidx );
  }

  /* Construct the reverse mapping to be used to 
     locate the operands of an operation */
  for ( cnt=0; cnt<MEPdim->NumNodes; cnt++ )
    if ( MEPtab[cnt] != NULL ) MEPReverseMapping[ MEPtab[cnt]->node_idx-1 ] = cnt;



  /* Allocate chromosome components */
  chromosome->code      = (t_code3*)malloc( MEPdim->NumNodes*sizeof(t_code3) );
  chromosome->constants = (double *)malloc( MEPdim->NumConstants*sizeof(double) );

  /* Fill the variables */
  for ( cnt=0; cnt<MEPdim->NumVariables; cnt++ )
  {
    chromosome->code[cnt].op = 99999999;
    chromosome->code[cnt].addr1 = -1;
    chromosome->code[cnt].addr2 = -1;

    int loop=1;
    i = 0;
    while (loop == 1 )
    {
      if ( strcmp( ((ast_node_variable_t*) MEPtab[cnt]->Payload)->tptr->name, vars[i] ) == 0 ) loop=0;
      if (loop==1) i++;
      if ( i >= nVars ) loop=-1;
    }
    if ( loop == 0 )
    {
      chromosome->code[cnt].op = i;
      chromosome->code[cnt].addr1 = -1;
      chromosome->code[cnt].addr2 = -1;
    }
  }
  

  /* Fill the constants */
  for ( cnt=MEPdim->NumVariables; cnt<MEPdim->NumVariables+MEPdim->NumConstants; cnt++ )
  {

    chromosome->code[cnt].op = cnt-MEPdim->NumVariables+nVars;
    chromosome->code[cnt].addr1 = -1;
    chromosome->code[cnt].addr2 = -1;
    if ( MEPtab[cnt]->PayloadType == NUM_E )
    {
      chromosome->constants[cnt-MEPdim->NumVariables] = ((ast_node_number_t*) MEPtab[cnt]->Payload)->number;
    }
    if ( MEPtab[cnt]->PayloadType == CONST_E )
    {
      chromosome->constants[cnt-MEPdim->NumVariables] = ((ast_node_constant_t*) MEPtab[cnt]->Payload)->constant;
    }
  }



  /* Adding operations to the code*/
  for ( cnt=MEPdim->NumVariables+MEPdim->NumConstants; cnt<MEPdim->NumNodes; cnt++ )
  {

    /* Local variables */
    int fcn_idx;
    int arg1_idx;
    int arg2_idx;
    int err;

    /* Convert Ast nodes to target architecture */
    Op2FcnIdx( MEPtab[cnt], nFcns, Fcns, MEPReverseMapping, &fcn_idx, &arg1_idx, &arg2_idx, &err ); 

    /* Fill MEP table */
    chromosome->code[cnt].op = -fcn_idx-1 ;
    chromosome->code[cnt].addr1 = arg1_idx;
    chromosome->code[cnt].addr2 = arg2_idx;
  }

  /* Free local memory */
  free( MEPtab );
  free( MEPReverseMapping );
  AstDeleteTree( inp_tree );

  __exit_function__( )

  return;

}


