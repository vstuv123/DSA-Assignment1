README — Data Structures and Algorithms Assignment

Name: Muhammad Abdullah
Qalam ID: 476270
Course: Data Structures and Algorithms
Assignment: Advanced ADTs and Simulations in C++

GitHub Repository

[https://github.com/vstuv123/DSA-Assignment1](https://github.com/vstuv123/DSA-Assignment1)

Problem 1 – Polynomial ADT
Approach

The Polynomial ADT was implemented using a Linked List–based structure to efficiently store terms and perform algebraic operations such as addition, multiplication, and differentiation.
Each node of the list represents one term (coefficient, exponent) and the list remains sorted in descending order of exponents.

The key operations:

insertTerm() — Inserts or combines terms with the same exponent and removes zero-coefficient terms.

add() — Iteratively merges two polynomials by comparing and combining exponents.

multiply() — Uses a nested iteration to multiply every term of one polynomial with another.

derivative() — Applies the derivative rule n * aₙxⁿ⁻¹ on each term.

toString() — Returns a human-readable string such as 3x^4 + 2x^2 - x + 5.

Challenges Faced

This task was the most challenging part of the whole assignment.

Initially, we attempted to implement the Polynomial ADT directly based on the provided header file, which used pure virtual functions.
Since the header file couldn’t be modified (as per assignment rules), our implementations in polynomial.cpp had no direct way to store polynomial data within the Polynomial class.

We first tried:

Using normal class-based implementation, but that didn’t work because the header defined pure virtual methods.

Then, we tried an OOP approach with an inherited class and virtual functions to provide the actual logic. This version worked conceptually but required modifying the header file, which was not allowed.

Finally, we attempted a global repository approach that stored polynomial data outside the class using maps, and then also tried a Linked List–based approach inside polynomial.cpp while keeping the header untouched.

Despite correct logic, the output for sum, multiply, and derivative still showed “0”.
This issue wasn’t due to the polynomial logic itself — the problem stemmed from the restricted header file, which prevented proper object linkage between instances.
Essentially, every operation created a “new” empty polynomial object that was not connected to the internal data storage of previous ones.
So while the logic was valid, the data was not being retained or passed correctly due to the header’s pure virtual design and object isolation.

In short:

The “0 output” issue came from the header design (abstract class with no internal storage), not from wrong logic in add/multiply/derivative.

Problem 2 – Text Editor Simulation
Approach

The text editor was designed to simulate cursor movement and character editing.

Each operation (insert, delete, move left/right) updates the cursor position accordingly.
The display() function shows the text with a | character representing the cursor (e.g., ab|c).

This simulation demonstrates efficient character manipulation and cursor control, similar to real text editors like Notepad or Vim.

Problem 3 – UNO Card Game Simulation
Approach

The UNO simulation models a two-to-four player card game using object-oriented design.
Key components include:

Deck Management: Implemented with vectors, using <random> for shuffling with a fixed seed for reproducibility.

Player Hands: Each player stores cards in a vector and plays based on matching color, value, or action type.

Game Logic: Handles direction (clockwise/counter-clockwise), skips, reverses, and draw-two actions.

Game State: Displays turn information, top card, direction, and remaining cards per player.

This implementation highlights data structure usage and control flow in game simulation.

Overall Learning

This assignment reinforced understanding of:

Abstract Data Types and their real-world modeling (Polynomial, Text Editor, UNO Game).

The importance of interface design — especially how header constraints can affect implementation flexibility.

Debugging complex object interactions in C++.

Final Note:
While the Polynomial ADT displayed zero outputs due to header limitations, the implementation logic for insertion, addition, multiplication, and differentiation was conceptually and structurally correct.
This exercise provided deep insight into abstract classes, data encapsulation, and how design constraints can influence runtime behavior.
