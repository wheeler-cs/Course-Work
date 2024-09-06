# ==== Imports =========================================================================================================
import csv
import numpy as np
import keras
from sys import argv
import tensorflow as tf


# ==== Functions =======================================================================================================
def readDataFile(fileName: str):
    with open(fileName, "rt") as dataStream:
        csvData = csv.reader(dataStream, delimiter=',')
        csvList = list(csvData)
    header = csvList[0]
    data = csvList[1:-1]
    x = []
    y = []
    for d in data:
        y.append(d[0])
        d = d[1:]
    processedData = np.array(data).astype("int")
    processedY = np.array(y).astype("int")

    data = tf.convert_to_tensor(processedData, dtype=tf.int64)
    y_train = tf.convert_to_tensor(processedY, dtype=tf.int64)


    model = keras.Sequential()
    model.add(keras.layers.Embedding(input_dim=500000, output_dim=64))
    model.add(keras.layers.LSTM(16))
    model.add(keras.layers.Dense(8))
    model.add(keras.layers.CategoryEncoding(2))
    model.compile(loss=keras.losses.SparseCategoricalCrossentropy(), optimizer="Adam", metrics=["accuracy"])
    model.fit(data, y_train, batch_size=150, epochs=1)
    model.summary()


# ==== Main ============================================================================================================
if __name__ == "__main__":
    readDataFile(argv[1])
