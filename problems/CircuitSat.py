import sys
import random
#from probinstance import CNFFormula

class BooleanCircuit():
    def __init__(self, bc_str):
        self.inputs = []
        self.circuit = dict()
        gateseq = eval(bc_str)
        for i in range(0,len(gateseq)):
            if isinstance(gateseq[i],int) :
                self.inputs.append(i)
            else:
                self.circuit[i] = gateseq[i]
    
    def evaluate(self, assign):
        gatevals = assign
        for (i, pair) in self.circuit.items():
            print(str(i)+str(pair))
            if  not ((gatevals[pair[0]] == 1) and (gatevals[pair[1]] == 1)) :
                gatevals[i] = 1
            else:
                gatevals[i] = 0
        print(gatevals)
        return gatevals[len(gatevals)-1]
        
    def __str__(self):
        return str(self.inputs) + ': ' + str(self.circuit)

#引数には python の論理式として書かれた3-CNF 論理式
for argval in sys.argv[1:] :
    if argval[0] != '-' :
        cc = BooleanCircuit(argval)

print('Boolean Circuit '+str(cc))

if 'deterministic' in sys.argv[1:]:
    bassign = { }
    for bvar in cc.inputs:
        bassign[bvar] = False
    while (True):
        print(str(sorted([assoc for assoc in bassign.items()])), end='')
        if cc.evaluate(bassign) :
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
    assign = dict()
    for ig in cc.inputs:
        assign[ig] = random.getrandbits(1)
    print('assignment = ' + str(assign))
    print(cc.evaluate(assign))
    
'''
python CircuitSat.py "[0,1,2,3,4,(2,3),(2,2),(4,6),(5,7)]"
'''