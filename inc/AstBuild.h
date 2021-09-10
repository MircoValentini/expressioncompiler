#ifndef __AST_BUILD_H__
#define __AST_BUILD_H__

#ifndef __AST_DATA_H__
  #error "Expected AstData.h included before AstBuild.h"
#endif

/* Leaf */
ast_node_t* AstAddNum( double val );
ast_node_t* AstAddConst( double val );
ast_node_t* AstAddVar( SymbolTableEntry_t *tptr );


/* Functions */
ast_node_t* AstAddFcnPtr( SymbolTableEntry_t *tptr );
ast_node_t* AstAddFcnPtr02( SymbolTableData_t *tptr );
ast_node_t* AstAddFcnCall( ast_node_t* fcn_ptr, ast_node_t* args );
ast_node_t* AstAddFcnLastArg( ast_node_t* fcn_arg );
ast_node_t* AstAddFcnPrevArg( ast_node_t* fcn_arg, ast_node_t* fcn_args );


/* Operations */
ast_node_t* AstAddBinOp( binop_type_t optype, ast_node_t* left_op, ast_node_t* right_op );
ast_node_t* AstAddUnaryOp( unaryop_type_t optype, ast_node_t* op );
ast_node_t* AstAddParen( ast_node_t* op );


#endif // __AST_BUILD_H__
