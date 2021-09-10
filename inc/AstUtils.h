#ifndef __AST_UTILS_H__
#define __AST_UTILS_H__


#ifndef __AST_DATA_H__
  #error "Expected AstData.h included before AstUtils.h"
#endif


/* Debug print */
void AstPrintUnaryOpType( unaryop_type_t optype, ast_node_t* op);
void AstPrintBinaryOpType( binop_type_t optype, ast_node_t* left_op, ast_node_t* right_op );

/* print tree*/
void AstPrintTree( ast_node_t* op, const char* fname );
void AstPrintTreeNodes( FILE* fid, ast_node_t* op );
void AstPrintTreeConnections( FILE* fid, ast_node_t* op );


/* Print graph */
void AstPrintNumberGraph( FILE* fid, ast_node_t* op );
void AstPrintConstantGraph( FILE* fid, ast_node_t* op );
void AstPrintVariableGraph( FILE* fid, ast_node_t* op );
void AstPrintBinaryOpGraph( FILE* fid, ast_node_t* op );
void AstPrintUnaryOpGraph( FILE* fid, ast_node_t* op );

/* Check dependency */
int AstCheckDependency( ast_node_t* op, char* VarName  );

/* Copy nodes */
ast_node_t* AstCopyNode( ast_node_t* inp_node );
ast_node_t* AstCopyTree( ast_node_t* inp_tree );

/* Delete Tree */
void AstDeleteTree( ast_node_t* inp_node );
void AstDeleteNode( ast_node_t* inp_node );

/* REnumbering the tree */
void AstNodesRenumbering( ast_node_t* inp_tree, int* n );

#endif // __AST_UTILS_H__
