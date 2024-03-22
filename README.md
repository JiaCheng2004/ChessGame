# ChessGame
Chess Game online

---

## Instructions

---

Talks about our AI later

---

### Requirements

Make sure you have:
1. Compiler `g++` version `13.2` or above.
2. Installed `CMake` version `3.8` or above.

---

### Building and Compiling

1. Make a directory in the project root directory: `build`
```
mkdir build
```
2. Navigate to the `build` directory.
```
cd build
```
3. Use this `cmake` command to make the makefiles to compile the project.
```
cmake ..
```
4. Use this `make` command to make the executabe file with this command. Remove the `-j` option if you don't wanna use all cores to compile.
```
make -j
```
5. Now run the ChessGame executable
```
./ChessGame
```

---

### Executable Arguments and Options

#### Verbose
`--verbose`, `--debug`, `-verbose`, `-debug`,`-v`, `-V`, `-d`, `-D`\
Showing all the details and what's happening in the background. Used for debugging and behavoir screening. Default is false.

#### Test
`--test`, `-test`, `-t`, `-T`\
Testing the program with the testing input, followed by the file name inside the test directory. Used for debugging and testing.

#### AI
`--ai`, `--bot`, `-ai`, `-bot`\
Choose to play the game against an AI, followed by the name of the AI. Default is none.