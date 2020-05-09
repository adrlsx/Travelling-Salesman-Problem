# Travelling Salesman Problem
This is a school project which aims at designing different types of algorithms/heuristics in order to solve the TSP problem.
We also study and compare the performance of each solution.
This project is developed thanks to the [Boost](https://www.boost.org/doc/libs/1_72_0/libs/graph/doc/index.html) library in C++.

For mor informations please refer to the [Instructions](Instructions.pdf) and to the [Report](Report/Report.pdf).
Specific README are also available for each algorithm/heuristic.

## Installing
Download the zip file from [Github](https://github.com/adrienls/MCQ-Correction)
```
wget --no-cookies https://github.com/adrienls/Travelling-Salesman-Problem/archive/master.zip -O Travelling-Salesman-Problem-master.zip
```

Unzip the folder
```
unzip ./Travelling-Salesman-Problem-master.zip
```
Install the needed dependency
```
# apt install libboost-graph-dev
```

Compile the project for your system using the [CMakeLists.txt](CMakeLists.txt) or the [Makefile](Makefile) available

Start the program by launching the `./Travelling_Salesman_Problem` file with the correct arguments.

Use the `--help` option for more information.

## Usage

### Mandatory options
This command line program aims at solving the TSP problem and needs at least 2 arguments to run.
The first one is the algorithm to use, and the second one is the file representing the adjacency matrix, from which the graph will be built.
* To select the algorithm enter the option `--algo` or `-a` followed by one of the four available argument: `exact`, `constructive`, `local_search`, or `grasp`.
* To select the source file enter the option `--file` or `-f` followed by the absolute path of the file you want to use. This file needs to follow the specifications given in the [Instructions](Instructions.pdf) and to end in `.in`.

For example, you could call the program like this, assuming that you are in the correct directory:
```
./Travelling_Salesman_Problem -a local_search -f "/home/user/test.in"
```
### Local Search specific
In the case you are running the local search heuristic, another option is available:
* To specify the maximum number of allowed iterations enter the option `--local-search-max-iteration` or `-l` followed by an integer greater than or equal to 1.
The Local Search heuristic will stop if it reaches the input iteration number and it will print out the best result.
This option is not mandatory, and its default value is `100`.

### GRASP specific
In the case you are running GRASP, two more options are available:
* To specify the Restricted Candidate List (RCL) quality criteria enter the option `--rcl-quality` or `-r` followed by a positive percentage.
This percentage ables GRASP to select the elements that are not more than `input%` away from the best element.
This option is not mandatory, and its default value is `5`.
* To specify the number of allowed iteration without improvement, enter the option `--improved-iteration` or `-i` followed by an integer greater than or equal to 1.
When GRASP finds a solution better than the best one he found yet, it resets the number of iteration to 0. For each solution found the number of iteration is incremented by one, and if it reaches the input iteration number GRASP stops and prints out the best result.
This option is not mandatory, and its default value is `15`.
* To specify the maximum number of allowed iterations enter the option `--grasp-max-iteration` or `-g` followed by an integer greater than or equal to 1.
GRASP will stop if it reaches the input iteration number and it will print out the best result.
This option is not mandatory, and its default value is `100`.

As the local search heuristic is used as part of GRASP you can also specify the max iteration number for the local search heuristic when using GRASP.

For example, you could call GRASP like this, assuming that you are in the correct directory:
```
./Travelling_Salesman_Problem -a grasp -f "/home/user/test.in" -r 10 -i 30 -g 50
```

### Instance generator
An option is available to generate a random instance in `*.in` for testing purpose.
This instance will have the size given in argument and will follow the [Instructions](Instructions.pdf) specifications.
Furthermore, each distance in the graph will randomly be between 1 and the the number of vertices times 10.
* To specify the size of the instance enter the option `--new-instance` or `-n` followed by an integer greater than or equal to 1.
This option is not mandatory, and its default value is `15`.

**If options are badly used, for example with invalid algorithms/heuristics no error will be thrown, but they will be discarded and there value will not be taken into account.**

## Built With
* [The Boost Graph Library (BGL)](https://www.boost.org/doc/libs/1_72_0/libs/graph/doc/index.html) - A standardized generic interface for traversing graphs.

## Authors
* [arthur79](https://github.com/arthur79)
* [jeremybeaugeard](https://github.com/jeremybeaugeard)
* [rt6fano](https://github.com/rt6fano)
* [adrienls](https://github.com/adrienls)

## License
This project is licensed under the GNU AGPLv3 License - see the [LICENSE.md](LICENSE) file for details

License chosen thanks to [choosealicense.com](https://choosealicense.com/)
