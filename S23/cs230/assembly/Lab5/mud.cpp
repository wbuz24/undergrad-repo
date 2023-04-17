// mud.cpp
// Template file for the mud assignment.
// (c) Stephen Marz
// 11-Jan-2023
// COSC230 - University of Tennessee [Knoxville]
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;

// -1 will signal that there is no valid exit in a given
// cardinal direction.
#define NO_EXIT    (-1)

// Cardinal directions. The exits[4] array uses these
// as indices to keep the direction correct.
#define EXIT_NORTH (0)
#define EXIT_EAST  (1)
#define EXIT_SOUTH (2)
#define EXIT_WEST  (3)

struct Room {
    // The room structure only has three instance fields.
    char *title;
    char *description;
    int exits[4];

    // Construct a new room by nulling out the title and
    // description. Furthermore, the exits are all set to -1.
    Room() {
        title = nullptr;
        description = nullptr;
        memset(exits, -1, sizeof(exits));
    }

    // Since we use strdup to duplicate the title and description,
    // they need to be freed using old C-style free() instead of
    // delete.
    ~Room() {
        free(title);
        free(description);
    }
};

// Make sure you export the following function labels before you start.
// Recall you can export using the .global directive.
extern "C" {
    void look_at_room(const Room *r);
    void look_at_all_rooms(const Room *rooms, int num_rooms);
    Room *move_to(Room *rooms, const Room *current, int direction);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <rooms file>\n";
        return -1;
    }

    ifstream fin;
    string text;
    int num_rooms = 0;
    Room *rooms;
    int i;
    Room *in_room;


    fin.open(argv[1]);
    if (!fin) {
        perror(argv[1]);
        return -1;
    }

    // The tilde ~ is the separator of three fields per room.
    // So, we can determine the number of rooms by 
    while (getline(fin, text)) {
        if (text == "~") {
            num_rooms += 1;
        }
    }

    num_rooms /= 3;

    fin.clear();
    fin.seekg(0);
    rooms = new Room [ num_rooms ];

    for (i = 0;i < num_rooms;i++) {
        // Alias r to be the room we're looking at for this iteration
        Room &r = rooms[i];

        if (!getline(fin, text, '~')) {
            break;
        }
        // Since we used ~ as the delimiter, the newline character
        // is right after ~, so ignore it.
        fin.ignore();
        // Use substr to remove the trailing \n character.
        r.title = strdup(text.substr(0, text.length() - 1).c_str());

        if (!getline(fin, text, '~')) {
            break;
        }
        fin.ignore();
        r.description = strdup(text.substr(0, text.length() - 1).c_str());

        if (!getline(fin, text, '~')) {
            break;
        }
        fin.ignore();

        // Exits are specified by <direction room_num> one line
        // at a time. There may be 0 to 4 exits.
        istringstream sin(text);
        string direction;
        int room_no;

        while (sin >> direction >> room_no) {
            int exdir;
            if (direction == "n") {
                exdir = EXIT_NORTH;
            }
            else if (direction == "e") {
                exdir = EXIT_EAST;
            }
            else if (direction == "s") {
                exdir = EXIT_SOUTH;
            }
            else if (direction == "w") {
                exdir = EXIT_WEST;
            }
            else {
                cout << "Invalid direction '" << direction << "' for room #" << (i+1) << '\n';
                break;
            }
            r.exits[exdir] = room_no;
        } 
    }

    fin.close();

    // Put the player in the first room.
    in_room = rooms + 0;

    look_at_room(in_room);

    for (;;) {
        string command;
        cout << "\n> ";
        if (!getline(cin, command)) {
            break;
        }
        else if (command == "l" || command == "look") {
            look_at_room(in_room);
        }
        else if (command == "n") {
            Room *to = move_to(rooms, in_room, EXIT_NORTH);
            if (to == nullptr) {
                cout << "You can't go north!\n";
            }
            else {
                in_room = to;
                cout << "You moved north.\n";
            }
        }
        else if (command == "e") {
            Room *to = move_to(rooms, in_room, EXIT_EAST);
            if (to == nullptr) {
                cout << "You can't go east!\n";
            }
            else {
                in_room = to;
                cout << "You moved east.\n";
            }
        }
        else if (command == "s") {
            Room *to = move_to(rooms, in_room, EXIT_SOUTH);
            if (to == nullptr) {
                cout << "You can't go south!\n";
            }
            else {
                in_room = to;
                cout << "You moved south.\n";
            }
        }
        else if (command == "w") {
            Room *to = move_to(rooms, in_room, EXIT_WEST);
            if (to == nullptr) {
                cout << "You can't go west!\n";
            }
            else {
                in_room = to;
                cout << "You moved west.\n";
            }
        }
        else if (command == "lall") {
            look_at_all_rooms(rooms, num_rooms);
        }
        else if (command == "quit") {
            break;
        }
        else if (command != "") {
            cout << "Unknown command\n";
        }
    }
    cout << "Goodbye!\n";

    delete [] rooms;

    return 0;
}


