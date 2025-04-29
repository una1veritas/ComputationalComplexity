'''
Created on 2025/04/27

@author: sin
'''

class TuringMachine:
    INTIAL_STATE = 0
    HALT_STATE = -1
    BLANK_SYMBOL = ' '
    
    def __init__(self):
        self.states = set()
        self.states.add(TuringMachine.INTIAL_STATE)
        self.transition = dict()

    def __str__(self):
        return 'TuringMachine('+ f'states={self.states}'+')'
        
if __name__ == '__main__':
    tm = TuringMachine()
    print(tm)