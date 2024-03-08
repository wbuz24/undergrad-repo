if [ $# -ne 3 ]; then
  echo 'usage: sh Import-Grader.sh Grading-Directory Disk-File Import-File' >&2
  exit 1
fi

if [ ! -f ./FATRW ]; then
  echo "The program ./FATRW does not exist" >&2
  exit 1
fi

echo "Making sure the tmp files are all deleted."

rm -f tmp-grader-stdout.txt tmp-grader.jdisk tmp-grader-stderr.txt tmp-grader-short.txt 
rm -f tmp-digest-output.txt tmp.txt
rm -f tmp-yours-stdout.txt tmp-yours.jdisk tmp-yours-stderr.txt tmp-yours-short.txt 

echo "Copying: $1/$2 to tmp-grader.jdisk"
cp "$1/$2" tmp-grader.jdisk
echo "Running: $1/FATRW tmp-grader.jdisk import $1/$3"
"$1/FATRW" tmp-grader.jdisk import "$1/$3" > tmp-grader-stdout.txt 2> tmp-grader-stderr.txt
graderstderr=`wc tmp-grader-stderr.txt | awk '{ print $1 }'`

if [ $graderstderr = 0 ]; then
  
  echo "Running: sh $1/Digest-Disk.sh tmp-grader.jdisk $1"
  if sh "$1/Digest-Disk.sh" tmp-grader.jdisk "$1" ; then
    echo "The file information is in tmp-grader-short.txt"
    mv tmp-digest-short.txt tmp-grader-short.txt
  else 
    echo Problem running $1/Digest-Disk.sh 
    exit 1
  fi
else
  echo "$1/FATRW exited with an error.  See tmp-grader-stderr.txt"
fi

echo "Copying: $1/$2 to tmp-your.jdisk"
cp "$1/$2" tmp-yours.jdisk
echo "Running: ./FATRW tmp-yours.jdisk import $1/$3"
"./FATRW" tmp-yours.jdisk import "$1/$3" > tmp-yours-stdout.txt 2> tmp-yours-stderr.txt
yourstderr=`wc tmp-yours-stderr.txt | awk '{ print $1 }'`

if [ $yourstderr = 0 ]; then
  echo "Running: sh $1/Digest-Disk.sh tmp-yours.jdisk $1"
  if sh "$1/Digest-Disk.sh" tmp-yours.jdisk "$1" ; then
    echo "The file information is in tmp-yours-short.txt"
    mv tmp-digest-short.txt tmp-yours-short.txt
  else 
    echo Problem running $1/Digest-Disk.sh 
    exit 1
  fi
fi

if [ $yourstderr -ne $graderstderr ]; then
  echo "Error: Your stderr does not match the correct one."
  exit 1
fi

if [ $yourstderr != 0 ]; then
  echo "Both your program and the correct one exited with an error.  Success!"
  exit 0
fi

echo "Checking to see how many sectors you changed."

diff=`"$1/sectordiff" "$1/$2" tmp-yours.jdisk`

if [ `echo $diff | wc | awk '{ print $2 }'` -gt 1 ]; then
  echo "Problem with your final jdisk file, when comparing with the original disk:"
  echo "In other words, the files tmp-yours.jdisk and $1/$2"
  echo $diff
  exit 1
fi

w=`sed -n 3p tmp-yours-stdout.txt | awk '{ print $2 }'`
# echo "Number of writes is: $w"

if [ a"$w" = "a" ];then 
  echo "Error.  You should have the return value of jdisk_writes() on line three."
  exit 1
fi

wp1=`echo $w | awk '{ print $1+1 }'`
wm1=`echo $w | awk '{ print $1-1 }'`

if [ $w != $diff -a $wp1 != $diff -a $wm1 != $diff ];then 
   echo "Error.  The number of writes your program took was: $w"
   echo "        It should have been: $diff"
   exit 1
fi

echo "Your number of writes (+- 1) matched the number of changed sectors."

md51=`openssl md5 tmp-grader-short.txt | awk '{print $2 }'`
md52=`openssl md5 tmp-yours-short.txt | awk '{print $2 }'`

if [ $md51 != $md52 ]; then
  echo "Error.  Your digest file does not match the correct one."
  echo "        Your digest file is tmp-yours-short.txt."
  echo "        The correct digest file is tmp-grader-short.txt."
  exit 1
fi

echo "Your digest file and the correct digest files match.  Success!"
exit 0
