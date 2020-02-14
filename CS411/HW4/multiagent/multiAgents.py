# multiAgents.py
# --------------
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


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
      A reflex agent chooses an action at each choice point by examining
      its alternatives via a state evaluation function.

      The code below is provided as a guide.  You are welcome to change
      it in any way you see fit, so long as you don't touch our method
      headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {North, South, West, East, Stop}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]
        newGhostDistances = successorGameState.getGhostPositions()

        #stops do basically nothing for us and suck, so we are penalizing stop action
        if action == 'Stop':
              return -1000

        #for ghost
        sum = 0
        index = 0
        manhattanDist = [util.manhattanDistance(newPos, ghost) for ghost in newGhostDistances]
        for ghostPos in newGhostDistances:
            for ghostState in newGhostStates:
                #ghost is not scared, behave normally
                if(ghostState.scaredTimer > -0.00001 and ghostState.scaredTimer < 0.00001):
                    temp = util.manhattanDistance(newPos, successorGameState.getGhostPosition(index+1))
                    if(temp <= 1): #if the ghost is really close and not scared, do anything to avoid it
                        temp = -1000
                    # sum += temp*.8 #dont worry about the ghost too much
                    sum += temp #dont worry about the ghost too much
                #ghost is scared, pretend it's a reasonable distance away
                else:
                    sum += 5
                index += 1

        #for food
        foodStates = successorGameState.getFood()
        closestFood = 99999

        #for each food that is left, find the closest food
        #if that food is close, we reward. the farther it is, the smaller the reward
        for food in foodStates.asList():
              if util.manhattanDistance(newPos, food) < closestFood:
                    closestFood = util.manhattanDistance(newPos, food)
                    # print(newPos, food, closestFood)
        invertReward = 200 * 1/float(closestFood) #the closer it is, the larger the reward
        sum += invertReward

        #if we would end up eating a food, we REALLY want to go there vs going somewhere without food
        if (currentGameState.getNumFood() > successorGameState.getNumFood()):
              sum += 100


        "*** YOUR CODE HERE ***"
        return sum + successorGameState.getScore()  # always grab food, unless near a ghost

def scoreEvaluationFunction(currentGameState):
    """
      This default evaluation function just returns the score of the state.
      The score is the same one displayed in the Pacman GUI.

      This evaluation function is meant for use with adversarial search agents
      (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
      This class provides some common elements to all of your
      multi-agent searchers.  Any methods defined here will be available
      to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

      You *do not* need to make any changes here, but you can if you want to
      add functionality to all your adversarial search agents.  Please do not
      remove anything, however.

      Note: this is an abstract class: one that should not be instantiated.  It's
      only partially specified, and designed to be extended.  Agent (game.py)
      is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
      Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
          Returns the minimax action from the current gameState using self.depth
          and self.evaluationFunction.

          Here are some method calls that might be useful when implementing minimax.

          gameState.getLegalActions(agentIndex):
            Returns a list of legal actions for an agent
            agentIndex=0 means Pacman, ghosts are >= 1

          gameState.generateSuccessor(agentIndex, action):
            Returns the successor game state after an agent takes an action

          gameState.getNumAgents():
            Returns the total number of agents in the game
        """
        "*** YOUR CODE HERE ***"
        numGhosts = gameState.getNumAgents() - 1  # num ghosts = total agents - pacman

        # #we start at agentindex =0, depth = 0
        def get_value(currentAgent, depth, gameState):
            actions = gameState.getLegalActions(currentAgent)  # get the list of possible actions

            # if there are no possible moves, we are at a terminal state
            if len(actions) == 0:
                return (' ', scoreEvaluationFunction(currentGameState=gameState))

            if depth == 0:
                return (' ', scoreEvaluationFunction(currentGameState=gameState))

            # WE ARE PACMAN
            if currentAgent == 0:
                v = -999999  # initialize to '-infinity'
                bestAction = actions[0]
                for action in actions:
                    new_state = gameState.generateSuccessor(currentAgent, action)
                    temp = get_value(currentAgent + 1, depth, new_state)
                    if (temp[1] > v):
                        v = temp[1]
                        bestAction = action
                    # v = max(v, get_value(currentAgent+1, depth, new_state))
                return (bestAction, v)  # v

            # WE ARE GHOST
            else:
                v = 999999  # initialize to 'infinity'
                bestAction = actions[0]
                if currentAgent == numGhosts:
                    for action in actions:
                        new_state = gameState.generateSuccessor(currentAgent, action)
                        temp = get_value(0, depth - 1, new_state)
                        # v = min(v, get_value(0, depth-1, new_state))
                        if (temp[1] < v):
                            v = temp[1]
                            bestAction = action
                    return (bestAction, v)  # v

                # if we arent last ghost, do as normal
                for action in actions:
                    new_state = gameState.generateSuccessor(currentAgent, action)
                    temp = get_value(currentAgent + 1, depth, new_state)
                    if (temp[1] < v):
                        v = temp[1]
                        bestAction = action
                    # v = min(v, get_value(currentAgent+1, depth, new_state))
                return (bestAction, v)  # v

        # WE NEED TO RETURN THE ACTION, NOT THE VALUE
        return (get_value(self.index, self.depth, gameState))[0]


