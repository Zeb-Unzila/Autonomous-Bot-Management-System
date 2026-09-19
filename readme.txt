---------------------------Robot Management System---------------------------

Introduction:

The project is a server-based application designed to manage and control a network of bots. 
The server allows users to add and remove bots, send commands to control them, and retrieve data from them. 
This system facilitates seamless interaction with multiple bots, making it ideal for use cases that require 
autonomous operations or monitoring across a fleet of devices.

Purpose:

The primary purpose of this project is to provide a robust framework for managing bots and collecting data from 
them in a controlled environment. It allows for dynamic bot management, enabling users to:

    1. Add and Remove Bots: The server can easily handle the addition and removal of bots, giving flexibility in
    managing the bot network.
    2. Send Commands: Users can send commands to specific bots or broadcast commands to all active bots.
    This feature provides central control for executing instructions remotely.
    3. Display Active Bots: The system provides an overview of all active bots, showing their current status and location,
    ensuring users can keep track of their operations.
    4. Request Data: At any point, users can request the data collected by the bots, such as information on the 
    terrain or environment the bots are interacting with.
    5. Store Commands: All commands issued to the bots are logged, with individual and combined commands being stored
    in separate files for record-keeping and debugging purposes.
    6. Unique Data Files per Bot: Each bot has its own dedicated data file that logs specific information related to 
    that bot's activities, ensuring that no data is lost or overwritten.

This project is designed to provide a comprehensive tool for managing autonomous bots, with an emphasis 
on control, tracking, and data management.

Run Commands:

1. Open Terminal
2. Write the following commands:
    - mingw32-make
    - ./server

Functionality:

    1. You can add bots and remove bots
    2. Send commands to control bots 
        - Commands can be sent to individual or all the bots
    3. Information of all active bots can be displayed.
    4. Current data collected by bots can be requested at any point in time.
        - It returns what terrain bot has found.
    5. Individual commands and Combined Commands are stored in their respected file
    6. Each bot has its own unique data file