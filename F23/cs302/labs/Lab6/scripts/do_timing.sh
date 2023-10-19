if [ $# -ne 1 ]; then
  echo 'usage: sh scripts/do_timing.sh algorithm' >&2 
  exit 1
fi

i=100
t=0

while [ $t -lt 10 -a $i -lt 1638401 ]; do
  tm=`csh -c "time bin/$1_sort $i 10 0 no no" | awk '{ print $3 }' | sed 's/:/ /g' | awk '{ print $1*60+$2 }'`
  t=`echo $tm | awk '{ printf "%.0lf\n", $1 }'`
  echo $1 $i $tm 
  i=`echo $i | awk '{ printf "%.0lf\n",  $1*1.4 }'`
done