class AlphaBetaAgent(MultiAgentSearchAgent):
    """
      Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
          Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        numGhosts = gameState.getNumAgents() - 1 #num ghosts = total agents - pacman

        # #we start at agentindex =0, depth = 0
        def get_value(currentAgent, depth, gameState, alpha, beta):
            actions = gameState.getLegalActions(currentAgent)  # get the list of possible actions

            # if there are no possible moves, we are at a terminal state
            if len(actions) == 0:
                return (' ', scoreEvaluationFunction(currentGameState=gameState))

            if depth == 0:
                return (' ', scoreEvaluationFunction(currentGameState=gameState))

            # WE ARE PACMAN
            if currentAgent == 0:
                v = -999999  # initialize to '-infinity'
                bestAction = actions[0]
                newAlpha = alpha
                for action in actions:
                    new_state = gameState.generateSuccessor(currentAgent, action)
                    temp = get_value(currentAgent + 1, depth, new_state, newAlpha, beta)
                    if (temp[1] > v):
                        v = temp[1]
                        bestAction = action
                    if v > beta:
                        return (bestAction, v)
                    newAlpha = max(newAlpha, v)
                    # v = max(v, get_value(currentAgent+1, depth, new_state))
                return (bestAction, v)  # v

            # WE ARE GHOST
            else:
                v = 999999  # initialize to 'infinity'
                bestAction = actions[0]
                newBeta = beta
                if currentAgent == numGhosts:
                    for action in actions:
                        new_state = gameState.generateSuccessor(currentAgent, action)
                        temp = get_value(0, depth - 1, new_state, alpha, newBeta)
                        # v = min(v, get_value(0, depth-1, new_state))
                        if (temp[1] < v):
                            v = temp[1]
                            bestAction = action
                        if v < alpha:
                            return (bestAction, v)
                        newBeta = min(newBeta, v)

                    return (bestAction, v)  # v

                # if we arent last ghost, do as normal
                for action in actions:
                    new_state = gameState.generateSuccessor(currentAgent, action)
                    temp = get_value(currentAgent + 1, depth, new_state, alpha, newBeta)
                    if (temp[1] < v):
                        v = temp[1]
                        bestAction = action
                    if v < alpha:
                        return (bestAction, v)
                    newBeta = min(newBeta, v)
                    # v = min(v, get_value(currentAgent+1, depth, new_state))
                return (bestAction, v)  # v

        # WE NEED TO RETURN THE ACTION, NOT THE VALUE
        alpha = -999999
        beta = 999999
        return (get_value(self.index, self.depth, gameState, alpha, beta))[0]

        #util.raiseNotDefined()

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
          Returns the expectimax action using self.depth and self.evaluationFunction

          All ghosts should be modeled as choosing uniformly at random from their
          legal moves.
        """
        "*** YOUR CODE HERE ***"
        util.raiseNotDefined()

def betterEvaluationFunction(currentGameState):
    """
      Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
      evaluation function (question 5).

      DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

# Abbreviation
better = betterEvaluationFunction

'''

'''