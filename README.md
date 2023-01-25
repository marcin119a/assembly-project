## Project

C++ part
I used a modification of the algorithm presented in the lecture to calculate the overlap (Dynamic programming). My algorithm solves the problem in O(k) memory where k is the read length, and O(k^2) complexity with an improved constant of 1/2. In addition, I compute 2 overlaps for the sequences x and y and y and x. The algorithm was written in C++.

Python part
To compute the contig I use a greedy modification of the DFS algorithm, which walks over the constructed graph of overlaps greedily considering the best edges, in each step sorting the edges due to the overlap. 

The graph itself is built in such a way that some edges are removed if the calculated ratio percent_of_mismatches is too big. Which significantly improves the structure of the graph instead of O(n^2) vertices I have about 25% of the vertices. 

In addition, I walk over each vertex and run the search algorithm for it. In this way, I get a contig. 

However, I take care not to remove paths that are too short, I have a minimal_size_contig parameter that decides whether to try to lengthen the config in the future.
The algorithm works effectively ~ 1 minute C++ + Python part. 
