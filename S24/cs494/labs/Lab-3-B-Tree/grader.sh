if [ $# -ne 2 ]; then
  echo 'usage: grader number Y|N' >&2
  echo 'Y means that we are going to clean up files afterwards' >&2
  exit 1
fi


dcs=/home/jplank/cs494/labs/Lab-3-B-Tree/bin/b_tree_dcs
namefile=/home/jplank/cs494/labs/Lab-3-B-Tree/names.txt
randnum=/home/jplank/bin/LINUX-X86_64/randnum

mod=`echo $1 | awk '{ if ($1 >= 0) print $1 % 10; else { i = ($1 % 10); print (i == 0) ? i : 10-(-i) }}'`

if [ $mod = 1 ]; then
  if [ ! -f bin/b_tree_test ]; then
     echo "Problem $1 Incorrect"
     echo 'bin/b_tree_test' does not exist. 
     exit 1
  fi
  n=`( echo "" ; echo "" ; echo "") |  $randnum $1`
  nentries=`echo $n | awk '{ printf "%d\n", ($1 * 15) + 1 }'`
  ks=`echo $n | awk '{ printf "%d\n", ($2 * 25) + 15 }'`
  rm -f tree-$USER.jdisk tree-answer.jdisk
  $randnum $1 < $namefile | sort -n | awk '{ print "I", $2, $3 }' | head -n $nentries > input.txt
  /home/jplank/cs494/labs/Lab-3-B-Tree/bin/b_tree_test tree-answer.jdisk CREATE 51200 $ks < input.txt > /dev/null
  bin/b_tree_test tree-$USER.jdisk CREATE 51200 $ks < input.txt > /dev/null
  test="rm -f tree-$USER.jdisk tree-answer.jdisk
/home/jplank/cs494/labs/Lab-3-B-Tree/bin/b_tree_test tree-answer.jdisk CREATE 51200 $ks < input.txt > /dev/null
./bin/b_tree_test tree-$USER.jdisk CREATE 51200 $ks < input.txt > /dev/null"

elif [ $mod = 2 ]; then
  if [ ! -f bin/b_tree_test ]; then
     echo "Problem $1 Incorrect"
     echo 'bin/b_tree_test' does not exist. 
     exit 1
  fi
  n=`( echo "" ; echo "" ; echo "") |  $randnum $1`
  nentries1=`echo $n | awk '{ printf "%d\n", ($1 * 150) + 1 }'`
  nentries2=`echo $n | awk '{ printf "%d\n", ($2 * 150) + 1 }'`
  nentries=`echo $nentries1 $nentries2 | awk '{ printf "%d\n", $1 + $2}'`
  ks=`echo $n | awk '{ printf "%d\n", ($3 * 200) + 15 }'`
  rm -f tree-$USER.jdisk tree-answer.jdisk
  $randnum $1 < $namefile | sort -n | awk '{ print "I", $2, $3 }' | head -n $nentries > input.txt
  head -n $nentries1 input.txt | /home/jplank/cs494/labs/Lab-3-B-Tree/bin/b_tree_test tree-answer.jdisk CREATE 614400 $ks > /dev/null
  cp tree-answer.jdisk tree-$USER.jdisk
  sed  1,"$nentries1"d input.txt | /home/jplank/cs494/labs/Lab-3-B-Tree/bin/b_tree_test tree-answer.jdisk > /dev/null
  sed  1,"$nentries1"d input.txt | ./bin/b_tree_test tree-$USER.jdisk > /dev/null

  test="rm -f tree-$USER.jdisk tree-answer.jdisk
head -n $nentries1 input.txt | /home/jplank/cs494/labs/Lab-3-B-Tree/bin/b_tree_test tree-answer.jdisk CREATE 614400 $ks > /dev/null
cp tree-answer.jdisk tree-$USER.jdisk
sed  1,$nentries1""d input.txt | /home/jplank/cs494/labs/Lab-3-B-Tree/bin/b_tree_test tree-answer.jdisk > /dev/null
sed  1,$nentries1""d input.txt | ./bin/b_tree_test tree-$USER.jdisk > /dev/null"

elif [ $mod = 3 ]; then
  if [ ! -f bin/random_tester_1 ]; then
     echo "Problem $1 Incorrect"
     echo 'bin/random_tester_1' does not exist. 
     exit 1
  fi
  n=`( echo "" ; echo "" ; echo "") |  $randnum $1`
  nentries=`echo $n | awk '{ printf "%d\n", ($1 * 20) + 1 }'`
  ks=`echo $n | awk '{ printf "%d\n", ($2 * 200) + 15 }'`
  vs=`echo $n | awk '{ printf "%d\n", ($3 * 200) + 1 }'`
  rm -f tree-$USER.jdisk tree-answer.jdisk
  /home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_1 $1 $nentries $ks $vs tree-answer.jdisk - - > /dev/null
  ./bin/random_tester_1 $1 $nentries $ks $vs tree-$USER.jdisk - - > /dev/null
  test="rm -f tree-$USER.jdisk tree-answer.jdisk
/home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_1 $1 $nentries $ks $vs tree-answer.jdisk - - > /dev/null
./bin/random_tester_1 $1 $nentries $ks $vs tree-$USER.jdisk - - > /dev/null"

elif [ $mod = 4 ]; then
  if [ ! -f bin/random_tester_1 ]; then
     echo "Problem $1 Incorrect"
     echo 'bin/random_tester_1' does not exist. 
     exit 1
  fi
  n=`( echo "" ; echo "" ; echo "") |  $randnum $1`
  nentries=`echo $n | awk '{ printf "%d\n", ($1 * 500) + 1 }'`
  ks=`echo $n | awk '{ printf "%d\n", ($2 * 238) + 15 }'`
  vs=`echo $n | awk '{ printf "%d\n", ($3 * 1022) + 1 }'`
  rm -f tree-$USER.jdisk tree-answer.jdisk
  /home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_1 $1 $nentries $ks $vs tree-answer.jdisk - - > /dev/null
  ./bin/random_tester_1 $1 $nentries $ks $vs tree-$USER.jdisk - - > /dev/null
  test="rm -f tree-$USER.jdisk tree-answer.jdisk
/home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_1 $1 $nentries $ks $vs tree-answer.jdisk - - > /dev/null
./bin/random_tester_1 $1 $nentries $ks $vs tree-$USER.jdisk - - > /dev/null"

elif [ $mod = 5 ]; then
  if [ ! -f bin/random_tester_2 ]; then
     echo "Problem $1 Incorrect"
     echo 'bin/random_tester_2' does not exist. 
     exit 1
  fi
  n=`( echo "" ; echo "" ; echo "") |  $randnum $1`
  nentries=`echo $n | awk '{ printf "%d\n", ($1 * 500) + 1 }'`
  ks=`echo $n | awk '{ printf "%d\n", ($2 * 238) + 15 }'`
  rm -f tree-$USER.jdisk tree-answer.jdisk
  /home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_2 $1 $nentries $ks tree-answer.jdisk - - > /dev/null
  ./bin/random_tester_2 $1 $nentries $ks tree-$USER.jdisk - - > /dev/null
  test="rm -f tree-$USER.jdisk tree-answer.jdisk
/home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_2 $1 $nentries $ks tree-answer.jdisk - - > /dev/null
./bin/random_tester_2 $1 $nentries $ks tree-$USER.jdisk - - > /dev/null"

elif [ $mod = 6 ]; then
  if [ ! -f bin/random_tester_2 ]; then
     echo "Problem $1 Incorrect"
     echo 'bin/random_tester_2' does not exist. 
     exit 1
  fi
  n=`( echo "" ; echo "" ; echo "") |  $randnum $1`
  nentries=`echo $n | awk '{ printf "%d\n", ($1 * 5000) + 1 }'`
  ks=`echo $n | awk '{ printf "%d\n", ($2 * 6) + 4 }'`
  rm -f tree-$USER.jdisk tree-answer.jdisk
  /home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_2 $1 $nentries $ks tree-answer.jdisk - - > /dev/null
  ./bin/random_tester_2 $1 $nentries $ks tree-$USER.jdisk - - > /dev/null
  test="rm -f tree-$USER.jdisk tree-answer.jdisk
/home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_2 $1 $nentries $ks tree-answer.jdisk - - > /dev/null
./bin/random_tester_2 $1 $nentries $ks tree-$USER.jdisk - - > /dev/null"

elif [ $mod = 7 ]; then
  if [ ! -f bin/random_tester_2 ]; then
     echo "Problem $1 Incorrect"
     echo 'bin/random_tester_2' does not exist. 
     exit 1
  fi
  n=`( echo "" ; echo "" ; echo "") |  $randnum $1`
  nentries=`echo $n | awk '{ printf "%d\n", ($1 * 5000) + 1 }'`
  ks=254
  rm -f tree-$USER.jdisk tree-answer.jdisk
  /home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_2 $1 $nentries $ks tree-answer.jdisk - - > /dev/null
  ./bin/random_tester_2 $1 $nentries $ks tree-$USER.jdisk - - > /dev/null
  test="rm -f tree-$USER.jdisk tree-answer.jdisk
/home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_2 $1 $nentries $ks tree-answer.jdisk - - > /dev/null
./bin/random_tester_2 $1 $nentries $ks tree-$USER.jdisk - - > /dev/null"

elif [ $mod = 8 ]; then
  if [ ! -f bin/random_tester_2 ]; then
     echo "Problem $1 Incorrect"
     echo 'bin/random_tester_2' does not exist. 
     exit 1
  fi
  n=`( echo "" ; echo "" ; echo "") |  $randnum $1`
  nentries1=`echo $n | awk '{ printf "%d\n", ($1 * 5000) + 1 }'`
  nentries2=`echo $n | awk '{ printf "%d\n", ($2 * 5000) + 1 }'`
  tsize=`echo $nentries1 $nentries2 | awk '{ print ($1+$2)*2*1024 }'`
  seed2=`echo $n | awk '{ print $3 }' | sed 's/..//'`
  ks=254
  rm -f tree-$USER.jdisk tree-answer.jdisk
  /home/jplank/cs494/labs/Lab-3-B-Tree/bin/b_tree_test tree-answer.jdisk CREATE $tsize $ks < /dev/null > /dev/null
  /home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_2 $1 $nentries1 $ks tree-answer.jdisk - input.txt > /dev/null
  cp tree-answer.jdisk tree-$USER.jdisk
  /home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_2 $seed2 $nentries2 $ks tree-answer.jdisk input.txt - > /dev/null
  ./bin/random_tester_2 $seed2 $nentries2 $ks tree-$USER.jdisk input.txt - > /dev/null
  test="rm -f tree-$USER.jdisk tree-answer.jdisk
/home/jplank/cs494/labs/Lab-3-B-Tree/bin/b_tree_test tree-answer.jdisk CREATE $tsize $ks < /dev/null > /dev/null
/home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_2 $1 $nentries1 $ks tree-answer.jdisk - input.txt > /dev/null
cp tree-answer.jdisk tree-$USER.jdisk
/home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_2 $seed2 $nentries2 $ks tree-answer.jdisk input.txt - > /dev/null
./bin/random_tester_2 $seed2 $nentries2 $ks tree-$USER.jdisk input.txt - > /dev/null"

elif [ $mod = 9 ]; then
  if [ ! -f bin/random_tester_2 ]; then
     echo "Problem $1 Incorrect"
     echo 'bin/random_tester_2' does not exist. 
     exit 1
  fi
  n=`( echo "" ; echo "" ; echo "" ; echo "") |  $randnum $1`
  nentries1=`echo $n | awk '{ printf "%d\n", ($1 * 5000) + 1 }'`
  nentries2=`echo $n | awk '{ printf "%d\n", ($2 * 5000) + 1 }'`
  tsize=`echo $nentries1 $nentries2 | awk '{ print ($1+$2)*2*1024 }'`
  seed2=`echo $n | awk '{ print $3 }' | sed 's/..//'`
  ks=`echo $n | awk '{ printf "%d\n", ($2 * 6) + 4 }'`
  rm -f tree-$USER.jdisk tree-answer.jdisk
  /home/jplank/cs494/labs/Lab-3-B-Tree/bin/b_tree_test tree-answer.jdisk CREATE $tsize $ks < /dev/null > /dev/null
  /home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_2 $1 $nentries1 $ks tree-answer.jdisk - input.txt > /dev/null
  cp tree-answer.jdisk tree-$USER.jdisk
  /home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_2 $seed2 $nentries2 $ks tree-answer.jdisk input.txt - > /dev/null
  ./bin/random_tester_2 $seed2 $nentries2 $ks tree-$USER.jdisk input.txt - > /dev/null
  test="rm -f tree-$USER.jdisk tree-answer.jdisk
/home/jplank/cs494/labs/Lab-3-B-Tree/bin/b_tree_test tree-answer.jdisk CREATE $tsize $ks < /dev/null > /dev/null
/home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_2 $1 $nentries1 $ks tree-answer.jdisk - input.txt > /dev/null
cp tree-answer.jdisk tree-$USER.jdisk
/home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_2 $seed2 $nentries2 $ks tree-answer.jdisk input.txt - > /dev/null
./bin/random_tester_2 $seed2 $nentries2 $ks tree-$USER.jdisk input.txt - > /dev/null"

else
  if [ ! -f bin/random_tester_2 ]; then
     echo "Problem $1 Incorrect"
     echo 'bin/random_tester_2' does not exist. 
     exit 1
  fi
  n=`( echo "" ; echo "" ; echo "" ; echo "") |  $randnum $1`
  nentries1=`echo $n | awk '{ printf "%d\n", ($1 * 5000) + 1 }'`
  nentries2=`echo $n | awk '{ printf "%d\n", ($2 * 5000) + 1 }'`
  tsize=`echo $nentries1 $nentries2 | awk '{ print ($1+$2)*2*1024 }'`
  seed2=`echo $n | awk '{ print $3 }' | sed 's/..//'`
  ks=`echo $n | awk '{ printf "%d\n", ($2 * 250) + 4 }'`
  rm -f tree-$USER.jdisk tree-answer.jdisk
  /home/jplank/cs494/labs/Lab-3-B-Tree/bin/b_tree_test tree-answer.jdisk CREATE $tsize $ks < /dev/null > /dev/null
  /home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_2 $1 $nentries1 $ks tree-answer.jdisk - input.txt > /dev/null
  cp tree-answer.jdisk tree-$USER.jdisk
  /home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_2 $seed2 $nentries2 $ks tree-answer.jdisk input.txt - > /dev/null
  ./bin/random_tester_2 $seed2 $nentries2 $ks tree-$USER.jdisk input.txt - > /dev/null
  test="rm -f tree-$USER.jdisk tree-answer.jdisk
/home/jplank/cs494/labs/Lab-3-B-Tree/bin/b_tree_test tree-answer.jdisk CREATE $tsize $ks < /dev/null > /dev/null
/home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_2 $1 $nentries1 $ks tree-answer.jdisk - input.txt > /dev/null
cp tree-answer.jdisk tree-$USER.jdisk
/home/jplank/cs494/labs/Lab-3-B-Tree/bin/random_tester_2 $seed2 $nentries2 $ks tree-answer.jdisk input.txt - > /dev/null
./bin/random_tester_2 $seed2 $nentries2 $ks tree-$USER.jdisk input.txt - > /dev/null"
fi

$dcs tree-answer.jdisk > dcs-answer.txt 2> dcs-answer-stderr.txt
$dcs tree-$USER.jdisk > dcs-$USER.txt 2> dcs-$USER-stderr.txt

incorrect=no

if [ `diff dcs-answer.txt dcs-$USER.txt | wc | awk '{ print $1 }'` != 0 ]; then
 echo "Problem $1 Incorrect"
 echo "Standard output of bin/b_tree_dcs on tree-answer.jdisk and tree-$USER.jdisk differs"
 incorrect=yes
fi
 
if [ `diff dcs-answer-stderr.txt dcs-$USER-stderr.txt | wc | awk '{ print $1 }'` != 0 ]; then
 echo "Problem $1 Incorrect"
 echo "Standard error of bin/b_tree_dcs on tree-answer.jdisk and tree-$USER.jdisk differs"
 incorrect=yes
fi
 
if [ $incorrect = no ]; then
 echo "Problem $1 Correct."
fi

echo ""
echo "tree-answer.jdisk and tree-$USER.jdisk created as follows:"
echo "----------------------------------------------------------"
echo "$test"
if [ $incorrect = yes ]; then
  echo ""
  echo "Correct standard output of bin/b_tree_dcs tree-answer.jdisk in dcs-answer.txt"
  echo "Correct standard error  of bin/b_tree_dcs tree-answer.jdisk in dcs-answer-stderr.txt"
  echo "Your    standard output of bin/b_tree_dcs tree-$USER.jdisk in dcs-$USER.txt"
  echo "Your    standard error  of bin/b_tree_dcs tree-$USER.jdisk in dcs-$USER-stderr.txt"
fi

if [ $2 = "Y" ]; then 
  rm -f input.txt tree-answer.jdisk tree-$USER.jdisk dcs-answer.txt dcs-answer-stderr.txt dcs-$USER.txt dcs-$USER-stderr.txt
fi 
