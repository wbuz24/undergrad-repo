/* Header file to define the PGM class, that lets you manipulate PGM files.
   The files themselves are simply stored in a vector of vectors of ints.
   All of the methods return true if they succeed and false if they fail.

   Write() needs to produce files in a specific format:

      - P2 on its own line, no spaces.
      - cols rows on the next line, separated by a space, no additional spaces
      - 255 on its own line, no spaces.
      - Then the pixels: 20 pixels per line, one space between pixels, no additional spaces.
      - You don't print additional newlines at the end of each row of pixels -- just 
        start the next row of pixels.
      - The last line is the only one that can have fewer than 20 pixels.
      - To give an example, if the picture has two rows and 11 columns, and all of the
        pixels have values of 5, then the pixels will look like:

5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5
5 5
 */

#pragma once

#include <vector>
#include <string>

class Pgm {
  public:
    bool Read(const std::string &file);           // Reads a PGM file 
    bool Write(const std::string &file) const;    // Writes a PGM file
    bool Create(size_t r, size_t c, size_t pv);   // Creates a rxc PGM with the given pixel value
    bool Clockwise();                             // Rotates 90 degrees clockwise
    bool Cclockwise();                            // Rotates 90 degrees counterclockwise
    bool Pad(size_t w, size_t pv);                // Adds a border of w pixels with the given value
    bool Panel(size_t r, size_t c);               // Makes rxc copies of the PGM
    bool Crop(size_t r,    size_t c,
              size_t rows, size_t cols);         // Crops from r:c to (r+rows):(c+cols)
  protected:
    std::vector < std::vector <int> > Pixels;
};
