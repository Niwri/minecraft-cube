import numpy as np

array = np.load("trainingData/positiveGrab/grab-2025-05-25_23-26-13.npy")
print(array.shape)
print(np.max(array), np.min(array))