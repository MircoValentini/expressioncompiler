.PHONY: clean, view, dview, viewParser

DOT=dot -Tps
LEX=flex
YACC=bison
PROG=ec
FC=gfortran -c
FL=gfortran
CL=gcc
CC=gcc -c -g -O0
LIBS=-ly -ll -lfl -lm
LIBMATH=-lm
MV=mv
ECHO=echo
VIEW=evince

# Directories
BINDIR=./bin
SRCDIR=./src
INCDIR=./inc
OBJDIR=./obj
OUTDIR=./out
PARSEDIR=$(SRCDIR)/parser
LEXERDIR=$(SRCDIR)/lexer

OBJECTS= \
$(OBJDIR)/Main.o \
$(OBJDIR)/FrontEnd.o \
$(OBJDIR)/SymbolTable.o \
$(OBJDIR)/AstBuild.o \
$(OBJDIR)/AstEval.o \
$(OBJDIR)/AstUtils.o \
$(OBJDIR)/Parser.o \
$(OBJDIR)/Lexer.o \
$(OBJDIR)/Intrinsics.o \
$(OBJDIR)/AstMEP_BackEnd.o \
$(OBJDIR)/ExpressionCompiler.o


CCFLAGS=-I$(INCDIR) -g3 -O0



#
# Main program rules
#
$(BINDIR)/$(PROG).x: $(OBJECTS)
	@$(ECHO) "   \e[34mCL \e[39m $(notdir $^) -o $(notdir $@)"
	@$(CL) $^ -o $@ -lm 



#
# Rules
#
$(OBJDIR)/Main.o: $(SRCDIR)/Main.c $(INCDIR)/Main.h $(INCDIR)/ExpressionCompiler.h $(INCDIR)/AstMEP_BackEnd.h $(INCDIR)/FrontEnd.h $(INCDIR)/SymbolTable.h $(INCDIR)/Ast.h $(INCDIR)/Parser.h $(INCDIR)/Lexer.h $(INCDIR)/Intrinsics.h
	@$(ECHO) "   \e[32mCC \e[39m $(notdir $<) -o $(notdir $@)"
	@$(CC) $(CCFLAGS) $< -o $@

$(OBJDIR)/ExpressionCompiler.o: $(SRCDIR)/ExpressionCompiler.c $(INCDIR)/ExpressionCompiler.h $(INCDIR)/FrontEnd.h $(INCDIR)/Utils.h $(INCDIR)/AstMEP_BackEnd.h $(INCDIR)/SymbolTable.h $(INCDIR)/Ast.h $(INCDIR)/Parser.h $(INCDIR)/Lexer.h
	@$(ECHO) "   \e[32mCC \e[39m $(notdir $<) -o $(notdir $@)"
	@$(CC) $(CCFLAGS) $< -o $@


$(OBJDIR)/FrontEnd.o: $(SRCDIR)/FrontEnd.c $(INCDIR)/FrontEnd.h $(INCDIR)/SymbolTable.h $(INCDIR)/Ast.h $(INCDIR)/Parser.h $(INCDIR)/Lexer.h
	@$(ECHO) "   \e[32mCC \e[39m $(notdir $<) -o $(notdir $@)"
	@$(CC) $(CCFLAGS) $< -o $@

$(OBJDIR)/SymbolTable.o: $(SRCDIR)/SymbolTable.c $(INCDIR)/SymbolTable.h
	@$(ECHO) "   \e[32mCC \e[39m $(notdir $<) -o $(notdir $@)"
	@$(CC) $(CCFLAGS) $< -o $@

$(OBJDIR)/AstBuild.o: $(SRCDIR)/AstBuild.c $(INCDIR)/Ast.h $(INCDIR)/AstData.h $(INCDIR)/AstBuild.h $(INCDIR)/AstUtils.h
	@$(ECHO) "   \e[32mCC \e[39m $(notdir $<) -o $(notdir $@)"
	@$(CC) $(CCFLAGS) $< -o $@

$(OBJDIR)/AstEval.o: $(SRCDIR)/AstEval.c $(INCDIR)/Ast.h $(INCDIR)/AstData.h $(INCDIR)/AstBuild.h $(INCDIR)/AstUtils.h
	@$(ECHO) "   \e[32mCC \e[39m $(notdir $<) -o $(notdir $@)"
	@$(CC) $(CCFLAGS) $< -o $@

