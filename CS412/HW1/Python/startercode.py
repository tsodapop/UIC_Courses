#From the console, run the following
#pip install numpy
#pip install scipy
#pip install scikit-learn
#pip install matplotlib

import numpy as np
from sklearn.neighbors import KNeighborsClassifier
import matplotlib.pyplot as mp
from pylab import show

data = np.loadtxt("data.csv")

#shuffle the data and select training and test data
np.random.seed(100)
np.random.shuffle(data)



features = []
digits = []


for row in data:
    if(row[0]==1 or row[0]==5):
        features.append(row[1:])
        digits.append(str(row[0]))

#select the proportion of data to use for training
numTrain = int(len(features)*.2)

trainFeatures = features[:numTrain]
testFeatures = features[numTrain:]
trainDigits = digits[:numTrain]
testDigits = digits[numTrain:]

#create the model
#https://scikit-learn.org/stable/modules/generated/sklearn.neighbors.KNeighborsClassifier.html



X = []
Y = []
simpleTrain = []
colors = []
for index in range(len(trainFeatures)):
    X.append(trainFeatures[index][72])
    Y.append(trainFeatures[index][88])
    simpleTrain.append([trainFeatures[index][72],trainFeatures[index][88]])
    if(trainDigits[index]=="1.0"):
        colors.append("b")
    else:
        colors.append("r")


#https://matplotlib.org/api/_as_gen/matplotlib.pyplot.scatter.html
#this just shows the points
#mp.scatter(X,Y,s=3,c=colors)
# show()

model = KNeighborsClassifier(n_neighbors=1)
model.fit(simpleTrain,trainDigits)

xPred = []
yPred = []
cPred = []
for xP in range(-100,100):
    xP = xP/100.0
    for yP in range(-100,100):
        yP = yP/100.0
        xPred.append(xP)
        yPred.append(yP)
        if(model.predict([[xP,yP]])=="1.0"):
            cPred.append("r")
        else:
            cPred.append("b")

mp.scatter(xPred,yPred,s=3,c=cPred,alpha=.2)
show()
