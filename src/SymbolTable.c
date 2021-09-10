#include "SymbolTable.h"


void 
TableInit( HashTable_t* table )
{

  /* Enter function  */
  __enter_function__();

  /* Initialize the table  */
  table->hash = NULL;

  /* Exit function  */
  __exit_function__();

  /* Exit point  */
  return;	

}


void
TableFree( HashTable_t* table )
{

  /* Local variables */
  SymbolTableEntry_t* node;
  SymbolTableEntry_t* tmp;

  /* Enter function  */
  __enter_function__();

  /* Initialize the table  */
  HASH_ITER( hh, table->hash, node, tmp) {
    __debug_printf__( "Deleting node: %s\n", node->key );	  
    HASH_DEL(table->hash, node);
    if ( node->data->name != NULL ) free(node->data->name);
    if ( node->data != NULL ) free(node->data);
    if ( node != NULL ) free(node);
  }

  /* Exit function  */
  __exit_function__();

  /* Exit point  */
  return;

}


SymbolTableEntry_t* 
GetSymbolTableNode( HashTable_t* table, char* key )
{

  /* Local variables  */
  SymbolTableEntry_t* node;
  char tmp[__HASH_KEY_SIZE__];
  size_t len;

  /* Enter function  */
  __enter_function__();

  /* Compute the length of the string  */
  node = NULL;
  len = strlen(key);

  /* Debug code  */
  __debug_printf__( "Search for: |%s| key;\n", key  );
  __debug_printf__( "keylength: %d\n", (int)len );
  /* Debug exit function  */
  if ( (*table).hash == NULL ){
    __debug_printf__( "C'è un problema\n" );
    return NULL;
  }

  if ( HASH_COUNT( (*table).hash ) == 0 ){
    __debug_printf__( "Tabella vuota\n" );
    return NULL;
  }

  __debug_printf__( "memset;\n" );
  memset( tmp, 0, __HASH_KEY_SIZE__  );

  __debug_printf__( "memcpy;\n" );
  memcpy( tmp, key, len );

  /* Search the node in the table */
  __debug_printf__( "Hash test;\n" );
  if ( (*table).hash == NULL ) {
    __debug_printf__( "Error;\n" );
  }
  __debug_printf__( "Hash find;\n" );
  HASH_FIND( hh, (*table).hash, tmp, __HASH_KEY_SIZE__, node );
  __debug_printf__( "Hash find result;\n" );

  /* Debug exit function  */
  if ( node == NULL ){
    __debug_printf__( "Node not found\n" );
  } 

  /* Exit function  */
  __exit_function__();

  /* Exit point  */
  return node;

} /* GetSymbolTableNode */


SymbolTableEntry_t*
AddSymbolTableNode( HashTable_t* table,  char* key, SymbolTableData_t* data  )
{

  /* Local variables  */
  SymbolTableEntry_t* node;
  size_t len;

  /* Exit function  */
  __enter_function__()

  /* Allocate our structure. initialize to some values */
  node = (SymbolTableEntry_t*)calloc(1UL,sizeof(SymbolTableEntry_t));

  /* Compute the length of the string  */
  len = strlen(key);
  __debug_printf__( "Insert key: %s, of length: %d\n", key, (int)len );
  
  /* Copy the key to the node   */
  memset( node->key, 0, __HASH_KEY_SIZE__ );
  memcpy( node->key, key, len );
  __debug_printf__( "The new key is: %s\n", node->key );

  /* Add the data in the container  */
  node->data = data;

  /* Insert node into the hash table  */
  HASH_ADD( hh, (*table).hash, key, __HASH_KEY_SIZE__, node);

  /* Debug exit function  */
  __debug_cond_printf__( ( (*table).hash != NULL  ), "Data inserted;\n" );

  /* Exit function  */
  __exit_function__();

  /* Exit point  */
  return node;

} /* AddSymbolTableNode */





