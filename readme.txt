Autonomous Bot Management System

A server-based application developed in C++ for managing and controlling a network of autonomous bots.
The system provides centralized control for multiple bots and supports bot management, command execution, status monitoring, data retrieval, and data logging.

Key Features
- Add and remove bots dynamically
- Send commands to individual bots
- Broadcast commands to all active bots
- Display active bots and their status and location
- Retrieve data collected by bots
- Maintain separate data files for individual bots
- Store commands for record-keeping and debugging
- Manage bot information using an AVL tree

System Architecture
The system uses a central server to communicate with multiple bots.

                    SERVER
                  /   |   \
                 /    |    \
              BOT 1  BOT 4  BOT 6
                |      |      |
              BOT 2  BOT 5  BOT 7
                |             |
              BOT 3          BOT 8

Data Structures
The project applies data structures and object-oriented programming concepts, including:
AVL Trees
Linked Lists
Classes and Objects
Dynamic Data Management
File Handling
The AVL tree is used for efficient organization and retrieval of bot-related information.

Command Management
The server supports commands directed to:
A specific bot
All active bots
Issued commands are stored for tracking and debugging.

Data Management
Each bot has its own dedicated data file. This allows information collected by individual bots to be stored separately without overwriting data from other bots.

Project Structure
.
├── main.cpp
├── Makefile
├── readme.txt
├── header/
│   ├── avl.h
│   ├── bot.h
│   ├── linkedlist.h
│   ├── server.h
│   └── utils.h
└── src/
    ├── avl.cpp
    ├── bot.cpp
    ├── linkedlist.cpp
    ├── server.cpp
    └── utils.cpp
Technologies
C++
Object-Oriented Programming
Data Structures
AVL Trees
Linked Lists
File Handling
Server-Based Bot Management
Project Documentation
The repository includes the project report describing the system architecture, implementation, outputs, and project contributions.

Project Focus
Server Communication → Bot Management → Command Execution → Data Collection → Data Logging → Efficient Data Organization
