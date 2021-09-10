#ifndef __INTRINSIC_FUNCTIONS_H__
#define __INTRINSIC_FUNCTIONS_H__

#include <math.h>        /* Math stuff */
#include <tgmath.h>        /* Math stuff */

#include "SymbolTable.h"


struct init_fnct
{
    char const *fname;
    func_t fnct;
    DataTypes_e type;
};


struct init_const
{
    char const *fname;
    double var;
    DataTypes_e type;
};


void
AddIntrinsics( HashTable_t *sym_table );

#endif
