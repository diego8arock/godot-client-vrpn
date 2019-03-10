import LeastSquares as LS;
import numpy as np;
from random import choice;
from matplotlib import pyplot;


def PlotFunction(X, Y, percentage, indexA, indexB):
    n = len(X)-1; #Number of items
    split = int(n*percentage);

    #Delete all columns but the ones on the given indexes
    for i in range(len(Y[0])):
        if(i == indexA or i == indexB):
            continue;

        X = np.delete(X, 0, 1);

    #Normalize values
    for i in range(n+1):
        X[i] = X[i] / X.max();
    
    testX = X[split:];
    testY = Y[split:];

    #The items will be sorted into classes in this list
    Points = [[] for i in range(testY.shape[1])];

    W = LS.CalculateWeights(testX, testY);

    correct = 0;

    #Calculate accuracy
    for i in range(n):
        prediction = LS.Predict(W, X[i]);
        itemClass = list(Y[i].A1);

        if(prediction == itemClass):
            correct += 1;

        #Find index of class
        index = -1;
        for j in range(len(prediction)):
            if(prediction[j] == 1):
                index = j;
                break;

        Points[index].append(X[i]);

    accuracy = correct/float(n)*100;
    print "Accuracy ", accuracy;

    colors = ['r', 'b', 'g', 'c', 'm', 'y'];
    
    for i in range(len(Points)):
        p = Points[i];
        Xa = [];
        Xb = [];

        #Choose color randomly from list, then remove it
        #(to avoid duplicates)
        color = choice(colors);
        colors.remove(color);
        
        for item in p:
            Xa.append(item[:, [0]].item(0));
            Xb.append(item[:, [1]].item(0));

        pyplot.plot(Xa, Xb, 'o', color=color);
        pyplot.plot(W[i], color=color);
    
    pyplot.show();


def main():
    X,Y,n = LS.ReadData('data.txt');

    PlotFunction(X, Y, 0.7, 2, 3);

main();
