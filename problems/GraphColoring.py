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
print('threshold for colors = '+str(k))

#非決定的な彩色の生成をランダムでシミュレーション
coloring = dict()
for v in g.vertices:
    coloring[v] = random.randint(0,k)
print('coloring = '+str(coloring))

print('verifying...')
for edge in g.edges :
    if coloring[edge[0]] == coloring[edge[1]] :
        print('failed. '+str(edge))
        break
else:
    print('success!')
#prints out success on accept