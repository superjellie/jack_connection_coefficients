# How to compile

To compile you will need `gcc` compiler and `make`. There are 2 programs:

- `acalc` - calculates Jack Connection Coefficients in special case.
- `graph` - prints partition diagram as graph in DOT language (can be used by graphviz).
	
To make `graph` simply write:
```
$ make graph
```

To make `acalc` you need to choose size of numbers you will use and output format.
In general one make `acalc` like this:
```
$ make <t|b><d|x><8|16|32|64|128|256|512>
``` 

Where:

- `t` means text-based output, `b` means binary
- `d` means print in decimal form (only for text-based), `x` means hex
- number is size of numbers to use in bits

All possible combinations are following:
```
td8 td16 td32 td64 tx8 tx16 tx32 tx64 tx128 tx256 tx512
bx8 bx16 bx32 bx64 bx128 bx256 bx512
```

# How to use

After compiling you will have two programs in directory:

- `graph`
- `acalc`

Both of them recieve one command-line argument - N for wich calculation is performed.
Both programs will output in standart stream. If you want to output in file use pipes.

Possible usage:
```
$ acalc 10 > file.txt
$ graph 10 | dot -Tsvg > output.svg
```
(`dot` is [graphviz](https://graphviz.org/) program for graph vizualization).

# TODO

1. Program that will extract data from binary file, generated by `acalc`.
2. Generalization to the case with two non-trivial partitions.