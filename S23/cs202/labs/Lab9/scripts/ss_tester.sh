if [ $# -ne 4 ]; then
  echo 'usage: sh ss_tester.sh your-solver my-solver player output-of-ss_random_game'
  exit 1
fi

yours="$1"
mine="$2"
player="$3"
input="$4"

board=`head -n 1 "$input" | sed 's/Grid: //'`
rows=`echo $board | wc | awk '{ print $2 }'`

sed 1,2d "$input" > tmp-pieces.txt
nlines=`$mine $board < tmp-pieces.txt | wc | awk '{ print $1 }'`

$yours $board < tmp-pieces.txt > tmp-youroutput.txt
ylines=`grep '[01]' tmp-youroutput.txt | wc | awk '{ print $1 }'`

if [ $nlines = 0 ]; then
  if [ $ylines = 0 ]; then
    echo "Correct"
  else 
    echo "Incorrect -- puzzle not solvable, yet you give a solution"
  fi
  exit 0
fi

if [ $nlines != $ylines ]; then
  echo "Incorrect -- your solution does not have $nlines shapes"
  exit 0
fi

"$player" - $board < tmp-youroutput.txt > tmp-yourgame.txt

if [ `grep Bad tmp-yourgame.txt | wc | awk '{ print $1 }'` != 0 ]; then
  echo "Incorrect -- your solution has bad lines in it"
  exit 0
fi


if [ `grep . tmp-yourgame.txt | tail -n $rows | grep 0 | wc | awk '{ print $1 }'` != 0 ]; then
  echo "Incorrect -- your solution does not solve the puzzle correctly."
  exit 0
fi

grep . tmp-youroutput.txt | awk '{ for (i = 1; i < NF-1; i++) { printf("%s%s", (i == 1)?"":" ", $i) }; print "" }' > tmp-yourpieces.txt

if [ `diff tmp-yourpieces.txt tmp-pieces.txt | wc | awk '{ print $1 }'` != 0 ]; then
  echo "Incorrect -- your solution does not use the correct pieces in the correct order."
  exit 0
fi

echo "Correct"
