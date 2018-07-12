import sys
import random
from probinstance import CNFFormula

#引数には python の論理式として書かれた3-CNF 論理式
for argval in sys.argv[1:] :
    if argval[0] != '-' :
        f = CNFFormula(argval)
        break

print('3-CNF Formula'+str(f))

if '-deterministic' in sys.argv[1:]:
    bassign = { }
    for bvar in f.variables:
        bassign[bvar] = False
    while (True):
        print(str(sorted([assoc for assoc in bassign.items()])), end='')
        if f.evaluate(bassign) :
            print(' -> satisfied.')
        else:
            print(' -> not satisfied.')
        if not (False in bassign.values()):
            break
        for var in sorted(list(bassign.keys())):
            if not bassign[var] :
                bassign[var] = True
                break
            bassign[var] = False
else:
    bassign = { }
    for bvar in f.variables:
        bassign[bvar] = (random.getrandbits(1) == 1)
    print('assignment = ' + str(sorted([assoc for assoc in bassign.items()])))
    print(f.evaluate(bassign))
    
'''
python CNFSat.py -deterministic "((x,z,w),(x,z,~w),(y,z,w),(y,z,~w),(~x,~y,~z))"
'''