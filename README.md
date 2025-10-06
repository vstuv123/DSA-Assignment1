README — Data Structures and Algorithms Assignment

Name: Muhammad Abdullah
Qalam ID: 476270
Course: Data Structures and Algorithms
Assignment: Advanced ADTs and Simulations in C++

GitHub Repository

https://github.com/vstuv123/DSA-Assignment1

Problem 1 – Polynomial ADT

Approach

The Polynomial ADT was implemented using a Linked List–based structure to efficiently store terms and perform algebraic operations such as addition, multiplication, and differentiation.
Each node of the list represents one term (coefficient, exponent), and the list remains sorted in descending order of exponents.

The key operations:

insertTerm() — Inserts or combines terms with the same exponent and removes zero-coefficient terms.

add() — Iteratively merges two polynomials by comparing and combining exponents.

multiply() — Uses nested iteration to multiply every term of one polynomial with another.

derivative() — Applies the derivative rule n * aₙxⁿ⁻¹ on each term.

toString() — Returns a human-readable format such as 3x^4 + 2x^2 - x + 5.

Challenges Faced

This problem required handling abstract class constraints from the provided header file.
Initially, it was difficult to implement all polynomial operations because the header file only contained pure virtual function declarations, which meant no internal data handling was allowed directly in the base class.

The correct and most efficient solution was achieved by applying Object-Oriented Programming (OOP) principles — particularly inheritance and virtual functions.
By ensuring that each member function in the header file was declared with the virtual keyword, the derived class was able to override and define the required logic for insertion, addition, multiplication, and differentiation.

This approach allowed dynamic binding between base and derived objects, enabling correct and complete functionality without violating abstraction.
The polynomial operations now execute successfully, and outputs for all operations (add, multiply, derivative) display correctly.
This part of the assignment helped in understanding how polymorphism and virtual dispatch play a critical role in extensible ADT design and function overriding in C++.

Problem 2 – Text Editor Simulation
Approach

The text editor was designed to simulate cursor movement and character editing.
It efficiently manages text operations using a two-stack structure or doubly linked list, which allows insertion and deletion at the cursor position in constant time.

Each operation (insert, delete, move left/right) updates the cursor’s position accordingly, while the display() function shows the text with a | character representing the cursor (e.g., ab|c).
This closely models how real-world text editors handle typing, backspace, and cursor navigation.

Challenges Faced

This task worked smoothly without requiring any modification to the provided header file.
The main challenge was maintaining the correct cursor position during consecutive insertions and deletions.
Initially, handling edge cases like deleting at position 0 or moving the cursor beyond text boundaries required careful checks.
After refining these conditions, the editor behaved exactly as intended.
This task reinforced understanding of stack-based data structures and their efficiency in managing editable text buffers.

Problem 3 – UNO Card Game Simulation
Approach

The UNO simulation models a two-to-four-player card game using object-oriented design.
Key components include:

Deck Management: Implemented with vectors, using <random> for shuffling with a fixed seed for reproducibility.

Player Hands: Each player stores cards in a vector and plays based on matching color, value, or action type.

Game Logic: Handles direction (clockwise/counter-clockwise), skips, reverses, and draw-two actions.

Game State: Displays turn information, top card, direction, and remaining cards per player.

This implementation demonstrates the use of data structures and algorithms to simulate real-world systems and maintain consistent game state across turns.

Challenges Faced

The UNO simulation was implemented successfully without any changes to the header file.
The primary challenge was handling the game flow logic, including turn switching, direction reversal, and skip/draw-two effects.
Ensuring that the correct player’s turn executed under all conditions required careful control of indices and direction tracking.
Another challenge was designing a readable game state output that clearly displayed all information at each step.
Overall, this task strengthened the understanding of vector-based data handling, control flow, and state management in C++ simulations.

Overall Learning

This assignment reinforced the following key concepts:

Understanding and application of Abstract Data Types (ADTs) in practical scenarios.

Use of Linked Lists, Stacks, Vectors, and OOP principles for problem-solving.

Realization of how virtual functions and inheritance enable flexibility in program design.

Importance of data abstraction and modular implementation in large-scale systems.

Deepened understanding of debugging, object relationships, and data encapsulation in C++.

Conclusion:
The assignment demonstrated the power of C++ OOP principles in structuring and extending abstract classes.
While the first task required the correct use of virtual to enable full functionality, the other tasks were successfully implemented as per the provided structure without modifications.
Overall, it was an insightful experience in building robust, extensible, and well-organized programs using advanced data structures and algorithms.
