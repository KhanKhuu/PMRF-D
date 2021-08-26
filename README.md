# PMRF-D

## Background:
see the PMRF-D paper for a complete explanation of PMRF-D including background and results:
- https://github.com/KhanKhuu/PMRF-D/blob/master/Paper/SULI_Summer%202020_Research%20Paper_Larkins_Matthew.pdf

## Dependencies:
1) OpenCV
2) CMake

## Installation:
1) cmake .
2) make

## Usage:
./PMRF-D imageName [#threadsToUse=1] [#iterations=1] [lambda=0.5] [psi_max=5000]

- Bracketed arguments are optional

- The right-hand side values in the bracketed arguments are the defaults for those parameters

- lambda is the weight to multiply the data term by during ICM

- psi_max is a cap on the data term during ICM. psi_max equal to one is Potts' model
