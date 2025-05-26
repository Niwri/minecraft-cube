from torch import tensor
import cv2
import mediapipe as mp
import numpy as np
import torch
  
# 3 LSB are used for flags
# Next 3 bits are used for type
TYPE_INVALID = 0x0

TYPE_DIRECTION = 0x8
FLAG_LEFT = 0x0
FLAG_RIGHT = 0x1
FLAG_UP = 0x2
FLAG_DOWN = 0x3

TYPE_GRAB = 0x18 


# def normalizePoints(points: tensor) -> tensor:
#   '''
#   takes the 18 points, and puts all points into this formulae:
#   X_i = (X_i - min(X)) /(max(X) - min(X))
#   Y_i = (Y_i - min(Y)) /(max(Y) - min(Y))
#   '''
#   normalizedPoints = points.detach().numpy()
#   # do stuff
#   maxValues = [np.amax(normalizedPoints[:, 0]), np.amax(normalizedPoints[:, 1]), np.amax(normalizedPoints[:, 2])]
#   minValues = [np.amin(normalizedPoints[:, 0]), np.amin(normalizedPoints[:, 1]), np.amin(normalizedPoints[:, 2])]
#   rangeValues = [maxValues[i] - minValues[i] for i in range(3)]

#   for i in range(3):
#     normalizedPoints[:, i] = (normalizedPoints[:, i] - minValues[i]) / rangeValues[i]
  
#   normalizedPoints = torch.tensor(normalizedPoints)
#   return normalizedPoints

def normalizePoints(points: np.array) -> np.array:
  '''
  takes the 18 points, and puts all points into this formulae:
  X_i = (X_i - min(X)) /(max(X) - min(X))
  Y_i = (Y_i - min(Y)) /(max(Y) - min(Y))
  '''
  normalizedPoints = points.copy()
  # do stuff
  maxValues = [np.amax(normalizedPoints[:, 0]), np.amax(normalizedPoints[:, 1]), np.amax(normalizedPoints[:, 2])]
  minValues = [np.amin(normalizedPoints[:, 0]), np.amin(normalizedPoints[:, 1]), np.amin(normalizedPoints[:, 2])]
  rangeValues = [maxValues[i] - minValues[i] for i in range(3)]

  for i in range(3):
    normalizedPoints[:, i] = (normalizedPoints[:, i] - minValues[i]) / rangeValues[i]
  
  return normalizedPoints