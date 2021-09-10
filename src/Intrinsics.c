#include "Intrinsics.h"

void
AddIntrinsics( HashTable_t *SymbolTable )
{

    /* Local variables */
    int i;
    SymbolTableData_t* data;


struct init_fnct const fcn[] =
{
    "sin",        &sin,   ST_FUNC_01_E,
    "cos",        &cos,   ST_FUNC_01_E,
    "tan",        &tan,   ST_FUNC_01_E,

    "asin",       &asin,  ST_FUNC_01_E,
    "arcsin",     &asin,  ST_FUNC_01_E,
    "acos",       &acos,  ST_FUNC_01_E,
    "arccos",     &acos,  ST_FUNC_01_E,
    "atan",       &atan,  ST_FUNC_01_E,
    "arctan",     &atan,  ST_FUNC_01_E,

    "sinh",       &sinh,  ST_FUNC_01_E,
    "cosh",       &cosh,  ST_FUNC_01_E,
    "tanh",       &tanh,  ST_FUNC_01_E,

    "ln",         &log,   ST_FUNC_01_E,
    "log",        &log,   ST_FUNC_01_E,
    "lg",         &log10, ST_FUNC_01_E,
    "log10",      &log10, ST_FUNC_01_E,
    "exp",        &exp,   ST_FUNC_01_E,

    "sqrt",       &sqrt,  ST_FUNC_01_E,
    "abs",        &fabs,  ST_FUNC_01_E,
    "ceil",       &ceil,  ST_FUNC_01_E,
    "floor",      &floor, ST_FUNC_01_E,

    "atan2",      &atan2, ST_FUNC_02_E,
    "pow",        &pow,   ST_FUNC_02_E,
    "mod",        &fmod,  ST_FUNC_02_E,

    0,            0, 0
};



struct init_const const pre_vars[] =
{
    "e",        2.718281828, ST_CONST_E,
    "pi",       3.141592653, ST_CONST_E,

    0,            0, 0
};

    /* Functions 0 */
    for (i = 0; fcn[i].fname != 0; i++)
    {
        data = (SymbolTableData_t*)malloc( sizeof(SymbolTableData_t) );
        data->val.fcn_ptr = fcn[i].fnct;
        size_t len = strlen(fcn[i].fname);
        data->name = (char*) malloc( len+1 );
        memset( data->name, 0, len+1 );
        data->type = fcn[i].type;
        memcpy( data->name, fcn[i].fname, len );
        AddSymbolTableNode( SymbolTable, data->name, data );
   }


    /* Constants */
    for (i = 0; pre_vars[i].fname != 0; i++)
    {
        data = (SymbolTableData_t*)malloc( sizeof(SymbolTableData_t) );
        data->val.data_d = pre_vars[i].var;
        size_t len = strlen(pre_vars[i].fname);
        data->name = (char*) malloc( len+1 );
        memset( data->name, 0, len+1 );
        data->type = pre_vars[i].type;
        memcpy( data->name, pre_vars[i].fname, len );
        AddSymbolTableNode( SymbolTable, data->name, data );
    }

    /* Exit point */
    return;

}
