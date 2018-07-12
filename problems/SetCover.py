import sys
import random

collection = []
for s in eval(sys.argv[1]) :
    collection.append(set(s))

universe = set()
for c in collection:
    universe.update(c)
    
print('universe = '+str(universe)+', collection = '+str(collection))
#非決定的な大きさ |X| の部分集合の生成をランダムシャッフルでシミュレーション
cover = [c for c in collection if random.randint(0,1) == 1]

print('selected '+str(cover))
u = set()
for c in cover:
    u.update(c)
if len(u) == len(universe):
    print('success!')
else:
    print('failed.')
#prints out success on accept