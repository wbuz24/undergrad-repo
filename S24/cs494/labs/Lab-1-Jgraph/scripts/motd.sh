# make clean, but shove output to /dev/null
make clean 1> /dev/null
make 1> /dev/null

# output text and run the script
echo "Music of the Day Jgraph Generator"
./bin/motd Music-Of-The-Day.txt 

# run and convert the jgraph
`~/Applications/jgraph/jgraph -P Music-Of-The-Day.jgr | ps2pdf - | convert -density 300 - -quality 100 Music-Of-The-Day.jpg`