$(OBJDIR)/AstUtils.o: $(SRCDIR)/AstUtils.c $(INCDIR)/Ast.h $(INCDIR)/AstData.h $(INCDIR)/AstBuild.h $(INCDIR)/AstUtils.h
	@$(ECHO) "   \e[32mCC \e[39m $(notdir $<) -o $(notdir $@)"
	@$(CC) $(CCFLAGS) $< -o $@

$(OBJDIR)/Intrinsics.o: $(SRCDIR)/Intrinsics.c $(INCDIR)/Intrinsics.h $(INCDIR)/SymbolTable.h
	@$(ECHO) "   \e[32mCC \e[39m $(notdir $<) -o $(notdir $@)"
	@$(CC) $(CCFLAGS) $< -o $@

$(OBJDIR)/AstMEP_BackEnd.o: $(SRCDIR)/AstMEP_BackEnd.c $(INCDIR)/AstMEP_BackEnd.h $(INCDIR)/AstData.h
	@$(ECHO) "   \e[32mCC \e[39m $(notdir $<) -o $(notdir $@)"
	@$(CC) $(CCFLAGS) $< -o $@

$(OBJDIR)/Parser.o: $(SRCDIR)/Parser.c $(INCDIR)/Parser.h
	@$(ECHO) "   \e[32mCC \e[39m $(notdir $<) -o $(notdir $@)"
	@$(CC) $(CCFLAGS) $< -o $@

$(OBJDIR)/Lexer.o: $(SRCDIR)/Lexer.c $(INCDIR)/Lexer.h
	@$(ECHO) "   \e[32mCC \e[39m $(notdir $<) -o $(notdir $@)"
	@$(CC) $(CCFLAGS) $< -o $@

$(SRCDIR)/Parser.c $(INCDIR)/Parser.h: $(PARSEDIR)/parser.y
	@$(ECHO) " \e[32mYACC \e[39m $(notdir $<) -o $(notdir $@)"
	@$(YACC) -v $< --defines=$(INCDIR)/Parser.h -g -o$(SRCDIR)/Parser.c
	@$(MV) $(SRCDIR)/Parser.dot $(OUTDIR)/Parser.dot
	@$(MV) $(SRCDIR)/Parser.output $(OUTDIR)/Parser.output

$(SRCDIR)/Lexer.c $(INCDIR)/Lexer.h: $(LEXERDIR)/scanner.l
	@$(ECHO) " \e[32mFLEX \e[39m $(notdir $<) -o $(notdir $@)"
	@$(LEX) --debug -o$(SRCDIR)/Lexer.c $<
	@$(MV) -f lexer.h $(INCDIR)/Lexer.h




#
# Abstract syntax tree graph
#
view: $(OUTDIR)/Ast.ps
	@$(VIEW) $< &

$(OUTDIR)/Ast.ps: $(OUTDIR)/Ast.dot
	@$(DOT) $< -o $@


$(OUTDIR)/Ast.dot: $(BINDIR)/$(PROG).x
	./$<


#
# Abstract syntax tree graph
#
dview: $(OUTDIR)/dAst.ps
	@$(VIEW) $< &

$(OUTDIR)/dAst.ps: $(OUTDIR)/dAst.dot
	@$(DOT) $< -o $@


$(OUTDIR)/dAst.dot: $(BINDIR)/$(PROG).x
	./$<


#
# Abstract syntax tree graph
#
viewParser: $(OUTDIR)/Parser.ps
	@$(VIEW) $< &

$(OUTDIR)/Parser.ps: $(OUTDIR)/Parser.dot
	@$(DOT) $< -o $@



#
# Clean the source tree
#
clean:
	rm -f Ast.dot
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/*.x
	rm -f $(SRCDIR)/Parser.c
	rm -f $(SRCDIR)/Lexer.c
	rm -f $(SRCDIR)/Parser.dot
	rm -f $(SRCDIR)/Parser.output
	rm -f $(SRCDIR)/Parser.ps
	rm -f $(OUTDIR)/*.*
	rm -f $(INCDIR)/Parser.h
	rm -f $(INCDIR)/lexer.h


