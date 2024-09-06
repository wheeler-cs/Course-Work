import csv
import numpy as np
from sklearn.neural_network import MLPClassifier


class RNN(object):
    def __init__(self, dataFile: str = "") -> None:
        # Model variables
        self.model = None
        self.uniqueElements = 0

        # Data variables
        self.dataHeader = []
        self.xTrain = []
        self.yTrain = []
        self.xTest = []
        self.yTest = []

        # Setup calls
        if(dataFile != ""):
            self.importData(dataFile)


    def importData(self, fileName: str) -> None:
        # Pull data from CSV
        with open(fileName, "rt") as dataStream:
            csvData = csv.reader(dataStream, delimiter=',')
            csvList = list(csvData)
        # Strip field headers from data
        self.dataHeader = csvList[0]
        if(csvList[-1] == ""):
            # Remove blank line at end of file
            dataLines = csvList[1:-1]
        else:
            dataLines = csvList[1:]
        # Divide training data into labels and data
        data = []
        labels = []
        for line in dataLines:
            labels.append(line[0])
            data.append(line[1:])
        self.xTrain = data[:28000]
        self.yTrain = labels[:28000]
        self.xTest = data[28000:]
        self.yTest = labels[28000:]
        self.xTrain = np.array(self.xTrain).astype("int")
        self.yTrain = np.array(self.yTrain).astype("int")
        self.xTest = np.array(self.xTest).astype("int")
        self.yTest = np.array(self.yTest).astype("int")
        #allXData = np.array(data).astype("int")
        #allYData = np.array(labels).astype("int")

        classifier = MLPClassifier(solver="lbfgs", alpha=1e-5, hidden_layer_sizes=(5, 2), random_state=1)
        classifier.fit(self.xTrain, self.yTrain)
        predictions = classifier.predict(self.xTest)
        count = 0
        for p in enumerate(predictions):
            if (p[1] != self.yTest[p[0]]):
                count += 1
        print(count)
        print(len(predictions))


if __name__ == "__main__":
    recurrNN = RNN("data/train.csv")
