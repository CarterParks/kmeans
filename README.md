# K-means Spotify
Use K-means clustering to group Spotify data based on metrics found in `genres_v2.csv`.
# Description
## Serial
The serial implementation implemented the K-means clustering 
algorithm as simply as possible with, a focus on isolating the 
functional parts of the program to aid parallelization later 
on.

## Shared CPU
The shared CPU implementation made use of OpenMP to parallelize 
protions of logic that were frequently running. Typically, this 
entailed the use of the `parallel for` directive to divide the 
serial work among processors.

## Shared GPU
The shared GPU implementation condensed much of the code down 
to its bare essentials. Using CUDA allowed the creation of kernels 
that could be launched to spearate the work of what would ususally 
be a serial loop. Although the output does not identically match 
the serial implementation, the visualization is inidstiguishable 
from the above implementations.

# Compilation
Makefiles are included in each subdirectory.

Compile with `make`

# Execution Script
The execution, validation and visualization steps can all be run with.

`bash run-all.sh`

# Execution
Each file has been already compiled within its subdirectory, 
and can be run as follows:

`./serial ../indata.csv > outdata`

The output is an in-order list of each song's cluster.

# Visualization
Visulization can be run using matplotlib as follows:

`python3 visualize.py serial shared-cpu shared-gpu`

# Validation
Validation was performed with GNU's `diff` program as follows:

`diff -q serial/outdata shared-cpu/outdata`

# Input
The input has been altered to only include the three visualized columns. An input file with more columns can be added by replacing the COLS definition in kmeans.h

