	
/* mini golf program
 *    will take in scores from 2 players
 *    */

	#include <iostream> /* input-output stream */
	#include <vector> /* vector is the c++ equivalent to arrayLists */

	using namespace std;
	
	void ask_for_names() {
		cout << "Please enter your name: ";
	}
	
	int sum_scores(vector <int> my_scores) {
		int final = 0;
		for (int i = 0; i < my_scores.size(); i++) {
			final += my_scores[i];
	}
		return final;
	}

	int main() {
	string name1, name2;
	int num_of_holes = 3;
	int p1holes = 0;
	int p2holes = 0;	// final scores for each player
	int data;
	int playerNum; // # of players

	vector <int> player1holes; // vectors to store each hole's score
	vector <int> player2holes;
	// note: instead of .get() with java, it is .at() in c++
	// note: instead of .add() with java, it is .push_back() in c++
	/*	This block of code shows the .size(), .at(), & .push_back() functions
	cout << "The vector is size " <<  player1holes.size() << endl;
	player1holes.push_back(5);
	cout << "The score for Player 1's hole 1 was: " << player1holes[0] << endl;
	cout << "The score for Player 1's hole 1 was: " << player1holes.at(0) << endl;
	cout << "The vector is size " << player1holes.size() << endl;
	player1holes.clear();
	cout << "Clearing the vector, it's now size: " << player1holes.size() << endl;
	*/

		/* Read in player names */
	ask_for_names();
	cin >> name1;
	cout << "You entered: " << name1 << endl;

	ask_for_names();
	cin >> name2;

		 /* count scores */
	 
	for (int i = 0; i < num_of_holes; i++) {
	
		cout << "Please enter " << name1 << "'s score for hole" << i + 1 << ": ";
		cin >> data; // equivalent to using scanner in java data = scan.nextInt();
		player1holes.push_back(data);
	
		cout << "Please enter " << name2 << "'s score for hole" << i + 1 << ": ";
		cin >> data;
		player2holes.push_back(data);	 // p2holes += data;
	 }

		// Calculate the final score
	p1holes = sum_scores(player1holes); // just need to type the vector's name, no brackets
	p2holes = sum_scores(player2holes);

	/* for loop to calculate final score
	for (int i = 0; i < num_of_holes; i++) { // can use player1holes.size() as limiter, but, bad programming
		p1holes += player1holes[i];
		p2holes += player2holes[i];
	} */
	 /* Reveal the winner of the game */
	cout << "Player 1 (" << name1 << ") scored a " << p1holes << "." << endl;
	cout << "Player 2 (" << name2 << ") scored a " << p2holes << "." << endl;
	
	
	if (p1holes < p2holes) {
		 cout << "Congrats " << name1 << " - you won the game!" << endl;
	}
	 else if (p1holes == p2holes) {
		 cout << "Tied game!" << endl;
}
	 else {
		 cout << "Congrats " << name2 << " - you won the game!" << endl;
	}
}
