# WSI - Wprowadzenie do Sztucznej Inteligencji  (Introduction to Artificial Intelligence) - lista 1 (15-Puzzle)
Author: Marek Świergoń

Program solving 15-Puzzle using A* algorithm with four different heuristics: Manhattan Distance, Manhattan Distance With Simplified Linear Conflicts 
(non-admissible, although in most cases is the fastest and gives results with the same quality as other heuristics used here, which are admissible), Inversion Distance and
Maximum(MD, ID) (usually the best admissible heuristics out of above).

To run it, enter (Linux):
`./solver <type> <flag (optional)>`

Types are:
* `MD` - Manhattan Distance Heuristic,
* `ID` - Inversion Distance Heurisitc,
* `MAXMDID` - Maximum(MD, ID) Heuristic,
* `MDLC` - Manhattan Distance with Simplified Linear Conflicts.

By default, program takes from stdin instance to solve.
`1;2;3;4;5;6;7;8;9;10;11;12;13;14;15;0` is an example format of stdin (already solved 15-Puzzle, 0 denotes the blank space).
Optional flag, `--random`, specifies that instead of reading instance from stdin, program will generate random solvable instance.

Example execution of program:

```
./solver MDLC --random
Generated permutation: 
-------------
|08|11|07|15|
-------------
|00|05|10|04|
-------------
|09|01|13|12|
-------------
|03|02|06|14|
-------------
Moves MD+SimplifiedLC (49 total):
5->1->2->3->9->5->1->2->3->6->13->10->4->15->7->11->8->1->2->3->6->13->10->12->15->4->11->8->3->2->5->9->13->10->14->15->12->11->8->7->4->8->7->3->2->6->10->14->15->SOLVED!
Solution found with 257663 explored game states.
```
Solution is displayed as series of pieces of puzzle to be sequentially moved onto blank space (in example we first make move 05 onto 00, then 01 onto 00, etc.).

In folder test_results, some test results can be found. We can see that not all instances are solvable by program using each of the heurisitcs (runs out of memory, tests performed on 16GB RAM). 