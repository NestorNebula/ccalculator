<a id="top"></a>

<div align="center">
    <h3>CCalculator</h3>
</div>

---

### Table of Contents

- [Description](#description)
  - [Built With](#built-with)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
  - [Basic Usage](#basic-usage)
  - [Powers and Square roots](#powers-and-square-roots)
  - [Variables](#variables)
  - [Precedence](#precedence)
- [Contributing](#contributing)
- [Acknoledgements](#acknoledgements)
- [License](#license)

---

## Description

CCalculator is a command line calculator implemented in C.

The calculator can compute the result of any expression containing numbers, basic operators (+, -, \* and /), brackets and two specials characters (^ in the format n^p to compute n to the power of p and √ in the format √n to compute the square root of n).

The calculator also accepts the creation and usage of variables. Results of expressions can be used to declare variables, that can be reused in following expressions.

### Built With

[![C](https://skillicons.dev/icons?i=c&theme=light)](https://www.c-language.org/)
[![CMake](https://skillicons.dev/icons?i=cmake&theme=light)](https://cmake.org/)

## Getting Started

### Prerequisites

- CMake
- vcpkg

### Installation

1. Fork the [Project repository](https://github.com/NestorNebula/ccalculator)
2. Clone the forked repository to your local machine
   ```
   git clone git@github.com:<your username>/<repo name>.git
   ```
3. Update remote URL

   ```
   # SSH:
   git remote add upstream git@github.com:NestorNebula/ccalculator.git

   # HTTPS:
   git remote add upstream https://github.com/NestorNebula/ccalculator.git
   ```

4. From the root directory of the project, create the "build" directory
   ```
   cmake -B build/ -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg
   ```
5. Go to the "build" directory created by the previous command and build the program
   ```
   make
   ```
6. Run the program
   ```
   ./ccalculator
   ```

#### Tests

Tests suites can be found in the "tests" directory.

New files in this directory with the extension .cpp will automatically be considered as tests suites.

To run tests, follow this steps:

1. From the root directory of the project, go to the "tests" directory
   ```
   cd tests
   ```
2. Create the "build" directory
   ```
   cmake -B build/ -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg
   ```
3. Go to the "build" directory created by the previous command and build the test file
   ```
   make
   ```
4. Run the tests
   ```
   ./ccalculator_tests
   ```

## Usage

### Basic usage

Once the program is running, the user can enter an expression. The program will print the result of the expression.

```c
Enter an expression: 1 + 1
2

Enter an expression: 3 - 2
1

Enter an expression: 3 * 3
9

Enter an expression: 2 / 2
1
```

#### Program termination

Entering an empty expression (except if it is redirected as a [variable assignment](#variables)) causes the program to terminate.

```c
Enter an expression:
// End of program
```

### Powers and Square roots

The program supports powers and square roots but they must be written in a specific format.

#### Powers

Powers are supported in the format n^p where p must be a number (not an expression).

```c
Enter an expression: 2^2
4

Enter an expression: 4^2
16

Enter an expression: 4^(2 + 1)
// Error, p must be a number

Enter an expression: 4^2+1 // Corresponds to (4^2) + 1
17
```

#### Square roots

Square roots are supported in the format √n where n must be a non-negative number (not an expression).

```c
Enter an expression: √9
3

Enter an expression: √-9
// Error, n must be non-negative

Enter an expression: √(9 + 9) //
// Error, n must be a number

Enter an expression: √9+9 // Corresponds to (√9) + 9
12
```

### Variables

The program supports creating variables and assigning values to them. When a variable is assigned the result of an expression, the result isn't printed in the terminal, but instead stored into the variable.

```c
Enter an expression: x = 10
// Nothing is printed in the terminal
```

Once initialized, a variable can be reused in any expression, at a place where a number would be used. Thus, a variable can be used in an expression that defines another variable, or even in an expression that redefines itself.

```c
Enter an expression: x = 10

Enter an expression: x^2
100

Enter an expression: y = x

Enter an expression: x = x^2

Enter an expression: x
100

Enter an expression: y
10
```

A variable can be deleted by assigning an empty expression to it.

```c
Enter an expression: x = 10

Enter an expression: x
10

Enter an expression: x =
// x deleted

Enter an expression: x
// Error, x isn't defined
```

### Precedence

Operators precedence is respected by the calculator.

Powers and square roots aren't affected by the operators around them.

```c
Enter an expression: √9 * 3 // Equals (√9) * 3
9

Enter an expression: 1 + 2^2 + 1 // Equals 1 + (2^2) + 1
6
```

Multiplications and divisions are computed before additions and subtractions.

```c
Enter an expresssion: 1 + 2 * 3 // Equals 1 + (2 * 3)
7

Enter an expression: 3 - 3 * 1 + 3 // Equals 3 - (3 * 1) + 3
3
```

#### Brackets

Brackets can be used to give higher precedence to some operations.

```c
Enter an expresssion: (1 + 2) * 3
9

Enter an expression: (3 - 3) * (1 + 3)
0
```

As powers and square roots must be numbers (i.e. not expressions), brackets can't be used around them.

```c
Enter an expression: 3^(2 + 1)
// Error, (2 + 1) is an expression.

Enter an expression: √(2 + 1)
// Error, (2 + 1) is an expression.
```

## Contributing

If you find any issue while using the program or want to contribute, please <a href="https://github.com/NestorNebula/ccalculator/issues">open an issue</a>.

## Acknoledgements

- [GoogleTest](https://github.com/google/googletest)
- [vcpkg](https://vcpkg.io/)

## License

[![MIT License](https://img.shields.io/badge/License-MIT-darkcyan.svg?style=for-the-badge)](https://github.com/NestorNebula/ccalculator/blob/main/LICENSE)

© Noa Houssier - 2025

<p align='right'>(<a href='#top'>go back to the top</a>)</p>
