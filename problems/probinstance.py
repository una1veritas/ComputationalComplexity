'''

Decision problem instance 
class library

Created on 2018/06/20

@author: sin
'''
import ast
        
class Graph():
    '''
    mathematical data structure representing a relation
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

class BooleanFormula():
    def __init__(self,f):
        self.formula = f
        boolvars = set()
        '''python のパーサを使って式から変数だけ取り出す'''
        for node in ast.walk(ast.parse(f)):
            if isinstance(node, ast.Name) :
                boolvars.add(node.id)
        self.variables = tuple(sorted(list(boolvars)))

    def evaluate(self, assign):
        return eval(self.formula, assign)

class CNFFormula():
    def __init__(self,fstr):
        self.clauses = []
        self.variables = set()
        lastlbracepos = -1
        for pos in range(0,len(fstr)):
            if lastlbracepos == -1 and fstr[pos] == '(':
                lastlbracepos = pos
            elif lastlbracepos != -1 and fstr[pos] == '(':
                '''(('''
                lastlbracepos = pos
            elif lastlbracepos != -1 and fstr[pos] == ')':
                t_clause = fstr[lastlbracepos+1:pos].split(',')
                f_clause = [ ]
                for a_literal in t_clause:
                    a_literal = a_literal.strip(' ')
                    self.variables.add(a_literal.replace('~',''))
                    f_clause.append(a_literal)
                self.clauses.append(f_clause)
                lastlbracepos = -1

    def evaluate(self, assign):
        for a_clause in self.clauses:
            clval = False
            for a_literal in a_clause:
                if '~' in a_literal:
                    litval = not assign[a_literal.strip('~')]
                else:
                    litval = assign[a_literal]
                if litval:
                    clval = True
            if not clval:
                return False            
        return True
    
        return eval(self.formula, assign)

    def __str__(self):
        t_str = '('
        t_str= t_str + '{'
        vc = 0
        for v in sorted(list(self.variables)) :
            if vc == 0:
                vc = 1
            else:
                t_str = t_str + ', '
            t_str = t_str + v
        t_str = t_str + '}'
        t_str = t_str + ', ('
        cc = 0
        for c in self.clauses :
            if cc == 0:
                cc = 1
            else:
                t_str = t_str + ', '                
            t_str = t_str + '('
            lc = 0
            for l in c:
                if lc == 0 :
                    lc = 1
                else:
                    t_str = t_str + ', '
                t_str = t_str + l
            t_str = t_str + ')'
        t_str = t_str + ')'
        return t_str
    