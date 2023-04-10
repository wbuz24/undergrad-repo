for i in `ls ???.txt | sed 1,20d` ; do
  echo $i 
  sed 1,2d $i | ../ss_solver `sed -n s/Grid://p $i`  | wc
done
