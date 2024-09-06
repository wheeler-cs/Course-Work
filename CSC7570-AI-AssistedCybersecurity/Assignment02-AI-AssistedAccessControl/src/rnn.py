import csv
from tkinter import Label
import keras
import numpy as np
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import LabelEncoder
import tensorflow as tf


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
        allXData = np.array(data).astype("int")
        allYData = np.array(labels).astype("int")
        # One-hot encode
        enc = LabelEncoder()
        enc.fit(np.unique(allXData))
        self.uniqueElements = len(np.unique(allXData))
        for x in allXData:
            x = enc.transform(x)
        # Convert arrays to tensors
        self.xTrain = tf.convert_to_tensor(allXData[:28000], dtype=tf.int64)
        self.yTrain = tf.convert_to_tensor(allYData[:28000], dtype=tf.int64)
        self.xTest  = tf.convert_to_tensor(allXData[28000:], dtype=tf.int64)
        self.yTest  = tf.convert_to_tensor(allYData[28000:], dtype=tf.int64)


    def initModel(self) -> None:
        self.model = keras.Sequential()
        self.model.add(keras.Input(shape=(9,), dtype=tf.int64))
        self.model.add(keras.layers.Embedding(input_dim=self.uniqueElements, output_dim=512))
        self.model.add(keras.layers.LSTM(512))
        self.model.add(keras.layers.Dense(256))
        self.model.add(keras.layers.Dense(1))
        self.model.compile(loss=keras.losses.binary_crossentropy, optimizer="Adam", metrics=["accuracy", keras.metrics.AUC(dtype=tf.int64), keras.metrics.FalsePositives(dtype=tf.int64)])
        self.model.fit(x=self.xTrain, y=self.yTrain, batch_size=150, epochs=1)
        self.model.evaluate(x=self.xTest, y=self.yTest)


if __name__ == "__main__":
    recurrNN = RNN("data/train.csv")
    recurrNN.initModel()
