import sys
import random

collection = []
for a_set in eval(sys.argv[1]) :
    collection.append(set(a_set))

universe = set()
for a_set in collection:
    universe.update(a_set)
    
print('universe = '+str(universe)+', collection = '+str(collection))
partition = set([e for e in universe if random.randint(0,1) == 1])

print('selected '+str(partition))
for a_set in collection:
    s = [e for e in a_set if e in partition]
    if len(s) == 0 or len(s) == len(a_set) :
        print('splitting failed for '+str(a_set))
        break
else:
    print('success!')
#prints out success on accept
#python3 SetSplit "('t','f'),('x','_x'),('y','_y'),('z','_z'),('x','y','z'),('_x','y','z','f'),('x','_y','z','f')"
#universe = {'f', 'y', 'z', 't', '_y', '_x', 'x', '_z'}, collection = [{'f', 't'}, {'x', '_x'}, {'_y', 'y'}, {'_z', 'z'}, {'x', 'z', 'y'}, {'f', 'z', 'y', '_x'}, {'x', 'f', '_y', 'z'}]
#selected {'x', '_z', 'f', 'y'}
#success!
#
#python3 SetSplit "('t','f'),('x','_x'),('y','_y'),('z','_z'),('x','y','z'),('_x','y','z','f'),('x','_y','z','f')"
#universe = {'y', 'z', '_y', 'x', '_x', 't', 'f', '_z'}, collection = [{'t', 'f'}, {'x', '_x'}, {'y', '_y'}, {'z', '_z'}, {'x', 'y', 'z'}, {'y', 'f', 'z', '_x'}, {'x', '_y', 'f', 'z'}]
#selected {'_y', 'x', 'z', 't'}
#success!