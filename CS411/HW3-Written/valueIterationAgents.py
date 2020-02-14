# valueIterationAgents.py
# -----------------------
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


import mdp, util

from learningAgents import ValueEstimationAgent

class ValueIterationAgent(ValueEstimationAgent):
    """
        * Please read learningAgents.py before reading this.*

        A ValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs value iteration
        for a given number of iterations using the supplied
        discount factor.
    """
    def __init__(self, mdp, discount = 0.9, iterations = 100):
        """
          Your value iteration agent should take an mdp on
          construction, run the indicated number of iterations
          and then act according to the resulting policy.

          Some useful mdp methods you will use:
              mdp.getStates()
              mdp.getPossibleActions(state)
              mdp.getTransitionStatesAndProbs(state, action)
              mdp.getReward(state, action, nextState)
              mdp.isTerminal(state)
        """
        self.mdp = mdp
        self.discount = discount
        self.iterations = iterations
        self.values = util.Counter() # A Counter is a dict with default 0

        # Write value iteration code here
        "*** YOUR CODE HERE ***"
        for i in range(self.iterations):
            tempDict = self.values.copy() #use a temp dictionary so as to not update values in the middle of an iteration
            for currState in self.mdp.getStates():
                possibleActions = self.mdp.getPossibleActions(currState) #list of possible actions for state currState. We now have state & action
                reward = 0
                maxReward = -999999999999
                for action in possibleActions:
                    transitionStates = self.mdp.getTransitionStatesAndProbs(currState, action)
                    for (transState, prob) in transitionStates:
                        if(self.mdp.isTerminal(transState)):
                            reward = self.mdp.getReward(currState, action, transState)
                        else:
                            reward += self.values[transState]*prob*discount #sum the reward for each value
                    if(reward > maxReward): #at the end of the loop, if this reward is the biggest given all possible actions, set it as max reward
                        maxReward = reward                                                                                                                                                
                    reward = 0
                if(maxReward != -999999999999):                                                                                                                                       
                    tempDict[currState] = maxReward #this should never actually be -9999999999999999999999999
            self.values = tempDict


    def getValue(self, state):
        """
          Return the value of the state (computed in __init__).
        """
        return self.values[state]


    def computeQValueFromValues(self, state, action):
        transitionStates = self.mdp.getTransitionStatesAndProbs(state, action)
        QValue = 0
        for (singleState, prob) in transitionStates:
            if(self.mdp.isTerminal(singleState)): #if we're terminal, get reward
                return self.mdp.getReward(state, action, singleState)
            QValue += self.values[singleState]*prob*self.discount
        return QValue

    
    def computeActionFromValues(self, state):
        """
          The policy is the best action in the given state
          according to the values currently stored in self.values.

          You may break ties any way you see fit.  Note that if
          there are no legal actions, which is the case at the
          terminal state, you should return None.
        """
        "*** YOUR CODE HERE ***"

        if not self.mdp.getPossibleActions(state): #if there are no legal actions, return None
            return None
        max_val = self.values[state] #gets you the optimal value from the state
        for action in self.mdp.getPossibleActions(state): #for every possible action from that state...
            if(self.computeQValueFromValues(state, action) <= max_val+.001 and self.computeQValueFromValues(state, action) >= max_val-.001):
                return action

    def getPolicy(self, state):
        return self.computeActionFromValues(state)

    def getAction(self, state):
        "Returns the policy at the state (no exploration)."
        return self.computeActionFromValues(state)

    def getQValue(self, state, action):
        return self.computeQValueFromValues(state, action)
