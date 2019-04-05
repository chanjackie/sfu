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
num_hours_i_spent_on_this_assignment = 0
#####################################################
#####################################################

#####################################################
#####################################################
# Give one short piece of feedback about the course so far. What
# have you found most interesting? Is there a topic that you had trouble
# understanding? Are there any changes that could improve the value of the
# course to you? (We will anonymize these before reading them.)
"""
<Your feedback goes here>

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

def depthFirstSearch(problem, visited = [], initialState = None, path = []):
    """
    Questoin 1.1
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print ( problem.getStartState() )
    print (problem.isGoalState(problem.getStartState()) )
    print ( problem.getSuccessors(problem.getStartState()) )

    """
    "*** YOUR CODE HERE ***"
    from util import Stack
    if (problem.isGoalState(problem.getStartState()) == True):
        return []
    if (initialState == None):
        startState = problem.getStartState()
    else:
        startState = initialState
    visited.append(startState)
    successors = problem.getSuccessors(startState)
    candidates = Stack()
    for i in successors:
        candidates.push(i)
    while (not candidates.isEmpty()):
        nextState = candidates.pop()
        if (problem.isGoalState(nextState[0])):
            print("FOUND GOAL")
            path.append(nextState[1])
            return path
        if (not (nextState[0] in visited)):
            if (depthFirstSearch(problem, visited, nextState[0], path) != []):
                path.insert(0, nextState[1])
                if (startState == problem.getStartState()):
                    try:
                        while (not problem.allCornersReached()):
                            problem.updateStartState(problem.getLastCornerReached())
                            result = depthFirstSearch(problem, [], None, [])
                            for i in result:
                                path.append(i)
                    except AttributeError:
                        pass
                return path
    return path


def breadthFirstSearch(problem, visited = [], initialState = None, path = [], candidates = None):
    """Questoin 1.2
     Search the shallowest nodes in the search tree first.
     """
    "*** YOUR CODE HERE ***"
    from util import Queue
    if (problem.isGoalState(problem.getStartState()) == True):
        return []
    if (initialState == None):
        startState = problem.getStartState()
    else:
        startState = initialState
    visited.append(startState)
    successors = problem.getSuccessors(startState)
    if (candidates == None):
        candidates = Queue()
    for i in successors:
        candidates.push(i)
    while (not candidates.isEmpty()):
        nextState = candidates.pop()
        if (problem.isGoalState(nextState[0])):
            print("FOUND GOAL: " + str(nextState[0]))
            path.append(nextState[1])
            return nextState
        if (not (nextState[0] in visited)):
            result = breadthFirstSearch(problem, visited, nextState[0], path, candidates)
            if (result != []):
                if (calcCoord(getOppositeDirection(result[1]), result[0]) == nextState[0]):
                    path.insert(0, nextState[1])
                    if (not startState == problem.getStartState()):
                        return nextState
                if (startState == problem.getStartState()):
                    try:
                        while (not problem.allCornersReached()):
                            problem.updateStartState(problem.getLastCornerReached())
                            result = breadthFirstSearch(problem, [], None, [], None)
                            for i in result:
                                path.append(i)
                    except AttributeError:
                        pass
                    return path
                return result
    if (startState == problem.getStartState()):
        return path
    return result


def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic, initialState = None,
                path = [], candidates = None, cost = {}, visited = []):
    """Question 1.3
    Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"
    from util import PriorityQueue
    if (problem.isGoalState(problem.getStartState()) == True):
        return []
    if (initialState == None):
        startState = problem.getStartState()
        cost[startState] = 0
    else:
        startState = initialState
    visited.append(startState)
    successors = problem.getSuccessors(startState)
    if (candidates == None):
        candidates = PriorityQueue()
    for i in successors:
        if (i[0] in cost):
            cost[i[0]] += 1
        else:
            cost[i[0]] = cost[startState] + 1
        fscore = cost[i[0]] + heuristic(i[0], problem)
        candidates.update(i, fscore)
    while (not candidates.isEmpty()):
        nextState = candidates.pop()
        if (problem.isGoalState(nextState[0])):
            print("FOUND GOAL")
            path.append(nextState[1])
            return nextState
        if (nextState[0] not in visited):
            result = aStarSearch(problem, heuristic, nextState[0], path, candidates, cost, visited)
            if (result != []):
                if (calcCoord(getOppositeDirection(result[1]), result[0]) == nextState[0]):
                    path.insert(0, nextState[1])
                    if (not startState == problem.getStartState()):
                        return nextState
                if (startState == problem.getStartState()):
                    try:
                        while (not problem.allCornersReached()):
                            problem.updateStartState(problem.getLastCornerReached())
                            result = aStarSearch(problem, heuristic, None, [], None, {}, [])
                            for i in result:
                                path.append(i)
                    except AttributeError:
                        pass
                    return path
                return result
    if (startState == problem.getStartState()):
        return path
    return result
"""
def isOppositeDirection(dir1, dir2):
    if (dir1 == 'West' and dir2 == 'East'): return True
    if (dir1 == 'East' and dir2 == 'West'): return True
    if (dir1 == 'South' and dir2 == 'North'): return True
    if (dir1 == 'North' and dir2 == 'South'): return True
    return False
"""
def getOppositeDirection(direction):
    if (direction == 'West'): return 'East'
    if (direction == 'East'): return 'West'
    if (direction == 'South'): return 'North'
    if (direction == 'North'): return 'South'

def calcCoord(direction, coord):
    newCoord = None
    if (direction == 'East'):
        newCoord = (int(coord[0])+1, coord[1])
    elif (direction == 'West'):
        newCoord = (int(coord[0])-1, coord[1])
    elif (direction == 'North'):
        newCoord = (int(coord[0]), coord[1]+1)
    elif (direction == 'South'):
        newCoord = (int(coord[0]), coord[1]-1)
    return newCoord

# def getDirectionToState(start, dest):
#     if (start[0]-dest[0] == 1): return 'West'
#     elif (start[0]-dest[0] == -1): return 'East'
#     elif (start[1]-dest[1] == 1): return 'South'
#     elif (start[1]-dest[1] == -1): return 'North'


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
