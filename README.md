# Robot 

## Building the project

From the projects root directory:

```
mkdir build
cd build
cmake ..
cmake --build .
```

## Running

By default binaries are stored in robot/build/src/.  
From the build directory run:

```
./src/robot_simulator
```

Then provide full or relative path to the text file with instructions.  
There must be no spaces between PLACE command parameters! 

```
PLACE 1,2,NORTH
```

## Running tests
Project requires Catch2 for tests.
Can be found here:

[Catch2 github](https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md#installing-catch2-from-git-repository)

By default test binaries are stored in robot/build/test/  
From the build directory run:

```
./test/tests
```