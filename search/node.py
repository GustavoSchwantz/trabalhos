class Node:
    """This class represent one node in the graph search."""
    def __init__ (self, state, actionSeq = [], pathCost = 0):
        self.state = state
        self.actionSeq = actionSeq
        self.pathCost = pathCost

    def getState (self):
        return self.state

    def getActionSeq (self):
        return self.actionSeq 

    def getPathCost (self):
        return self.pathCost