for i in *.txt ; do
  sed 's/EXP/FACT/g' $i > tmp.txt
  mv tmp.txt $i
  echo $i
done
