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
  string song, t, artist, album, genre;
  size_t tindex; // time index
  int mins, sec, num;
  map <string, Artist *> artists; // map of artists
  map <string, Artist *>::iterator ait; // map iterator
  Song *ns = new Song;
  Artist *a = new Artist;
  Album *na = new Album;

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

        song = commas(song); // convert strings - remove _ for ' '
        artist = commas(artist);
        album = commas(album);
 
        ns->title = song; // create a new song
        ns->time = mins*60 + sec;
        ns->track = num;

        genre = commas(genre);

        if (artists.find(artist) == artists.end()) { // artist is found

          artists.insert(make_pair(artist, a));
        }

        if (a->albums.find(album) == a->albums.end()) {

          a->albums.insert(make_pair(album, na));
          na->name = album;
          na->time = 0;
        }
        
        na->songs.insert(make_pair(num, ns));


      }
    }
    else {
    cout << "File not found\n";
    return 0;

  }


  } else cout << "Usage: ./lib_info filename\n";

}
