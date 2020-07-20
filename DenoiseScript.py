#!/usr/bin/env python
# coding: utf-8

import cv2
import numpy as np
import subprocess
from os import path
import unicodedata


# ### Get names of all the images to open and their containing folder names

with open("Input/imageNames.txt") as f:
    imageNames = f.read().splitlines()
print(imageNames)
imageFolderNames = [path.splitext(imageName)[0] for imageName in imageNames]
print(imageFolderNames)


# ### Get names of all the folders containing images with the corresponding noise type

with open("Input/imageCategories.txt") as f:
    imageCategories = f.read().splitlines()
if 'Original' in imageCategories:
    imageCategories.remove('Original')
print(imageCategories)


# ### Call PMRF-D for all the images

for i in range(len(imageNames)):
    for noiseType in imageCategories:
        folder = 'Input/' + imageFolderNames[i] + "/" + noiseType + "/"
        noisedImageName = str(subprocess.check_output(["ls", folder]).decode('utf-8')).rstrip()
        NUM_THREADS = 8
        NUM_ITERS = [1, 2]
        LAMBDAS = [0.01, 0.1, 0.5, 1.0, 10.0, 100.0]
        PSI_MAXES = [1, 10, 100, 1000, 5000, 65025]
        for lam in LAMBDAS:
            for psi_max in PSI_MAXES:
                for num_iter in NUM_ITERS:
                    subprocess.run(["./PMRF-D", folder + noisedImageName, str(NUM_THREADS), str(num_iter), str(lam), str(psi_max)])



