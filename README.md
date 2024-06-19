# Booking Service API

This project contains an API implementation for a demo booking service that manages movies, theaters, and seats.

## Compilation Instructions

To compile the code, follow these steps:

1. Ensure you have `g++` installed on your system.
2. Open a terminal.
3. Navigate to the directory containing the source files and the Makefile.
4. Run the following command to compile the code:

    make

5. The executable `cppchallenge` will be created upon successful compilation.

## Running the Program

To run the program, follow these steps:

1. After compiling the code, run the following command in the terminal:

    ./cppchallenge

2. The program will execute and provide a menu-driven interface to interact with the booking service API.

3. A telnet console listening on the port 8080 allow to access to a very simple CLIconsole
 binded to the server build on the demo


## Usage Instructions

- Use the menu options to view all movies, select a movie, view theaters for the selected movie, select a theater, show available seats, and book seats.
- Follow the on-screen instructions to navigate through the booking process.

## Cleaning Up

To clean up the intermediate files and the executable generated during compilation, run:

    make clean

