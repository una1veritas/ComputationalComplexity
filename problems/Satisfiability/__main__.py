import sys
import random
from probinst import BooleanFormula

#引数には python の論理式として書かれた論理関数
f = BooleanFormula(sys.argv[1])
print('BooleanFormula'+str(f.variables)+' = \n   '+str(f.formula))

bassign = { }
for bvar in f.variables:
    bassign[bvar] = (random.getrandbits(1) == 1)

print('assignment = ' + str(bassign))
if f.evaluate(bassign) :
    print(True)
else:
    print(False)
