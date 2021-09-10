#ifndef __ASTMEP_BACKEND_H__
#define __ASTMEP_BACKEND_H__


#include "AstData.h"
#include "AstUtils.h"


#ifndef __AST_DATA_H__
  #error "Expected AstData.h included before AstUtils.h"
#endif


/* Useful structure for converting Ast to MEP*/
typedef struct _AstTreeDims {

  int NumNodes;
  int NumConstants;
  int NumVariables;

} AstTreeDims_t;

typedef struct _t_code3 {
        int op;             // either a variable, operator or constant; 
                            // variables are indexed from 0: 0,1,2,...; 
                            // constants are indexed from num_variables
                            // operators are -1, -2, -3...
        int addr1, addr2;   // pointers to arguments
}t_code3;

typedef struct _t_result {
        double fitness;         // the fitness (or the error)
        int    complexity;      // the complexity
        int    idx;                     // index
}t_result;

typedef struct _t_mep_chromosome {
        t_code3  *code;          // the program - a string of genes
        double   *constants;     // an array of constants
        t_result  best_fitness;
        t_result  best_complexity;
        t_result  best_overall;
}t_mep_chromosome;

/* Helpers for MEP generation */
void AstCreateMepTable( ast_node_t* source_tree, t_mep_chromosome* chromosome, AstTreeDims_t* MEPdim, int nVars, char** vars, int nFcns, char** fcns );



#endif /* __ASTMEP_BACKEND_H__ */
