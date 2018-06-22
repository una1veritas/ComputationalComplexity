import sys
import random
from probinstance import Graph

#引数はコンマで区切りの（tuple として解釈される）頂点の列，と辺の列の組
#あるいは set, tuple, list 形式での頂点の集合，辺の集合 
if len(sys.argv) == 4 :
    v = eval(sys.argv[1])
    e = eval(sys.argv[2])
    k = eval(sys.argv[3])
else:
    (v, e) = eval(sys.argv[1])
    k = eval(sys.argv[2])
g = Graph(v, e)
print('G = (V = '+str(g.vertices)+', E = '+str(g.edges)+ ' )')
print('independent set no less than = '+str(k))

#非決定的な独立点集合の選択をランダムでシミュレーション
vsub = set()
for v in g.vertices:
    if random.randint(0,1) == 1 :
        vsub.add(v)
print('subset = '+str(vsub))

print('verifying...')
induced = g.inducedEdges(vsub)
if len(vsub) >= k and len(induced) == 0 :
    print('success!')
elif len(vsub) < k:
    print('failed, subset is no more than '+str(k - 1))
else:
    print('failed, adjacent in '+str(induced))
