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

## Use
This command line program aims at solving the TSP problem and needs 2 arguments to run.
The first one is the algorithm to use, and the second one is the file representing the adjacency matrix, from which the graph will be built.
* To select the algorithm enter the option `--algo` or `-a` followed by one of the four available argument: `exact`, `constructive`, `local_search`, or `grasp`.
* To select the source file enter the option `--file` or `-f` followed by the absolute path of the file you want to use. This file needs to follow the specifications given in the [Instructions](Instructions.pdf) and to end in `.in`.

For example, you could call the program like this, assuming that you are in the correct directory:
```
./Travelling_Salesman_Problem -a grasp -f "/home/user/test.in"
```

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
