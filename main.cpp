#include <iostream>
#include <string>
#include <memory>  // For std::shared_ptr
#include "bot.h"   // Include the Bot header file
#include "server.h" // Include the Server header file
#include "avl.h" // Include the AVLTree header file (if needed)
#include "linkedlist.h" // Include the LinkedList header file (if needed)

using namespace std;

int main() {
    cout << "Server is starting..." << endl;
    cout << "Server successfully started." << endl;

    Server server;

    int choice;
    while (true) {
        cout << "\nMenu:\n"
             << "1. Add Bot\n"
             << "2. Remove Bot\n"
             << "3. Get Data\n"
             << "4. Send Command\n"
             << "   1. Specific Bot\n"
             << "   2. All Bots\n"
             << "5. Display Bots\n"
             << "6. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string location;
            cout << "Enter Bot ID: ";
            cin >> id;
            cout << "Enter Bot Location: ";
            cin >> location;
            auto bot = make_shared<Bot>(id, location);
            server.addBot(bot);
        } else if (choice == 2) {
            int id;
            cout << "Enter Bot ID to remove: ";
            cin >> id;
            server.removeBot(id);
        } else if (choice == 3) {
            server.fetchDataFromAllBots();
        } else if (choice == 4) {
            int subChoice;
            cout << "1. Send Command to Specific Bot\n"
                 << "2. Send Command to All Bots\n"
                 << "Enter your choice: ";
            cin >> subChoice;
            string command;

            if (subChoice == 1) {
                int id;
                cout << "Enter Bot ID: ";
                cin >> id;
                cout << "Enter Command: ";
                cin.ignore();
                getline(cin, command);

                auto bot = make_shared<Bot>(id, "");
                server.sendCommandToBot(bot, command);
            } else if (subChoice == 2) {
                cout << "Enter Command: ";
                cin.ignore();
                getline(cin, command);

                server.sendCommandToAll(command);
            } else {
                cout << "Invalid choice." << endl;
            }
        } else if (choice == 5) {
            server.displayAllBots();
        } else if (choice == 6) {
            break;
        } else {
            cout << "Invalid choice." << endl;
        }
    }

    cout << "Server is shutting down..." << endl;
    cout << "Server successfully shut down." << endl;
    return 0;
}
