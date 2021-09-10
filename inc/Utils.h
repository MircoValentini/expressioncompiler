#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include "Cfg.h"


/* Some useful functions to debug the software */
#if  defined(__DEBUG_ENTER_FCN__)
#if __DEBUG_ENTER_FCN__==1
#define __enter_function__( ) \
printf( "\n\e[32mDEBUG ENTER  \e[39m:: \e[32mfile:\e[39m%20.20s, \e[32mline:\e[39m%5d, \e[32mfunction name:\e[39m%30.30s\n", __FILE__, __LINE__, __func__ );
#else
#define __enter_function__( )
#endif
#else 
#define __enter_function__( )
#endif



#if  defined(__DEBUG_EXIT_FCN__)
#if __DEBUG_EXIT_FCN__==1
#define __exit_function__( ) \
printf( "\e[31mDEBUG EXIT  \e[39m :: \e[31mfile:\e[39m%20.20s, \e[31mline:\e[39m%5d, \e[31mfunction name:\e[39m%30.30s\n\n", __FILE__, __LINE__, __func__ );
#else
#define __exit_function__( )
#endif
#else 
#define __exit_function__( )
#endif


#if  defined(__DEBUG_ASSERT_FCN__)
#if __DEBUG_ASSERT_FCN__==1
#define __assert__( COND, MSG ) \
IF ( COND == 1 ) printf( "\tDEBUG ASSERT  :: file:%s, line:%d, function name:%s :: %s \n", __FILE__, __LINE__, __func__, MSG );
#else
#define __assert__( COND, MSG )
#endif
#else 
#define __assert__( COND, MSG )
#endif


#if  defined(__DEBUG_COND_PRINT_FCN__)
#if __DEBUG_COND_PRINT_FCN__==1
#define __debug_cond_printf__( COND, ... ) \
if ( COND==1 ) { printf( "\tDEBUG COND PRINT  :: file:%s, line:%d, function name:%s   ", __FILE__, __LINE__, __func__ ); printf( __VA_ARGS__ ); };
#else
#define __debug_cond_printf__( COND, ... )
#endif
#else 
#define __debug_cond_printf__( COND, ... )
#endif


#if  defined(__DEBUG_PRINT_FCN__)
#if __DEBUG_PRINT_FCN__==1
#define __debug_printf__( ... ) \
printf( "\t\e[34mDEBUG PRINT \e[39m :: \e[34mfile:\e[39m%20.20s, \e[34mline:\e[39m%5d, \e[34mfunction name:\e[39m%30.30s \e[39m\e[34m->\e[39m ", __FILE__, __LINE__, __func__ ); printf( __VA_ARGS__ );
#else
#define __debug_printf__( ... )
#endif
#else 
#define __debug_printf__( ... )
#endif

#endif /* __UTILS_H__ */


