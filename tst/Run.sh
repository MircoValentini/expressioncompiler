#!/bin/bash

EXE=../bin/ec.x
DOT="dot -Tps"
OUTDIR=.

rm -f *.dot
rm -f *.ps
rm -f *.pdf

${EXE} -e "-56*34+75*x+y^2-z^5*sin(45/43)^tan(t)+tanh(x)*cosh(y^46)+sinh(z)" -r "x:p:y:q:z:r:t" -o "sum:sub:div:mul:pow:sin:cos:tan:sinh:cosh:tanh:exp:log"  -v 2

for i in `ls *.dot` ; do
  ${DOT} ${i} -o ${i%.dot}.ps
  convert ${i%.dot}.ps ${i%.dot}.pdf
done

