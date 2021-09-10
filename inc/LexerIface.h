#ifndef __LEXER_IFACE_H__
#define __LEXER_IFACE_H__

typedef void* yyscan_t;
/* REplace the prototype of the lexer 
#define YY_DECL int testlex \
               (YYSTYPE * yylval_param, YYLTYPE * yylloc_param , HashTable_t** symbolTable, int line, yyscan_t yyscanner) */
extern int testlex(DOUBLE_STYPE * yylval_param, DOUBLE_LTYPE * yylloc_param , HashTable_t** symbolTable, int line, yyscan_t yyscanner);

#endif /* __LEXER_IFACE_H__ */
