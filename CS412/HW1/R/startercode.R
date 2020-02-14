#Installing packages ONLY RUN THIS ONCE!
#Make sure that you have the up to date GCC and R
install.packages("caret",dependencies=TRUE)
install.packages("e1071")
install.packages("dplyr")
install.packages("ggplot2")

#Linking the packages
library(caret)
library(e1071)
library(dplyr)
library(ggplot2)

# Read data
# If you have trouble loading the data, 
# Select "Source File Location" under Session -> Set Working Directory

data = read.csv("data.csv",sep=" ",header=FALSE,col.names=append("Digit",seq(1,257,by=1)))

data$X257 = NULL

#selecting 
data = filter(data,Digit==1|Digit==5)
#force R to treat 1,5 as categories, not numerics
data$Digit = as.factor(data$Digit)

#Partitioning the data
set.seed(100)
index = createDataPartition(data$Digit, p = 0.2, list = F )
train = data[index,]
test = data[-index,]

#pick the first and second pixel and plot them
#https://www.rstudio.com/wp-content/uploads/2015/03/ggplot2-cheatsheet.pdf
graph <- ggplot(train,
                aes(x=X72,X88))+# this sets the axes CHOOSE BETTER AXES THAN THIS
        geom_point(aes(color=Digit)) #this tells the plot to make a scatter plot and color them based on digit

graph #this will display the graph

#Set the level of cross-validation
trControl <- trainControl(method  = "cv",
                          number  = 10)

#this will build the model
model1 <- train(Digit~. , # the . character means use all other variables
                data = train, 
                trControl = trControl, 
                method = "knn",
                tuneGrid   = expand.grid(k = 1:49)) #modeling 1s and 5s for 256 dimensions
plot(model1)

model2 <- train(Digit~X72+X88 , #these are the predictive variables
                data = train, 
                method = "knn",
                trControl = trControl,
                tuneGrid   = expand.grid(k = 1:49)) #modeling 1s and 5s for 256 dimensions
plot(model2)

m
