import numpy as np
import pandas as pd
from sklearn.naive_bayes import MultinomialNB
from sys import argv


# --- NaiveBayes Class -------------------------------------------------------------------------------------------------
class NaiveBayes(object):
    def __init__(self) -> None:
        # Data-related variables
        self.trainData           = None
        self.trainLabels         = None
        self.validateData        = None
        self.validateLabels      = None

        # Model-related variables
        self.model               = None
        self.trainResults        = None

        # Model performance statistics
        self.f1Score:           float = 0.0
        self.truePositives:     int   = 0
        self.falsePositives:    int   = 0
        self.trueNegatives:     int   = 0
        self.falseNegatives:    int   = 0
        self.falsePositiveRate: float = 0.0


    def importData(self, fileName: str) -> None:
        # Create a data frame
        dataFrame = pd.read_csv(fileName)
        dataFrame.head()

        # One-hot encode everything except the ACTION column
        dataFrame = pd.get_dummies(dataFrame, columns=dataFrame.columns[1:])

        # Split the data 80-20 training and validation
        trainingDataset = dataFrame.sample(frac=0.80, random_state=42)
        validationDataset = dataFrame.drop(trainingDataset.index)

        # Split labels from data
        self.trainData = trainingDataset.drop("ACTION", axis=1)
        self.trainLabels = trainingDataset["ACTION"]
        self.validateData = validationDataset.drop("ACTION", axis=1)
        self.validateLabels = validationDataset["ACTION"]

        # Get the shape of the dataset for the model
        self.datasetShape = [self.trainData.shape[1]]


    def initializeModel(self) -> None:
        self.model = MultinomialNB()


    def trainModel(self) -> None:
        self.model.fit(self.trainData, self.trainLabels)
        self.trainResults = self.model.predict(self.validateData)

    
    def generateStatistics(self) -> None:
        self.truePositives = 0
        self.falsePositives = 0
        self.trueNegatives = 0
        self.falseNegatives = 0
        # Compare training results with expected values
        for result in enumerate(self.validateLabels):
            # Obtained a negative in testing
            if(result[1] == 0):
                if self.trainResults[result[0]] == 0:
                    self.trueNegatives += 1
                else:
                    self.falseNegatives += 1
            # Obtained a positive in testing
            elif(result[1] == 1):
                if self.trainResults[result[0]] == 0:
                    self.falsePositives += 1
                else:
                    self.truePositives += 1
        
        # Calculate FPR
        self.falsePositiveRate = self.falsePositives / (self.falsePositives + self.trueNegatives)

        # Calculate F1 score
        recall = self.truePositives / (self.truePositives + self.falseNegatives)
        precision = self.truePositives / (self.truePositives + self.falsePositives)
        self.f1Score = (2 * precision * recall) / (precision + recall)

    
    
    def __str__(self) -> str:
        return (f"F1-Score: {self.f1Score}" +
                f"\nFP Count: {self.falsePositives}" +
                f"\nTN Count: {self.trueNegatives}" +
                f"\n FP Rate: {self.falsePositiveRate}")



# --- main() -----------------------------------------------------------------------------------------------------------
if __name__ == "__main__":
    nBayes = NaiveBayes()
    nBayes.importData(argv[1])
    nBayes.initializeModel()
    nBayes.trainModel()
    nBayes.generateStatistics()
    print(nBayes)
