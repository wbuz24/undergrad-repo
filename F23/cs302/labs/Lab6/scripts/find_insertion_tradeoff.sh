i=10
while [ $i -lt 200 ]; do
  q=`csh -c "time quick_2_sort $i 50000 8 no no" | awk '{ print $3 }' | sed 's/0://'`
  m=`csh -c "time merge_1_sort $i 50000 8 no no" | awk '{ print $3 }' | sed 's/0://'`
  ins=`csh -c "time insertion_3_sort $i 50000 8 no no" | awk '{ print $3 }' | sed 's/0://'`
  echo $i $q $m $ins
  i=`echo $i | awk '{ print $1+5 }'`
done
