#!/bin/sh

if [ $# -ne 7 ]; then
  echo 'usage: sh run_multiple.sh r c mss colors player nruns starting_seed' >& 2
  exit 1
fi

seed=$7
i=1
t=0
while [ $i -le $6 ]; do
  j=`bin/sb-player $1 $2 $3 $4 $5 n n $seed | awk '{ print $NF }'`
  if [ a"$j" = a ]; then
    j=0
  fi
  t=`echo $t $j | awk '{ print $1+$2 }'`
  echo $i $j $t | awk '{ printf "Run %3d - Score: %6d  - Average %10.3lf\n", $1, $2, ($3+0.0)/($1+0.0) }'
  i=`echo $i | awk '{ print $1 + 1 }'`
  seed=`echo $seed | awk '{ print $1 + 1 }'`
done

