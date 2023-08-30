// Will Buziak
// CS302
// Lab 1
// Music Library

#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
using namespace std;

class Song { 
  public:
    string title;
    int time;
    int track;
};

class Album {
  public:
    map <int, Song *> songs;
    string name;
    int time;
};

class Artist {
  public:
    map <string, Album *> albums;
    string name;
    int time;
    int nsongs;
};

string commas(string word) {
  size_t i = 0;
  for (i = 0; i < word.size(); i++) {
    if (word[i] == '_') word[i] = ' ';
  }
  return word;
}


int main(int argc, char **argv) {
  ifstream fin;
  istringstream ss;
  string song, t, artist, album, genre, num;
  size_t tindex; // time index
  int mins, sec;
  map <int, Song *>::iterator sit; // song map iterator
  Artist *artptr; // album map iterator


  if (argc == 2) {
    string filename = argv[1];
    fin.open(filename);
    if (!fin.fail()) {
      while (fin >> song >> t >> artist >> album >> genre >> num) {
        if (t.find(':') != string::npos) { // convert time to an integer
          tindex = t.find(':');
          mins = stoi(t.substr(0, tindex));
          sec = stoi(t.substr(tindex + 1, t.size()));
        } 
        
        song = commas(song);
        artist = commas(artist);
        album = commas(album);
        genre = commas(genre);

        artptr = Artist::albums.find(artist);
        
        if (Artist->albums.find(artist) != Artist::albums->end()) { // song is found
          cout << "Old Artist: " << artist << endl;
        }
        else { // otherwise, place it in the map
          cout << "New Artist: " << artist << endl;
        }
        // if (Songs.find())
        //cout << genre << endl;
      }
    }
    else {
      cout << "File not found\n";
      return 0;

    }


  } else cout << "Usage: ./lib_info filename\n";
  
}
