#     if (commands.find('E') != string::npos) {    Delete
#     if (commands.find('L') != string::npos) {    Clear
#     if (commands.find('D') != string::npos) {    Destroy
#     if (commands.find('H') != string::npos) {    Height
#     if (commands.find('K') != string::npos) {    Keys
#     if (commands.find('A') != string::npos) {    Assignment
#     if (commands.find('C') != string::npos) {    Copy

i=1
while [ $i -le 100 ]; do
  n=`echo $i | awk '{ n = $1 % 25; if (n == 0) n = 25;  
      if (n <= 10) {
        n *= 20 
      } else {
        n *= 50; 
      } print n }'`
  echo $n
  if [ $i -le 25 ]; then
    c="-"
  elif [ $i -le 50 ]; then
    c="E"
  elif [ $i -lt 75 ]; then
    c="CA"
  elif [ $i -le 95 ]; then
    c="EHKAC"
  else 
    c="CDEHKAC"
  fi
  key=`echo $i | awk '{ printf "%03d", $1 }'`
  echo $key
  ( echo $n $c ; random_names $n | sed 's/ /-/g' | sort -u ) | a.out > $key.txt
  i=$(($i+1))
  sleep 1
done
