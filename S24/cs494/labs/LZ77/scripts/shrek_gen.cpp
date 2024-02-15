/* Will Buziak
 * CS494
 * Quick & hacky, generate files of designated size
 * */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main(int argc, char **argv) {
  long long n, i, j;
  string filename, line;
  vector <string> lines;
  ifstream fin;
  ofstream fout;
  char ofile[100], name[200];

  if (argc != 3) {
    printf("./bin/gen_txt kB file.txt\n");
    return 0;
  }

  n = atoi(argv[1]);
  filename = argv[2];

  /* Check the file */
  fin.open(filename);
  if (fin.fail()) {
    printf("%s failed\n", filename.c_str());
    return 0;
  }

  /* Check n */
  if (n <= 0) {
    printf("n must be greater than zero\n");
    return 0;
  }

  n = n * 1000;
  i = 0;
  /* Read file only as long as you read less than n bytes */
  while (getline(fin, line)) {
    lines.push_back(line);
    i += line.length();
    if (i > n) break;
  }

  /* Make output file, assumes data will be in shrek folder */
  sscanf(filename.c_str(), "shrek/%s.txt", ofile);
  sprintf(name, "data/%lld_%s", (n / 1000), ofile);
  fout.open(name);

  /* print n bytes of shrek */
  for (j = 0; j < (long long) lines.size(); j++) {
    fout << lines[j] << endl;
  }

  while (i < n) {
    for (j = 0; j < (long long) lines.size(); j++) {
      fout << lines[j] << endl;
      i+= lines[j].length();
      if (i > n) break;
    } 
  }

  return 1;
 

}
