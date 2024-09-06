import csv
import numpy as np
from sklearn.neural_network import MLPClassifier


class MultilayerPerceptron(object):
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

        # Statistics
        self.testDatasetSize = 0
        self.truePositives = 0
        self.trueNegatives = 0
        self.falsePositives = 0
        self.falseNegatives = 0
        self.precision = 0
        self.recall = 0
        self.fMeasure = 0
        self.fpr = 0
        self.fnr = 0
        self.tpr = 0
        self.tnr = 0

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
        # Split data into training and testing
        self.xTrain = data[:24000]
        self.yTrain = labels[:24000]
        self.xTest = data[24000:]
        self.yTest = labels[24000:]
        # Convert data to numpy arrays
        self.xTrain = np.array(self.xTrain).astype("int")
        self.yTrain = np.array(self.yTrain).astype("int")
        self.xTest = np.array(self.xTest).astype("int")
        self.yTest = np.array(self.yTest).astype("int")


    def runModel(self) -> None:
        classifier = MLPClassifier(solver="lbfgs", alpha=1e-5, hidden_layer_sizes=(5, 2), random_state=1)
        classifier.fit(self.xTrain, self.yTrain)
        predictions = classifier.predict(self.xTest)
        self.falsePositives = 0
        self.falseNegatives = 0
        self.truePositives = 0
        self.trueNegatives = 0
        for p in enumerate(predictions):
            # Mismatch indicates a false +/-
            if (p[1] != self.yTest[p[0]]):
                # F+
                if(p[1] == 1):
                    self.falsePositives += 1
                # F-
                else:
                    self.falseNegatives += 1
            # Match indicates a true +/-
            else:
                # T+
                if(p[1] == 1):
                    self.truePositives += 1
                # T-
                else:
                    self.trueNegatives += 1
        self.testDatasetSize = len(predictions)

    
    def calcStatistics(self) -> None:
        # NOTE: Formulas below were sourced from the information found at
        # https://machinelearningmastery.com/precision-recall-and-f-measure-for-imbalanced-classification/
        self.tpr = self.truePositives / (self.truePositives + self.falseNegatives)
        self.fpr = self.falsePositives / (self.falsePositives + self.trueNegatives)
        self.tnr = self.trueNegatives / (self.trueNegatives + self.falsePositives)
        self.fnr = self.falseNegatives / (self.falseNegatives + self.truePositives)
        self.precision = self.truePositives / (self.truePositives + self.falsePositives)
        self.recall = self.truePositives / (self.truePositives + self.falseNegatives)
        self.fMeasure = (2 * self.precision * self.recall) / (self.precision + self.recall)


    def __str__(self) -> str:
        return (f"TPR: {self.tpr}\nFPR: {self.fpr}\nTNR: {self.tnr}\nFNR: {self.fnr}" +
                f"\nPrecision: {self.precision}\nRecall: {self.recall}\nF-Measure: {self.fMeasure}")


if __name__ == "__main__":
    mlp = MultilayerPerceptron("data/train.csv")
    mlp.runModel()
    mlp.calcStatistics()
    print(mlp)
