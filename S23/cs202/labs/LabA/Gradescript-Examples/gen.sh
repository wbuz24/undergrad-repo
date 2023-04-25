i=1
while [ $i -le 100 ]; do
  n=`echo $i | sed 's/.*\(.\)$/\1/'`
  n=`echo $n | awk '{ print ($1+1)*500-400 }'`
  if [ $i -le 10 ]; then
    c="D"
  elif [ $i -lt 20 ]; then
    c="H"
  elif [ $i -lt 30 ]; then
    c="K"
  elif [ $i -lt 40 ]; then
    c="R"
  elif [ $i -lt 50 ]; then
    c="C"
  else
    c="DHKRC"
  fi
  key=`echo $i | awk '{ printf "%03d", $1 }'`
  echo $key
  ( echo $n $c ; random_names $n | sed 's/ /-/g' | sort -u ) | a.out > $key.txt
  i=$(($i+1))
  sleep 1
done
