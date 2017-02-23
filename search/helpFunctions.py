"""Methods for use in the search algorithms."""

def isNotInClosed (state, closed):
    """Return true only if "state" is not in "closed"."""
    for s in closed:
        if s == state:
            return False
    return True        

def expand (node, problem):
    """Return all nodes that result from expansion of "node"."""
    from node import *
    nodes = []
    for triple in problem.getSuccessors (node.getState ()):
        nodes.append (Node (triple[0], node.getActionSeq () + [triple[1]],
            node.getPathCost () + triple[2]))
    return nodes

def insertAll (nodes, fringe):
    """Just insert a set of nodes in the "fringe" data structure."""
    for node in nodes:
        fringe.push (node, node.getPathCost ())
    return fringe    