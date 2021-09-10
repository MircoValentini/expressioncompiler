#include "Main.h"


char** str_split(char* a_str, const char a_delim, int* sz )
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    *sz = 0;
    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            (*sz)++;
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        *(result + idx) = 0;
    }

    return result;
}

int 
main( int argc, char *argv[] )
{

  /* Input variables */
  int opt; 
  int verbose = 0; 
  char* expression;
  int nVars;
  char** Vars;
  int nFcns;
  char** Fcns;

  // put ':' in the starting of the 
  // string so that program can  
  // zdistinguish between '?' and ':'  
  while((opt = getopt(argc, argv, "e:r:o:v:")) != -1)  
  {  
      switch(opt)  
      {  
          case 'e':/* expression */
              expression = optarg;
              break;
          case 'r': /* registers */
              Vars = str_split( optarg, ':', &nVars );
              break;
          case 'o': /* operations */
              Fcns = str_split( optarg, ':', &nFcns );
              break;
          case 'v':
              verbose = atoi(optarg);
              break;  
          case '?':  
              printf("unknown option: %c\n", optopt); 
              exit(1);  
      }
  }

  /* MEP Table stage 1
  int nVars = 7;
  const char* Vars[nVars];
  Vars[0] = "x";
  Vars[1] = "p";
  Vars[2] = "y";
  Vars[3] = "q";
  Vars[4] = "z";
  Vars[5] = "r";
  Vars[6] = "t";

  int nFcns=12;
  const char* Fcns[nFcns];
  Fcns[0]  = "sum";
  Fcns[1]  = "sub";
  Fcns[2]  = "div";
  Fcns[3]  = "mul";
  Fcns[4]  = "pow";
  Fcns[5]  = "sin";
  Fcns[6]  = "cos";
  Fcns[7]  = "tan";
  Fcns[8]  = "sinh";
  Fcns[9]  = "cosh";
  Fcns[10] = "tanh";
  Fcns[11] = "sech";
 */

  if ( expression != NULL )
  {

    AstTreeDims_t     MEPdim;
    t_mep_chromosome  chromosome;

    int err = ExpressionCompiler( 
      expression, 
      nVars, 
      Vars, 
      nFcns, 
      Fcns, 
      verbose, 
      &MEPdim, 
      &chromosome );

    if ( verbose > 0 )
    {
      printf( "\n" );
      printf( " Number of nodes:     %3d\n", MEPdim.NumNodes );
      printf( " Number of variables: %3d\n", MEPdim.NumVariables );
      printf( " Number of constants: %3d\n", MEPdim.NumConstants );
      printf( "\n\n" );
      printf( " ------------------------\n" );
      printf( " | Variables table: %3d |\n", nVars );
      printf( " ------------------------\n" );
      printf( " |    id |         name |\n" );
      printf( " ------------------------\n" );
      for ( int i=0; i<nVars; i++ )
      {
        printf( " | %5.5d | %12s |\n", i, Vars[i] );
      }
      printf( " ------------------------\n" );
      printf( "\n\n" );
      printf( " ------------------------\n" );
      printf( " | Oprations table: %3d |\n", nFcns );
      printf( " ------------------------\n" );
      printf( " |    id |         name |\n" );
      printf( " ------------------------\n" );
      for ( int i=0; i<nFcns; i++ )
      {
        printf( " | %5.5d | %12s |\n", i, Fcns[i] );
      }
      printf( " ------------------------\n" );
      printf( "\n\n" );
      printf( " ------------------------\n" );
      printf( " | Constants table: %3d |\n", MEPdim.NumConstants );
      printf( " ------------------------\n" );
      printf( " |    id |        value |\n" );
      printf( " ------------------------\n" );
      for ( int i=0; i<MEPdim.NumConstants; i++ )
      {
        printf( " | %5.5d | %+12.5f |\n", i, chromosome.constants[i] );
      }
      printf( " ------------------------\n" );
      printf( "\n\n" );
      printf( " -------------------------------------\n" );
      printf( " |            MEP Table              |\n" );
      printf( " ------------------------------------- \n" );
      printf( " |   line |    op. |  addr1 |  addr2 | \n" );
      printf( " ------------------------------------- \n" );
      int cnt;
      for ( cnt=0; cnt<MEPdim.NumNodes; cnt++ ) 
      {
        printf( " | %+5.5d | %+5.5d | %+5.5d | %+5.5d |\n", cnt, chromosome.code[cnt].op, chromosome.code[cnt].addr1, chromosome.code[cnt].addr2 );
      }

      printf( " ------------------------------------- \n" );
    }

    FILE* fid = fopen( "ExpressionMEPTable.txt", "w" );
    fprintf( fid, "\n" );
    fprintf( fid, " Number of nodes:     %3d\n", MEPdim.NumNodes );
    fprintf( fid, " Number of variables: %3d\n", MEPdim.NumVariables );
    fprintf( fid, " Number of constants: %3d\n", MEPdim.NumConstants );
    fprintf( fid, "\n\n" );
    fprintf( fid, " ------------------------\n" );
    fprintf( fid, " | Variables table: %3d |\n", nVars );
    fprintf( fid, " ------------------------\n" );
    fprintf( fid, " |    id |         name |\n" );
    fprintf( fid, " ------------------------\n" );
    for ( int i=0; i<nVars; i++ )
    {
      fprintf( fid, " | %5.5d | %12s |\n", i, Vars[i] );
    }
    fprintf( fid, " ------------------------\n" );
    fprintf( fid, "\n\n" );
    fprintf( fid, " ------------------------\n" );
    fprintf( fid, " | Oprations table: %3d |\n", nFcns );
    fprintf( fid, " ------------------------\n" );
    fprintf( fid, " |    id |         name |\n" );
    fprintf( fid, " ------------------------\n" );
    for ( int i=0; i<nFcns; i++ )
    {
      fprintf( fid, " | %5.5d | %12s |\n", i, Fcns[i] );
    }
    fprintf( fid, " ------------------------\n" );
    fprintf( fid, "\n\n" );
    fprintf( fid, " ------------------------\n" );
    fprintf( fid, " | Constants table: %3d |\n", MEPdim.NumConstants );
    fprintf( fid, " ------------------------\n" );
    fprintf( fid, " |    id |        value |\n" );
    fprintf( fid, " ------------------------\n" );
    for ( int i=0; i<MEPdim.NumConstants; i++ )
    {
      fprintf( fid, " | %5.5d | %+12.5f |\n", i, chromosome.constants[i] );
    }
    fprintf( fid, " ------------------------\n" );
    fprintf( fid, "\n\n" );
    fprintf( fid, " -------------------------------------\n" );
    fprintf( fid, " |            MEP Table              |\n" );
    fprintf( fid, " ------------------------------------- \n" );
    fprintf( fid, " |   line |    op. |  addr1 |  addr2 | \n" );
    fprintf( fid, " ------------------------------------- \n" );
    int cnt;
    for ( cnt=0; cnt<MEPdim.NumNodes; cnt++ ) 
    {
      fprintf( fid, " | %+5.5d | %+5.5d | %+5.5d | %+5.5d |\n", cnt, chromosome.code[cnt].op, chromosome.code[cnt].addr1, chromosome.code[cnt].addr2 );
    }

    fprintf( fid, " ------------------------------------- \n" );
    fclose( fid );

    /* Free memory */
    free( chromosome.code );
    free( chromosome.constants );

  }

  for ( int i=0; i<nFcns; i++ ) {
    free( Fcns[i] );
  }
  free( Fcns );


  for ( int i=0; i<nVars; i++ ) {
    free( Vars[i] );
  }
  free( Vars );

  return 0;

}

