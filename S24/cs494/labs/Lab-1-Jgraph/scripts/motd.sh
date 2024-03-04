# make clean, but shove output to /dev/null
if [ -f bin/motd ]; then
	make clean 1> /dev/null

fi
make 1> /dev/null

# output text and run the script
echo "Music of the Day Jgraph Generator"
./bin/motd txt/Music-Of-The-Day.txt 

# run and convert the jgraph
`~/Applications/jgraph/jgraph -P jgr/Music-Of-The-Day.jgr | ps2pdf - | convert -density 300 - -quality 100 jpg/Music-Of-The-Day.jpg`
# `jgraph -P Music-Of-The-Day.jgr | ps2pdf - | convert -density 300 - -quality 100 Music-Of-The-Day.jpg`
