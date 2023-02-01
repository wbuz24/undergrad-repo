/* Multi-User Dungeons
 * CS 102
 * wbuziak
 * 000510519
 */

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


class rooms {
    public:
        string name;
        string descript;
        string direct;
        int nor = -4, eas = -4, wes = -4, sou = -4;
};

int main(int argc, char ** argv) {
    // open and read text file
    ifstream fin;
    ofstream fout;
    ostringstream sout;
    int roomNum = 0;
    string ifile = argv[1], line;
    fin.open(ifile);

    // count number of rooms
    while (getline(fin, line)) {
        if (line == "~"){
            roomNum++;
        }

    }

    fin.clear();
    fin.seekg(0); //resets getline without closing file

    // dynamically allocate room information
    int n = roomNum / 3;
    rooms *roomPtr = new rooms[n];
    int tildes = 0, iter = -1;

    // read through file again to store information
    while (getline(fin, line)) {
        if (line != "~"){
            if (tildes % 3 == 0){
                iter++;
                roomPtr[iter].name = line;
            }
            if (tildes % 3 == 1){
                roomPtr[iter].descript = line;
            }
            // build string stream to store index in direction
            if (tildes % 3 == 2){
                string a;
                int b;
                sout << line << "\n";
                istringstream sin(line);
                sin >> a >> b;  
                roomPtr[iter].direct = a;
                if (a == "n"){
                    roomPtr[iter].nor = b;
                }
                else if (a == "e"){
                    roomPtr[iter].eas = b;
                }
                else if (a == "w"){
                    roomPtr[iter].wes = b;
                }
                else if (a == "s"){
                    roomPtr[iter].sou = b;
                }
                sout.clear();
            }
        }
        else {
            tildes++;
        }
    } 

    fin.close();
    // begin game
    bool playing = 1;
    int index = 0;
    while (playing){
        char action;
        string exitString;
        cout << "> ";
        cin >> action;
        // concatenate string with direction if exit exists
        if (roomPtr[index].nor >= 0){
            exitString += "n ";
        }
        if (roomPtr[index].sou >= 0){
            exitString += "s ";
        }
        if (roomPtr[index].wes >= 0){
            exitString += "w ";
        }
        if (roomPtr[index].eas >= 0){
            exitString += "e ";
        }
        // switch action cases
        switch(action){
            case 'l':
                cout << roomPtr[index].name << endl << roomPtr[index].descript << endl;
                cout << "Exits: " << exitString << endl;
                break;
            case 'q':
                playing = 0;
                break;
            case 'n':
                if (roomPtr[index].nor < 0){
                    cout << "You can't go NORTH!" << endl;
                    break;
                }
                index = roomPtr[index].nor;
                cout << "You moved NORTH." << endl;
                break;
            case 'e':
                if (roomPtr[index].eas < 0){
                    cout << "You can't go EAST!" << endl;
                    break;
                }
                index = roomPtr[index].eas;
                cout << "You moved EAST." << endl;
                break;
            case 'w':
                if (roomPtr[index].wes < 0){
                    cout << "You can't go WEST!" << endl;
                    break;
                }
                index = roomPtr[index].wes;
                cout << "You moved WEST." << endl;
                break;
            case 's':
                if (roomPtr[index].sou < 0){
                    cout << "You can't go SOUTH!" << endl;
                    break;
                }
                index = roomPtr[index].sou;
                cout << "You moved SOUTH." << endl;
                break;
            default:
                break;
        }
    }
    delete[] roomPtr;
}
