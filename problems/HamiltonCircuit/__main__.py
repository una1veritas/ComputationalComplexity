import sys
import random
from probinstance import Graph

#引数は頂点のコレクション，辺のコレクション（あるいはその組）
g = Graph(eval(sys.argv[1])[0], eval(sys.argv[1])[1])
print('G = (V = '+str(g.vertices)+', E = '+str(g.edges)+ ' )')
circuit = list(g.vertices)

#非決定的な順列の生成をランダムシャッフルでシミュレーション
random.shuffle(circuit)
print('circuit = '+str(circuit))

print('checking the circuit...')
for i in range(0, len(g.vertices)) :
    j = (i + 1) % len(g.vertices)
    print(str(circuit[i])+' -> '+str(circuit[j])+', ', end='')
    if not g.adjacent(circuit[i], circuit[j]) :
        print('failed.')
        break
    print()
else:
    print('success!')
#prints out success on accept