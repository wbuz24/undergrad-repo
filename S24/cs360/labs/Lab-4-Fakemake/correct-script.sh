ge=/home/jplank/cs360/labs/Lab-4-Fakemake/Gradescript-Examples
cp $ge/onefile.c .
sleep 1
gcc -c onefile.c
rm -f onefile
cp $ge/001.fm fmakefile
if /home/shartreuce/repos/undergrad-repo/S24/cs360/labs/Lab-4-Fakemake/fakemake; then
  ./onefile
fi
