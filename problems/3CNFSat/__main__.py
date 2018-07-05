import sys
import random
from probinstance import CNFFormula

#引数には python の論理式として書かれた3-CNF 論理式
f = CNFFormula(sys.argv[1])

print('3-CNF Formula'+str(f))

bassign = { }
for bvar in f.variables:
    bassign[bvar] = (random.getrandbits(1) == 1)

print('assignment = ' + str(bassign))
print(f.evaluate(bassign))