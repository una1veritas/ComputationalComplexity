import sys
import random

collection = []
for a_set in eval(sys.argv[1]) :
    collection.append(set(a_set))

universe = set()
for a_set in collection:
    universe.update(a_set)
    
print('universe = '+str(universe)+', collection = '+str(collection))
#非決定的な大きさ |X| の部分集合の生成をランダムシャッフルでシミュレーション
partition = set([e for e in universe if random.randint(0,1) == 1])

print('selected '+str(partition))
for a_set in collection:
    s = [e for e in a_set if e in partition]
    if len(s) == 0 or len(s) == len(a_set) :
        print('failed for '+str(a_set))
        break
else:
    print('success!')
#prints out success on accept