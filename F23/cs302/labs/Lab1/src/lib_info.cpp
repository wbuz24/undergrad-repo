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
  map <string, Artist *>::iterator arit; // map iterator
  map <string, Album *>::iterator alit; // map iterator
  map <int, Song *>::iterator sit; // map iterator

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
        genre = commas(genre);

        if (artists.find(artist) == artists.end()) { // artist is not found
          Artist *a = new Artist;
          a->name = artist;
          a->time = 0;
          a->nsongs = 1;
          artists.insert(make_pair(artist, a)); // make a new artist
        }

        if (artists.find(artist)->second->albums.find(album) == artists.find(artist)->second->albums.end()) { // cannot find the album
          Album *na = new Album; // create a new album
          na->name = album;
          na->time = 0;
          artists.find(artist)->second->albums.insert(make_pair(album, na)); // insert the album into the artist
        }

        Song *ns = new Song;
        ns->title = song; // create a new song
        ns->time = mins*60 + sec;
        ns->track = num;
        artists.find(artist)->second->albums.find(album)->second->songs.insert(make_pair(num, ns)); // insert the song into the album
        artists.find(artist)->second->albums.find(album)->second->time += (mins*60 + sec); // increment the time
      }

      for (arit = artists.begin(); arit != artists.end(); arit++) { // loop through artists
        cout << arit->first << endl; // print the artist
        for (alit = arit->second->albums.begin(); alit != arit->second->albums.end(); alit++) {
           cout << "        " << alit->first << endl; // print the album
        }
          for (sit = alit->second->songs.begin(); sit != alit->second->songs.end(); sit++) {
           cout << "                 " << sit->second->track << ". " << sit->second->title << ": " << sit->second->time << endl; // print the songs of the album
            
        }
      }
    }
    else {
      cout << "File not found\n";
      return 0;

    }
  } else cout << "Usage: ./lib_info filename\n";
}
