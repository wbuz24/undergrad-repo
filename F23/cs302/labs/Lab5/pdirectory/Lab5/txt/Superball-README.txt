Superball.jar - README

Alexander Teepe
1/2/2016

Copyright: none... (Enjoy!)

Superball game on which this player is based: 
http://web.eecs.utk.edu/~plank/plank/classes/cs302/Labs/Lab5/

Download to the player: 
https://drive.google.com/file/d/0B4rzPrfwFCsKX3VacmctTjdneVU/view?usp=sharing

Contents:
1. Installation
2. Playing the game
3. Testing your sb-play lab
4. Getting sb-play to work with the Superball player
5. sb-play path names
6. If sb-play crashes...

1. Installation:

  In order to run this Superball player, you must have the latest version of Java 
  installed on your machine.

  Windows:
    
    Install Java directly from https://www.java.com/en/download/
    The installation should be very straightforward, and afterwards
    you should be able to simply double click the Superball.jar file
    and it will run automatically.

  Mac:

    I do not own a Mac, so I was not able to test it, sorry :(
    Although everything in the player uses the standard Java libraries
    and should be 100% multiplatform.

  Linux (Ubuntu):

    The Java installation on Linux is a bit trickier, though I was able to 
    install a fresh installation of Ubuntu on a spare hard drive to
    confirm that it works.

    To install Java, go to the Java website and select the right version
    for your Linux distribution. It will download a .tar or .gz file, which you will
    have to unpack using the terminal. Navigate to your downloads folder using the
    terminal to find where it was saved (i.e. "cd ~/Downloads/"). Unpack the files
    using "tar zxvf jre-8u66-linux-x64.tar.gz" where the third argument is the filename
    of the java package (may change depending which version you choose). This will
    put the Java installation folder in the current directory.

    Now, assuming both the Java installation directory and the Superball.jar files are 
    located in your Downloads folder, you run Superball using the command line. From 
    the termainal (in your Downloads directory), type 
    "./jre-8u66-x64/bin/java -jar ./Superball.jar".
    The first argument navigates to the Java executable, the -jar argument says to
    run an executable .jar file, and ./Superball.jar is just the path to the jar 
    file to open. The superball player window will then open.

2. Playing the game:

  When you first open the player, it will start a new game, with 5 tiles spawned on the 
  board. The board is the 8 x 10 grid of buttons on the left. The column to the right
  of the board keeps track of your current score and the number of empty tiles remaining,
  and has buttons to let you score a set, reset the game, or let your sb-play program
  (from Lab 5) make a "guess" move for you.

  Swapping/Scoring:

    When you click a tile (button), that tile becomes selected (there is no visual confirmation
    of this, sorry). Once a tile is selected, you can click another valid tile to swap those
    two tiles. Or you can select a goal cell and click "Score" to score the set on that goal cell 
    (if possible). If you click the same tile twice, click an empty tile, or try to score an 
    invalid set, it will deselect the currently selected tile.

    If you make a swap, 5 new tiles will randomly spawn on the board. If there are fewer than
    5 empty tiles left when it tries to spawn 5 new tiles, it's game over.

    If you score a valid set (5+ tiles connected to a goal cell), it will remove that set, add
    the value of that set to your score, and spawn 3 more tiles on board.

  Reset:

    At any point, whether after a Game Over or during the middle of a game, you can hit the
    Reset button to clear the board, set the score back to 0, and start a new game.

3. Testing your sb-play lab:

  Since the purpose of the Superball lab is to write a sb-play program that can make smart
  moves and score high on Superball, it would be beneficial to see what exactly your program
  is doing. Fortunately, this Superball player is designed to work with the exact same sb-play
  program you have to write for the lab, and it has much more user friendly graphics than the 
  terminal for seeing what's going on.

  By pressing the "Guess" button, the player will locate your sb-play lab (using the file path 
  in the text box below) to pass sb-play the current game board, and then read in what move it
  makes, and then performs that move. The exact output of the program is listed in the log
  at the bottom on the player window. To better visualize what move sb-play made, if a swap
  was made, both of the swapped tiles will contain a large "X" on them. If it scored a tile,
  the tile that was scored will contain a large "X" on it.

4. Getting sb-play to work with the Superball player:

  If wrote and compiled your sb-play program on the lab computers, and want to use it with the
  Superball player on your personal computer, then you will have to recompile your sb-play 
  program from source on your personal computer. You might not have to recompile if your 
  personal computer is also running linux like the lab machines, but if you have Windows or 
  a Mac, then you will definitely have to recompile it.

5. sb-play path names:

  The textbox with the default text "./sb-play.exe" is the path to your sb-play executable.
  By default, it asumes you use the name sb-play.exe and the program is located in the same
  directory as Superball.jar. However, you can name it whatever you like, or switch between
  multiple different players, i.e. sb-play1, sb-play2, sb-play3, etc. You can also drop the
  .exe extension and use whatever extension name your OS uses. 

  If you wanted, you could also use aboslute path names like "C:/Users/Alex/Desktop/sb-play.exe"
  if you really wanted to, or stick to relative paths with the "./sb-play.exe" format.
    

6. If sb-play crashes...:

  If you try to test your sb-play program using the "Guess" button and it can't find the program,
  or it gives incorrect output, an error will be printed in the logging error at the bottom of
  the window.

  However, if the player freezes entirely, it could be an infinite loop in your program, OR the program
  exists, but gives an error when you try to run it. This could be due to not having the proper
  c++ redistributable packages installed, side-by-side errors, or a bunch of other stuff I don't
  understand. For example, if you compile sb-play using visual studio 2015, and then copy the 
  executable to another computer and try to run it, it may say something like, missing MSVC .dll 
  files or something or another.

  If you want to know the exact error, you will have to run sb-play yourself from the command line.
  Just run it as you would from the terminal, give it an arbitrary board, and check what errors pop up.