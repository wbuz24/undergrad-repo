# LZ77 Compression Algorithm
I was assigned LZ77 compression for my CS494 final presentation. This directory houses the experiment that I presented for my presentation in which I implement LZ77 in c and expressed, in jgraph, the runtime efficiency and compression rate for various file sizes.

```
./bin/LZ77 search_size window_size input.txt output.txt
```

# Shrek
I decided to use the script from Shrek the movie, as a .txt file as my experiment on my implementation of LZ77. 

You can use the .txt file generator to generate a file into the data/ directory with a specified file size on the command line. 

```
./bin/shrek_gen n shrek/input.txt
```

Note: Since I quickly wrote it for this project, it is hard coded to extract data from the shrek folder.
