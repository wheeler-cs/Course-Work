from decimal import DivisionByZero
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

        # Remove certain columns to improve model
        # NOTE: Dropping these columns may not _really_ improve model performance, but a quick evaluation does show some
        # positive benefit to doing so. Ultimately, the problem this dataset applies to is hard to solve, and there are
        # **HUGE** number of possible combinations for dropping features that may boost how well a model does.
        dataFrame = dataFrame.drop("ROLE_DEPTNAME", axis=1)
        dataFrame = dataFrame.drop("ROLE_TITLE", axis=1)
        dataFrame = dataFrame.drop("ROLE_FAMILY_DESC", axis=1)
        dataFrame = dataFrame.drop("ROLE_FAMILY", axis=1)
        dataFrame = dataFrame.drop("ROLE_CODE", axis=1)

        # One-hot encode everything except the ACTION column (using two-category categorical classification)
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
        # This variable is initialized when a model is trained and then predicted using the validation set
        if(self.trainResults is None):
            print("[ERR] Please initialize and train model before generating performance statistics!")
            raise(ValueError)
    
        # Result values in counter variables for new counter iteration
        self.truePositives = 0
        self.falsePositives = 0
        self.trueNegatives = 0
        self.falseNegatives = 0
        # Compare training results with expected values
        for result in enumerate(self.validateLabels):
            # Obtained a negative in testing
            if(result[1] == 0):
                # True negative
                if self.trainResults[result[0]] == 0:
                    self.trueNegatives += 1
                # False negative
                else:
                    self.falseNegatives += 1
            # Obtained a positive in testing
            elif(result[1] == 1):
                # False positive
                if self.trainResults[result[0]] == 0:
                    self.falsePositives += 1
                # True positive
                else:
                    self.truePositives += 1
        
        try:
            # Calculate FPR
            self.falsePositiveRate = self.falsePositives / (self.falsePositives + self.trueNegatives)

            # Calculate F1 score
            recall = self.truePositives / (self.truePositives + self.falseNegatives)
            precision = self.truePositives / (self.truePositives + self.falsePositives)
            self.f1Score = (2 * precision * recall) / (precision + recall)
        except(DivisionByZero):
            # Theoretically, this should only occur if training wasn't performed and the pos-neg values are still 0
            print("[ERR] Please make sure model is trained before attempting to generate statistics!")
            raise(DivisionByZero)

    
    
    def __str__(self) -> str:
        # Treat printing as an output of the performance of the model after evaluation
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
