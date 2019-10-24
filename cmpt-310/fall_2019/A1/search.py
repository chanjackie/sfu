# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
#
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).

#####################################################
#####################################################
# Please enter the number of hours you spent on this
# assignment here
"""
num_hours_i_spent_on_this_assignment = 24
"""
#
#####################################################
#####################################################

#####################################################
#####################################################
# Give one short piece of feedback about the course so far. What
# have you found most interesting? Is there a topic that you had trouble
# understanding? Are there any changes that could improve the value of the
# course to you? (We will anonymize these before reading them.)
"""
Love the usage of PacMan to demonstrate searching algorithms, as it provides a visual representation of our implementation
in a familiar environment. Look forward to implementing machine learning in an assignment

"""
#####################################################
#####################################################

"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def depthFirstSearch(problem):
    """
    Q1.1
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print ( problem.getStartState() )
    You will get (5,5)

    print (problem.isGoalState(problem.getStartState()) )
    You will get True

    print ( problem.getSuccessors(problem.getStartState()) )
    You will get [((x1,y1),'South',1),((x2,y2),'West',1)]
    """
    "*** YOUR CODE HERE ***"
    fringe = util.Stack()
    childParentDict = {}
    explored = []
    actionsArray = []
    startStateTuple = (problem.getStartState(), '', 0)
    fringe.push(startStateTuple)
    while not fringe.isEmpty():
        node = fringe.pop()
        if (problem.isGoalState(node[0])):
            # print("Found the goal!")
            while (node[0] != problem.getStartState()):
                actionsArray.insert(0, node[1])
                node = childParentDict[node]
            break
        if (node[0] in explored):
            continue
        else:
            explored.append(node[0])
        for i in problem.getSuccessors(node[0]):
            if (i[0] in explored):
                continue
            fringe.push(i)
            childParentDict[i] = node
    return actionsArray


def breadthFirstSearch(problem):
    """
    Q1.2
    Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"
    fringe = util.Queue()
    childParentDict = {}
    explored = []
    actionsArray = []
    startStateTuple = (problem.getStartState(), '', 0)
    fringe.push(startStateTuple)
    while not fringe.isEmpty():
        node = fringe.pop()
        if (problem.isGoalState(node[0])):
            # print("Found the goal!")
            while (node[0] != problem.getStartState()):
                actionsArray.insert(0, node[1])
                node = childParentDict[node]
            break
        if (node[0] in explored):
            continue
        else:
            explored.append(node[0])
        for i in problem.getSuccessors(node[0]):
            if (i[0] in explored):
                continue
            fringe.push(i)
            childParentDict[i] = node
    return actionsArray


def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """
    Q1.3
    Search the node that has the lowest combined cost and heuristic first."""
    """Call heuristic(s,problem) to get h(s) value."""
    "*** YOUR CODE HERE ***"
    fringe = util.PriorityQueue()
    childParentDict = {}
    explored = []
    actionsArray = []
    startStateTuple = (problem.getStartState(), '', 0)
    fringe.push(startStateTuple, 0)
    while not fringe.isEmpty():
        node = fringe.pop()
        if (problem.isGoalState(node[0])):
            # print("Found the goal!")
            # printDataStruct(fringe)
            while (node[0] != problem.getStartState()):
                actionsArray.insert(0, node[1])
                node = childParentDict[node]
            break
        if (node[0] in explored):
            continue
        else:
            explored.append(node[0])
        for i in problem.getSuccessors(node[0]):
            if (i[0] in explored):
                continue
            newNode = (i[0], i[1], i[2]+node[2])
            cost = heuristic(i[0], problem) + newNode[2]
            fringe.update(newNode, cost)
            childParentDict[newNode] = node
    return actionsArray

def printDataStruct(struct):
    import copy
    newStruct = copy.deepcopy(struct)
    print("----PRINTING FRINGE----")
    while not newStruct.isEmpty():
        print(newStruct.pop())

def calcDirection(child, parent):
    from game import Directions
    n = Directions.NORTH
    s = Directions.SOUTH
    w = Directions.WEST
    e = Directions.EAST
    if (child[0] - parent[0] == -1):
        return w
    elif (child[0] - parent[0] == 1):
        return e
    elif (child[1] - parent[1] == -1):
        return s
    else:
        return n

# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
