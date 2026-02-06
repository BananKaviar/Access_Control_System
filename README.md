# Access Control System – IoT & Embedded Systems Project

## Description
This project was developed as part of the **IoT and Embedded Systems Development program.**

The assignment was a learning exercise focused on practicing **C programming** concepts commonly used in embedded and IoT systems.

***The program simulates a card-based door access control system where an administrator manages employee access rights based on time shifts.***

## System Overview

### Each access card in the system contains:
<ol>
  <li>A card number</li>
  <li>A creation date</li>
  <li>An access status (enabled or disabled)</li>
  <li>A time-based access rule (time shift)</li>
</ol>


### The system includes:
<ul>
  <li>A set of predefined cards available when the program starts</li>
  <li>Additional cards that can be added or removed dynamically by the administrator during runtime</li>
</ul>


#### Access is granted or denied depending on:
<ul>
  <li>Whether the card has access enabled</li>
  <li>Whether the current time matches the card’s assigned time shift</li>
</ul>


## Time Shift Logic
#### Time-based access is implemented using an enum with the following values:
<ul>
<li>SHIFT_MORNING – 06:00 to 14:00</li>
<li>SHIFT_AFTERNOON – 14:00 to 22:00</li>
<li>SHIFT_EVENING – 22:00 to 06:00</li>
<li>SHIFT_ALWAYS – 24/7 access</li>
<li>ACCESS_NONE – no access</li>
</ul>

When access is removed from a card, the system automatically assigns ACCESS_NONE.
In this case, the user is not asked to select a time shift, ensuring a logical and consistent access state.

## Functionality
The program provides an admin menu that allows the administrator to:

#### List all registered cards
<ul>
<li>Add new cards during runtime</li>
<li>Remove existing cards</li>
<li>Enable or disable card access</li>
<li>Assign time-based access rules</li>
<li>Simulate door access using visual feedback (green/red indication)</li>
<li>User input is validated to prevent invalid data from being stored.</li>
</ul>

## Technical Structure

### The project is written in C and organized using multiple source and header files to separate responsibilities, including:
<ul>
<li>Main program flow and menu handling</li>
<li>Card data structures and enums</li>
<li>Access logic and time-based checks</li>
<li>Safe user input handling</li>
<li>Both static and dynamic memory allocation are used to manage card data.</li>
</ul>

## Build and Run
The project is compiled using gcc and a provided Makefile.

### To build the project:
```bash
make

```

### To run the program:
If you’re in Git Bash / MSYS2
```bash
./main.exe
```
If you’re in PowerShell / CMD
```bash
.\main.exe
```
## Purpose
This application is a simplified simulation created for educational purposes.
It is not intended for real-world security use, but to *demonstrate understanding of programming concepts relevant to IoT and embedded systems development and mainly to understand the complexities of programming in C.*

## Author
Developed as part of the IoT and Embedded Systems Development program.
>This is the first creating a ReadMe file and also used this as an oppurtunity to pratice Markdown. 
