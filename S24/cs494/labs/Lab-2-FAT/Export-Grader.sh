if [ $# -ne 3 ]; then
  echo 'usage: sh Export-Grader.sh Grading-Directory Disk-File Starting-Block' >&2
  exit 1
fi

if [ ! -f ./FATRW ]; then
  echo "The program ./FATRW does not exist" >&2
  exit 1
fi

if [ ! -f "$1/$2" ]; then
  echo "Jdisk file $1/$2 does not exist." >&2
  exit 1
fi

rm -f tmp-grader-stdout.txt tmp-grader.jdisk tmp-grader-stderr.txt tmp-grader-file.txt 
rm -f tmp-yours-stdout.txt tmp-yours.jdisk tmp-yours-stderr.txt tmp-yours-file.txt 

echo "Copying: $1/$2 to tmp-grader.jdisk"
cp "$1/$2" tmp-grader.jdisk

if [ `"$1/FAT" tmp-grader.jdisk report | grep "File Starting Block $3\. " | wc | awk '{ print $1 }'` = 0 ]; then
  echo "Block $3 in $1/$2 is not a starting block of a file" >&2
  exit 1
fi

echo "Running: $1/FATRW tmp-grader.jdisk export $3 tmp-grader-file.txt"
"$1/FATRW" tmp-grader.jdisk export "$3"  tmp-grader-file.txt > tmp-grader-stdout.txt 2> tmp-grader-stderr.txt
graderstderr=`wc tmp-grader-stderr.txt | awk '{ print $1 }'`

if [ $graderstderr != 0 ]; then
  echo "$1/FATRW exited with an error.  See tmp-grader-stderr.txt"
fi

echo "Copying: $1/$2 to tmp-your.jdisk"
cp "$1/$2" tmp-yours.jdisk
echo "Running: ./FATRW tmp-yours.jdisk export $3 tmp-yours-file.txt"
"./FATRW" tmp-yours.jdisk export "$3"  tmp-yours-file.txt > tmp-yours-stdout.txt 2> tmp-yours-stderr.txt
yourstderr=`wc tmp-yours-stderr.txt | awk '{ print $1 }'`

if [ $yourstderr -ne $graderstderr ]; then
  echo "Error: Your stderr does not match the correct one."
  exit 1
fi

if [ $yourstderr != 0 ]; then
  echo "Both your program and the correct one exited with an error.  Success!"
  exit 0
fi

echo "Double-checking that the exported files are the same."
if [ `diff tmp-yours-file.txt tmp-grader-file.txt | wc | awk '{ print $1 }'` != 0 ]; then
  echo "Your exported file did not match the correct one."
  exit 1
fi

echo "Double-checking that the stdout files are the same."
if [ `diff tmp-yours-stdout.txt tmp-grader-stdout.txt | wc | awk '{ print $1 }'` != 0 ]; then
  echo "Your standard output did not match the correct one."
  exit 1
fi

echo "All is good -- Success!"
