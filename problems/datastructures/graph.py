'''
Created on 2018/06/20

@author: sin
'''
        
class graph():
    '''
    datastructures data structure
    '''
    def __init__(self,v,e):
        self.vertices = set(v)
        self.edges = set()
        for u, v in e:
            if u != v : #rejects self loop
                edge = (u,v) if u < v else (v,u)
                self.edges.add(edge)

    def adjacent(self, u, v):
        if u < v :
            return (u,v) in self.edges
        else:
            return (v,u) in self.edges
    
    def inducedEdges(self, vsub):
        iedges = set()
        for u, v in self.edges:
            if u in vsub and v in vsub:
                iedges.add( (u,v) )
        return iedges
