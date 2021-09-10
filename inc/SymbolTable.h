#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__


/* Header for the hash table  */
#include "uthash.h"
#include "Utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/* Definition of the key length  */
#define __HASH_KEY_SIZE__ 64


/* Abstract function pointer */
typedef void * func_t;


/* Datatypes that can be stored in this table  */
typedef enum { 
    ST_VAR_E,
    ST_CONST_E,
    ST_FUNC_00_E,
    ST_FUNC_01_E,
    ST_FUNC_02_E,
    ST_FUNC_03_E,
    ST_FUNC_04_E,
    ST_FUNC_05_E,
    ST_FUNC_06_E,
    ST_FUNC_07_E,
    ST_FUNC_08_E,
    ST_FUNC_09_E,
    ST_FUNC_10_E,
} DataTypes_e;


/* Symbol table container dfinition */
typedef struct {
    char* name;
    DataTypes_e type;
    union {
      double data_d;  /* value of a double */
      func_t fcn_ptr; /* value of a FNCT */
    } val;
} SymbolTableData_t;


/* Conatiner data  */
typedef struct {
    UT_hash_handle hh;
    SymbolTableData_t* data;
    char key[__HASH_KEY_SIZE__];
} SymbolTableEntry_t;


/* Table definition  */
typedef struct {
  SymbolTableEntry_t* hash;
} HashTable_t;


/* Create/Destroy a new symbol table entry  */
void TableInit( HashTable_t* table );
void TableFree( HashTable_t* table );


/* Manage symbol table  */
SymbolTableEntry_t* GetSymbolTableNode( HashTable_t* table, char* key );
SymbolTableEntry_t* AddSymbolTableNode( HashTable_t* table, char* key, SymbolTableData_t* data  );

#endif /* __SYMBOL_TABLE_H__  */
