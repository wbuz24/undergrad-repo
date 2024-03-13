# Jgraph lab
This lab was rather open ended, generate a jgraph that is "visually interesting".

I decided to do mine on my Professor, [Dr. Plank](https://web.eecs.utk.edu/~jplank/)'s infamous "Music of The Day". It was my hope that I could create a visual represntation of Dr. Plank's music taste. He often includes a description with a date, whether it be when the music piece was released, or the decade the artist was most active.

The format is inconsistent and largely written in stream-of-thought text. Therefore, to achieve my goal, I had to parse the entire file and write a program to find the dates and throw out all the extraneous details, numbers and irrelevant dates.

## Dependencies
This was entirely written in cpp and shell scripts and compiles with make, you only need gcc, a bash shell and jgraph of course.

 - gcc
 - make
 - bin/bash
 - jgraph

## Pulling and compilation
I intended to take care of everything with the shell script, simply pull the repo, run the script and open the resulting jpg.
```
git clone git@github.com:wbuz24/wbuziak-jgraph.git 
```

cd into the repo & run the script

```
sh scripts/motd.sh
```
If you have any issues, check your jgraph location, for instance, my local jgraph is in my applications folder and I have that command commented out of the shell script

Additionally, make sure you have all directories:
 - jgr/
 - jpg/
 - bin/
