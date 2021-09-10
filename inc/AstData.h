#ifndef __AST_DATA_H__
#define __AST_DATA_H__


#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tgmath.h>

#include "Utils.h"
#include "SymbolTable.h"

static int node_idx = 0;

/*
 * Node type
 */
enum node_type
{
  NUM_E,               /* Number */
  CONST_E,             /* Constant */
  VARIABLE_E,          /* Variable */
  FUNCTION_PTR_E,      /* Function pointer */
  FUNCTION_ARG_E,      /* Function arg */
  BINARY_OPERATION_E,  /* Binary operation */
  UNARY_OPERATION_E,   /* Unary operation */
  FUNCTION_CALL_E
};

enum binop_type
{
  ASSIGNMENT_E,
  SUM_E,
  SUB_E,
  MUL_E,
  DIV_E,
  MOD_E,
  POW_E,
};

enum unaryop_type
{
  NEG_E,
  LAST_ARG_E
};

typedef enum node_type node_type_t;
typedef enum binop_type binop_type_t;
typedef enum unaryop_type unaryop_type_t;


struct ast_node_number
{
  double number;
};


struct ast_node_constant
{
  double constant;
};


struct ast_node_variable
{
    SymbolTableData_t *tptr;
};

struct ast_node_fcn_eval
{
    int numArgs;
};

struct ast_node_fcn_pointer
{
    SymbolTableData_t *tptr;
};

struct ast_node_fcn_arg
{
    int argIdx;
};

struct ast_node_binaryop
{
    binop_type_t BinaryOperationType;
};

struct ast_node_unaryop
{
    unaryop_type_t UnaryOperationType;
};


/* Payloads */
typedef struct ast_node_number      ast_node_number_t;
typedef struct ast_node_constant    ast_node_constant_t;
typedef struct ast_node_variable    ast_node_variable_t;
typedef struct ast_node_fcn_eval    ast_node_fcn_eval_t;
typedef struct ast_node_fcn_pointer ast_node_fcn_ptr_t;
typedef struct ast_node_fcn_arg     ast_node_fcn_arg_t;
typedef struct ast_node_binaryop    ast_node_binaryop_t;
typedef struct ast_node_unaryop     ast_node_unaryop_t;

/*
 * Node container
 */
struct ast_node
{

   /* Payload */ 
  int    node_type;
  int    node_idx;

  /* Node data payload */
  node_type_t PayloadType;
  void* Payload;

  /* Management */ 
  struct ast_node* parent;
  struct ast_node* left;
  struct ast_node* right;

};

typedef struct ast_node ast_node_t;



/* Function type. */
typedef double (* func_zero) ();
typedef double (* func_one) (double);
typedef double (* func_two) (double, double);
typedef double (* func_three) (double, double, double);
typedef double (* func_many) ( ast_node_t *);

#endif /* __AST_DATA_H__ */
