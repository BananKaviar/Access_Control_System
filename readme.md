# Access Control System – IoT & Embedded Systems Project

## Description
This project was developed as part of the IoT and Embedded Systems Development program.
The assignment was a learning exercise focused on practicing C programming concepts commonly used in embedded and IoT systems.

The program simulates a card-based door access control system where an administrator manages employee access rights based on time shifts.

## System Overview
Each access card in the system contains:

A card number

A creation date

An access status (enabled or disabled)

A time-based access rule (time shift)

The system includes:

A set of predefined cards available when the program starts

Additional cards that can be added or removed dynamically by the administrator during runtime

Access is granted or denied depending on:

Whether the card has access enabled

Whether the current time matches the card’s assigned time shift

## Time Shift Logic
Time-based access is implemented using an enum with the following values:

SHIFT_MORNING – 06:00 to 14:00

SHIFT_AFTERNOON – 14:00 to 22:00

SHIFT_EVENING – 22:00 to 06:00

SHIFT_ALWAYS – 24/7 access

ACCESS_NONE – no access

When access is removed from a card, the system automatically assigns ACCESS_NONE.
In this case, the user is not asked to select a time shift, ensuring a logical and consistent access state.

## Functionality
The program provides an admin menu that allows the administrator to:

List all registered cards

Add new cards during runtime

Remove existing cards

Enable or disable card access

Assign time-based access rules

Simulate door access using visual feedback (green/red indication)

User input is validated to prevent invalid data from being stored.

## Technical Structure
The project is written in C and organized using multiple source and header files to separate responsibilities, including:

Main program flow and menu handling

Card data structures and enums

Access logic and time-based checks

Safe user input handling

Both static and dynamic memory allocation are used to manage card data.

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
It is not intended for real-world security use, but to demonstrate understanding of programming concepts relevant to IoT and embedded systems development.

## Author
Developed as part of the IoT and Embedded Systems Development program.
