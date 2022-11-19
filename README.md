# AlgorithmAnalysis
FAU programming assignment designed to compare the implementation of three algorithms for the purpose of comparing empirical RT with predicted RT.

Selection  Problem:  given  an  array  A[1...n]  of  n  elements,  find  the  ith  order  statistic  (e.g.  ith smallest element) where 1 ≤ i ≤ n.
	For the order statistic, we will be using i = ⌊2n/3⌋
	We will be utilizing three algorithms to solve this problem, each algorithm with m = 5 iterations of each array of n = 10000, 20000, 30000, 40000, ...., 100000 values. The run time (RT) of each m iteration of every array of n values will be documented for analysis, and an average among the m iterations of every array of n values will be calculated.
  
The three algorithms will follow the given conventions, assuming array A[1…n]:

	ALG1(A, n, i)
	INSERTION-SORT(A, n)
	Print A[i]
	ALG2(A, n, i)
	HEAP-SORT(A, n)
	Print A[i]
	ALG3(A, n, i)
	X = RANDOMIZED-SORT(A, 1, n, i)
	Print x

Some applications of the selection problem include the distribution of various sets of numbers within industries including finance, insurance, and marketing (tied together with statistic analysis). Finding the ith smallest/lesser object of a set of objects is referenced to be used in policy distribution in insurers, as well as efficient distribution among power sources within the same machine, AKA battery distribution.

The language used for the implimentations of the three algorithms is C++ using Visual Studio Code

Peyton Adkins – Z23553314
November 19th 2022
