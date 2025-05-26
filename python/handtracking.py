import cv2
import mediapipe as mp
import numpy as np
from util import *
import keyboard
import datetime
mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles
mp_hands = mp.solutions.hands

class HandTracking:
  def __init__(self):
    self.cap = cv2.VideoCapture(0)
    self.hands = mp_hands.Hands(
      model_complexity=0,
      min_detection_confidence=0.5,
      min_tracking_confidence=0.5)
    self.landmarkPositions = np.zeros((2, 21, 3), dtype=np.float32)
    self.detectionFunctions = [
      self.detectDirection,
    ]

    self.saveData = []
    self.saveDataFlag = False
    self.releaseFlag = True

  def __del__(self):
    self.cap.release()

  def handTrackingProcess(self):
    while self.cap.isOpened():
      success, image = self.cap.read()
      if not success:
        print("Ignoring empty camera frame.")
        continue

      image.flags.writeable = False
      image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
      results = self.hands.process(image)

      image.flags.writeable = True
      image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
      if results.multi_hand_landmarks:
        for handId, hand_landmarks in enumerate(results.multi_hand_landmarks):
          handNum = 0 if results.multi_handedness[handId].classification[0].index == "Left" else 1
          mp_drawing.draw_landmarks(
            image,
            hand_landmarks,
            mp_hands.HAND_CONNECTIONS,
            mp_drawing_styles.get_default_hand_landmarks_style(),
            mp_drawing_styles.get_default_hand_connections_style())
          
          for landmarkId, landmark in enumerate(hand_landmarks.landmark):
            self.landmarkPositions[handNum, landmarkId, :] = [landmark.x, landmark.y, landmark.z]

        # TODO: Run a list of functions to process landmarksPositions here
        # for detectionFunc in self.detectionFunctions:
        #   result = detectionFunc(self.landmarkPositions)
        #   print(f"Detection Result: {result}")
        #   if result == TYPE_INVALID:
        #     continue

      if keyboard.is_pressed('s') and releaseFlag:
        releaseFlag = False
        if self.saveDataFlag:
          self.saveDataFlag = False

          fileName = "trainingData/negativeGrab/grab-" + datetime.datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
          print(f"Toggled Off! Saving file: {fileName}.npy")
          print(np.array(self.saveData).shape)
          np.save(fileName, np.array(self.saveData))
          self.saveData = []
        else:
          self.saveDataFlag = True
          self.saveData = []

          print("Toggled On!")

      elif not keyboard.is_pressed('s'):
        releaseFlag = True
      
      if self.saveDataFlag:
        self.saveData.append(normalizePoints(self.landmarkPositions[1, :, :]))

      cv2.imshow('MediaPipe Hands', cv2.flip(image, 1))
      cv2.waitKey(1)
    self.cap.release()


  def detectDirection(landmarkPositions):

    return TYPE_DIRECTION, 