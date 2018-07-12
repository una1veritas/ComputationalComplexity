import sys
import random
#from probinstance import CNFFormula

class BooleanCircuit():
    def __init__(self, cstr):
        self.gateseq = eval(cstr)
        self.inputs = sorted([gate for gate in self.gateseq if isinstance(gate, int) ])
    
    def evaluate(self, bits):
        gatevals = [False, True]
        for gi in range(2, len(self.gateseq)):
            if gi in self.inputs :
                if isinstance(bits[gi],bool) :
                    gatevals[gi] = bits[gi]
                else:
                    gatevals[gi] = (int(bits[gi]) != 0)
            else:
                t_gate = self.gateseq[gi]
                gatevals[gi] = not (gatevals[t_gate[0]] and gatevals[t_gate[1]])
        print(gatevals)
        return gatevals[-1]
        
    def __str__(self):
        return str(self.inputs) + ': ' + str(self.gateseq)

#引数には python の論理式として書かれた3-CNF 論理式
for argval in sys.argv[1:] :
    if argval[0] != '-' :
        cc = BooleanCircuit(argval)

print('Boolean Circuit '+str(cc))

if 'deterministic' in sys.argv[1:]:
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
    bits = [i for i in range(0,len(cc.gateseq))]
    for i in cc.inputs:
        bits[i] = random.getrandbits(1)
    print('assignment = ' + str(bits))
    print(cc.evaluate(bits))
    
'''
python CircuitSat.py "[0,1,2,3,4,(2,3),(2,2),(4,6),(5,7)]"
'''