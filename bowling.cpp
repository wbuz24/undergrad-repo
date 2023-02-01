/* 
 * Will Buziak
 * wbuziak
 * 000510519
 * Bowling.cpp
 * score several players in bowling
 */

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector <string> players;
    vector <int> scores;
    vector <int> roll;
    int total;
    bool playing = 1, start_score = 0;
    string input;


    cout << "Enter a player's name (done for no more players): ";
    cin >> input;
    players.push_back(input);
    scores.push_back(0);
    int playindex = 0;

    // check if any players were input
    if (input == "done") {
        cout << "No players were entered." << endl;
        playing = 0;
    }
    
    // continue to score until user enters done
    while (playing) {

        // prompt for score & store values in a vector
        // roll vector tracks each score
        for (int i = 0; i < 9; i++) {
            int num, num2;
            int iter = i + 1;
            cout << "Enter score for frame " << iter << ", roll 1: ";
            cin >> num;
            // score regularly ( ask for 2 rolls per frame)
            if (num != 10) {
                cout << "Enter score for frame " << iter << ", roll 2: ";
                cin >> num2;
                roll.push_back(num);
                roll.push_back(num2);
            }
            
            // if strike, dont prompt for second roll
            else {
                roll.push_back(10);
                roll.push_back(0);
            }
        }

        // final three frames
        for (int i = 0; i < 3; i++) {
            int num;
            cout << "Enter score for frame 10, roll " << i + 1 << ": ";
            cin >> num;
            roll.push_back(num);
        }

        // score players
        for (int i = 0; i < roll.size() - 1; i++) {
            if (i % 2 == 0) { // if even
                if (roll[i] == 10) { // if strike
                    if (roll[i + 2] == 10) { // if next frame is strike
                        roll[i] = 10 + 10 + roll[i + 4];
                    }
                    else { // if next frame is not a strike
                        roll[i] = 10 + roll[i+2] + roll[i+3]; 
                    }
                }
            }

            // if spare
            else {
                int ten;
                ten = roll[i] + roll[i-1];
                if (ten == 10) {
                    roll[i] = roll[i] + roll[i + 1];
                }
            }

            // score each player
            scores[playindex] = scores[playindex] + roll[i];
        }

        roll.clear(); // clear contents of roll vector after scoring
        cout << "Enter a player's name (done for no more players): ";
        cin >> input;
        if (input != "done"){
            players.push_back(input);
            scores.push_back(0);
            playindex++;
        }
        else {
            playing = 0;
            start_score = 1;
        }

        // print scores
        while (start_score) { 

            // print final score & winner
            int max = scores[0], j = 0, k = 0, min = scores[0];
            for (int i = 0; i < players.size(); i++) {
                cout << players[i] << " scored " << scores[i] << "." << endl;
            }

            for (int i = 0; i < scores.size(); i++) {
                // find maximum
                if (scores[i] > max) {
                    j = i;
                    max = scores[i];
                }

                // if tie, lowest index wins
                if (scores[i] == scores[j]) {
                    if (i < j) {
                        j = 0;

                    }                 
                }

            }

            // find minimum
            for (int i = 0; i < scores.size(); i++) {
                if (scores[i] < min) {
                    k = i;
                    min = scores[i];

                }
            }

            // declare loser/winner
            cout << players[k] << " did the worst by scoring " << scores[k] << "." << endl;
            cout << players[j] << " won the game by scoring " << scores[j] << "." << endl; 

            start_score = 0;
        }
    }
}
