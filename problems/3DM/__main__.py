import sys
import random

triples = eval(sys.argv[1])
X = set()
Y = set()
Z = set()
for t in triples:
    X.add(t[0])
    Y.add(t[1])
    Z.add(t[2])
    
print(X, Y, Z, triples)
if not (len(X) == len(Y) and len(X) == len(Z)):
    print('All the sets of dimensions must be the same size.')
    exit(1)
    
#非決定的な triples の部分集合 W の生成をランダムシャッフルでシミュレーション
#ただし |W| = |X| = |Y| = |Z|
bits = [ 1 if i < len(X) else 0 for i in range(0,len(triples)) ]
random.shuffle(bits)
W = [ triples[i] for i in range(0,len(triples)) if bits[i] ]

print('subset = '+str(W))
if len(W) != len(X) :
    print('the size of subset W is not correct.')
    exit(1)

WX = set()
WY = set()
WZ = set()
for t in W:
    WX.add(t[0])
    WY.add(t[1])
    WZ.add(t[2])

if len(X) == len(WX) and len(X) == len(WY) and len(X) == len(WZ):
    print('success!')
else:
    print('failed.')
#prints out success on accept