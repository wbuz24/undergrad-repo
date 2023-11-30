i=091
while [ $i -le 100 ]; do
  j=`( echo "" ; echo "" ; echo "" ; echo "" ; echo "") | randnum | sed 's/...//' | junk2`
  echo "$i: $j"
  echo $j | sh > $i.txt
  
  echo ""
  sleep 1
  i=`echo $i | awk '{ printf "%03d\n", $1+1 }'`
done
