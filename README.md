# Travelling Salesman Problem
This is a school project which aims at designing different types of algorithms/heuristics in order to solve the TSP problem.
We also study and compare the performance of each solution.
This project is developed thanks to the [Boost](https://www.boost.org/doc/libs/1_72_0/libs/graph/doc/index.html) library in C++.

For mor informations please refer to the [Instructions](Instructions.pdf) and to the [Report](Report/Report.pdf).
Specific README are also available for each algorithm/heuristic.

### Installing
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
