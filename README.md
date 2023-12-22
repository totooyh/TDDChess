#TODO
- Pawn ampassent
- Pawn promotion
- Castling
- Check-Mate
- ChessGame per se
- ChessGame interface
- ChessBot


Chess Game in C++ with Test-Driven Development (TDD)
This project is a simple implementation of a Chess game in C++ using the principles of Test-Driven Development (TDD). The primary goal is to showcase the differences between object-oriented programming (OOP) in Smalltalk and C++. The project structure follows best practices for C++ development, with an emphasis on unit testing.

Project Structure
The project is organized into the following directories:

src: Contains the source code for the Chess game.

test: Houses the unit tests for the Chess game using a TDD approach.
Building and Running
To build the project, you can use a C++ compiler such as g++:

bash
Copy code
g++ -o chess_game src/*.cpp
To run the compiled executable:

bash
Copy code
./chess_game
Dependencies
This project uses Google Test as the testing framework. Make sure to have it installed or included in your project.

Test-Driven Development
The development process follows TDD, where tests are written before the actual implementation. Tests are placed in the test directory and can be run using the following commands:

bash
Copy code
# Compile and run tests
g++ -o test_runner tests/*.cpp -lgtest -lgtest_main -pthread
./test_runner
Object-Oriented Programming
The Chess game is designed using classes and objects, adhering to OOP principles in C++. Each chess piece is represented by a class, and interactions are managed through well-defined interfaces.

Differences from Smalltalk
While Smalltalk and C++ both support OOP, there are notable differences. C++ uses a static type system, whereas Smalltalk relies on dynamic typing, however with the use of smartpointers we can mimic the dynamic typing of SmallTalk. C++ employs header files for declarations and source files for implementations, which is different from Smalltalk's unified image.

Contributing
Feel free to contribute by opening issues or submitting pull requests. Follow the CONTRIBUTING.md guidelines for details.

License
This project is licensed under the MIT License - see the LICENSE file for details.

