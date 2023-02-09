i=34
while [ $i -le 100 ]; do
  en=`echo $i | awk '{ printf "%03d\n", $1 }'`
  echo $i $en
  gengold > $en.txt
  i=`echo $i | awk '{ print $1+1 }'`
  sleep 1
done
