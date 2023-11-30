if [ $# != 1 ]; then
  echo 'usage sh genrandom.sh n' >&2
  exit 1
fi

rm -f junk-z.txt
i=0
while [ $i -lt $1 ]; do
  echo "" >> junk-z.txt
  i=`echo $i | awk '{ print $1+1 }'`
done

randnum < junk-z.txt | awk '{ printf "%.1lf\n", $1*10.0 }' | tfill
