# if the jgr, jpg and bin directories are not present, make them
if [ -d bin/ ]; then
	echo 'Directory: bin/ exists' 1> /dev/null
else
	mkdir bin 1> /dev/null

fi

if [ -d data/ ]; then
	echo 'Directory: data/ exists' 1> /dev/null
else
	mkdir data 1> /dev/null

fi

if [ -d input/ ]; then
	echo 'Directory: data/ exists' 1> /dev/null
else
	echo "No input text available"

fi

# make clean, but shove output to /dev/null
if [ -f bin/motd ]; then
	make clean 1> /dev/null

fi

make

./bin/motd txt/Music-Of-The-Day.txt 

`jgraph -P jgr/Music-Of-The-Day.jgr | ps2pdf - | convert -density 300 - -quality 100 jpg/Music-Of-The-Day.jpg`

echo "Generated jgr/Music-Of-The-Day.jgr and converted to jpg/Music-Of-The-Day.jpg"
