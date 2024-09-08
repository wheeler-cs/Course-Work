# --- Imports ----------------------------------------------------------------------------------------------------------
import keras
import pandas as pd
from sys import argv
import tensorflow as tf

# --- DeepNeuralNetwork Class ------------------------------------------------------------------------------------------
class DeepNeuralNetwork(object):
    def __init__(self) -> None:
        # Data-related variables
        self.trainData      = None
        self.trainLabels    = None
        self.validateData   = None
        self.validateLabels = None
        self.datasetShape   = None

        # Model-related variables
        self.model: keras.Sequential = None
        self.trainResults = None

        # Model performance statistics
        self.f1Score: float      = 0.0
        self.falsePositives: int = 0
        self.trueNegatives: int  = 0
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
        # Create the layers of the model
        self.model = keras.Sequential([
            keras.layers.Dense(64, activation="gelu"),
            keras.layers.Dense(16),
            keras.layers.Dense(32),
            keras.layers.Dense(64, activation="leaky_relu"),
            keras.layers.Dense(32),
            keras.layers.Dense(16),
            keras.layers.Dense(16),
            keras.layers.Dense(8),
            keras.layers.Dense(4),
            keras.layers.Dense(units=1, input_shape=self.datasetShape, activation="sigmoid")
        ])
        # Compile to allow for training
        self.model.compile(optimizer="adam", loss="mean_squared_error", metrics=["f1_score", "false_positives", "true_negatives"])


    def trainModel(self) -> None:
        # Train the model, recording the results
        self.trainResults = self.model.fit(self.trainData, self.trainLabels, validation_data=(self.validateData, self.validateLabels), batch_size=64, epochs=10)


    def generateStatistics(self) -> None:
        # Get the metrics for the very last epoch
        self.f1Score = self.trainResults.history["val_f1_score"][-1]
        self.falsePositives = self.trainResults.history["val_false_positives"][-1]
        self.trueNegatives = self.trainResults.history["val_true_negatives"][-1]
        self.falsePositiveRate = self.falsePositives / (self.falsePositives + self.trueNegatives)


    def __str__(self) -> str:
        return (f"F1-Score: {self.f1Score}" +
                f"\nFP Count: {self.falsePositives}" +
                f"\nTN Count: {self.trueNegatives}" +
                f"\n FP Rate: {self.falsePositiveRate}")


# --- main() -----------------------------------------------------------------------------------------------------------
if __name__ == "__main__":
    dnn = DeepNeuralNetwork()
    dnn.importData(argv[1])
    dnn.initializeModel()
    dnn.trainModel()
    dnn.generateStatistics()
    print(dnn)
