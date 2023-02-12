# bucketing-superkmers

C++ implementation of a superkmer bucketing tool for an intern test from https://github.com/yoann-dufresne/buckettingtest

# Use 

## Compiling

To compile a first time :
```
make
```

To clean up the repository and delete all compiled files :
```
make clean
```

## Executing

To use the program :
```
./main file_in rep_out k m
```
With : 
- file_in : file in FASTA format
- rep_out : path to a repository where the output will be saved
- k : integer smaller or equal to 31
- m : integer smaller than k representing the size of the minimisers

For example : 
```c
./main ../fastafiles/sequence.fasta ../fastafiles/ 31 20
// or
./main data/ecoli.fasta data/ecoli_out/ 31 13
```

## Result

Output is a file titled `superkmer_buckets.txt` saved in the given repository, containing one superkmer per line.
