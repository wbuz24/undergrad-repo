ge=/home/jplank/cs360/labs/Lab-4-Fakemake/Gradescript-Examples
cp $ge/onefile.c .
sleep 1
gcc -c onefile.c
sleep 1
gcc -o onefile onefile.o
cp $ge/001.fm fmakefile
if /home/jplank/cs360/labs/Lab-4-Fakemake/fakemake; then
  ./onefile
fi