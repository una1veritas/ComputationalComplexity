import sys
sys.path.append('/Users/sin/Documents/Projects/ComputationalComplexity/problems')
import random
import datastructures

#引数にはコンマで区切った（tuple として解釈される）頂点の列，辺の列，
#あるいは set, tuple, list 形式での頂点の集合，辺の集合 
g = graph(eval(sys.argv[1]), eval(sys.argv[2]))
k = int(eval(sys.argv[3]))
print('G = (V = '+str(g.vertices)+', E = '+str(g.edges)+ ' )')
print('colors = '+str(k))

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