#!/usr/bin/env python
# coding: utf-8

# In[1]:


import cv2
import numpy as np
import subprocess
from os import path
import unicodedata


# ### Get names of all the images to open and their containing folder names

# In[2]:


with open("Input/imageNames.txt") as f:
    imageNames = f.read().splitlines()
print(imageNames)
imageFolderNames = [path.splitext(imageName)[0] for imageName in imageNames]
print(imageFolderNames)


# ### Get names of all the folders containing images with the corresponding noise type

# In[3]:


with open("Input/imageCategories.txt") as f:
    imageCategories = f.read().splitlines()
if 'Original' in imageCategories:
    imageCategories.remove('Original')
print(imageCategories)


# ### Call PMRF-D for all the images

# In[ ]:


for i in range(len(imageNames)):
    for noiseType in imageCategories:
        folder = 'Input/' + imageFolderNames[i] + "/" + noiseType + "/"
        noisedImageName = str(subprocess.check_output(["ls", folder]).decode('utf-8')).rstrip()
        subprocess.run(["./PMRF-D", folder + noisedImageName, "1000"])


# In[ ]:




