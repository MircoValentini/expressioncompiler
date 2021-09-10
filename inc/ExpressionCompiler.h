#ifndef __EXPRESSIONCOMPILER_H__
#define __EXPRESSIONCOMPILER_H__

#include <unistd.h> 

#include "FrontEnd.h"
#include "Utils.h"
#include "AstMEP_BackEnd.h"

int ExpressionCompiler( char* expression, int nVars, char** Vars, int nFcns, char** Fcns, int verbose, AstTreeDims_t* MEPdim, t_mep_chromosome* chromosome );

#endif /* __EXPRESSIONCOMPILER_H__ */
