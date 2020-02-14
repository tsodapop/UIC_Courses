import numpy as np

#sigmoid and its derivative
def sigmoid(t):
    return 1 / (1 + np.exp(-t))
    
def sigmoid_derivative(p):
    return p * (1 - p)

np.random.seed(100)


class NeuralNetwork:
    def __init__(self,x=[[]],y=[],numLayers=2,numNodes=2,eta=0.1,maxIter=10000):

        self.lr = eta
        self.numLayers = numLayers
        self.numNodes = numNodes
        
        self.weights = [np.random.uniform(-1,1,(x.shape[1],numNodes))] #create the weights from the inputs to the first layer
        
        for i in range(1,numLayers-1):
            self.weights.append(np.random.uniform(-1,1,(numNodes,numNodes))) #create the random weights between internal layers
            
        self.weights.append(np.random.uniform(-1,1,(numNodes,1))) #create weights from final layer to output node
        
        self.outputs = np.zeros(y.shape)    #creates an output array of similar size to y 
        
        self.bias = [np.ones(numNodes)] #create bias nodes to the first layer, all 1's
        for i in range(numLayers-1):    #create bias in btwn hidden layers
            self.bias.append(np.ones(numNodes))
        self.bias.append(np.ones(y.shape))#create bias node to last layer, to output, all 1's        
        
        self.train(learningRate=eta,maxIterations=maxIter) 

    def train(self,learningRate,maxIterations):       
        for i in range(1,maxIterations):
            self.feedforward()
            self.backprop()

    def predict(self,x=[]):
        test.feedforward()
        return self.outputs


    def feedforward(self):
        self.layerdata = []
        
        #this adds in the input layer to the first hidden layer
#         print(x)
#         print(self.weights[0])
        self.to_first_layer = sigmoid(np.dot(x, self.weights[0]) + self.bias[0])
        self.layerdata.append(self.to_first_layer) #
        
        #this adds from hidden layer to hidden layer
        for i in range(1,self.numLayers-1):
            self.layerdata.append(sigmoid(np.dot(self.layerdata[i-1], self.weights[i] + self.bias[i])))          
            
        #this adds from the last hidden layer to output
        self.to_output_layer =  sigmoid(np.dot(self.layerdata[-1], self.weights[-1]) + self.bias[-1])
        self.layerdata.append(self.to_output_layer) 
        self.outputs = (self.to_output_layer)


    def backprop(self): 

        #error from the actual and predicted output
        self.error = (y - self.layerdata[-1])
        
        #update the weights to output
        self.output_layer_gradient = sigmoid_derivative(self.layerdata[-1])      
        self.hidden_delta = self.error * self.output_layer_gradient #output delta
        self.weights[-1] = self.weights[-1] + np.dot(self.to_first_layer.T, self.hidden_delta) * self.lr  
        
        #loop the hidden layers  
        j = -1
        for i in range(1, self.numLayers-1,):
            self.hidden_layer_gradient = sigmoid_derivative(self.layerdata[j-1])         
            self.hidden_error = np.dot(self.hidden_delta,self.weights[j].T) 
            self.hidden_delta = self.hidden_error * self.hidden_layer_gradient
            self.weights[j-1] = self.weights[j-1] + np.dot(self.layerdata[j].T, self.hidden_delta) * self.lr  
            j = j-1
            
        #update the input's weights
        self.hidden_layer_gradient = sigmoid_derivative(self.to_first_layer)         
        self.hidden_error = np.dot(self.hidden_delta,self.weights[1].T)
        self.hidden_delta = self.hidden_error * self.hidden_layer_gradient
        self.weights[0] = self.weights[0] +  np.dot(x.T, self.hidden_delta) * self.lr  