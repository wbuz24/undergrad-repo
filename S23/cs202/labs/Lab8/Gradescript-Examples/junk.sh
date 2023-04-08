a.out 10 1 > 019.txt
a.out 10 2 > 020.txt
a.out 10 3 > 021.txt
a.out 10 4 > 022.txt
a.out 10 5 > 023.txt
a.out 20 6 > 019.txt
a.out 20 7 > 020.txt
a.out 20 8 > 021.txt
a.out 20 9 > 022.txt
a.out 20 23 > 023.txt
a.out 20 24 > 024.txt
a.out 20 25 > 025.txt

i=26
while [ $i -le 100 ]; do
  if [ $i -lt 35 ]; then
    e=$i
  elif [ $i -lt 50 ]; then
    e="$(($i*2))"
  elif [ $i -lt 60 ]; then
    e="$(($i*5))"
  elif [ $i -lt 70 ]; then
    e="$(($i*10))"
  elif [ $i -lt 80 ]; then
    e="$(($i*25))"
  elif [ $i -lt 90 ]; then
    e="$(($i*50))"
  else 
    e="$(($i*100))"
  fi
  a.out $e $i > 0$i.txt
  i=$(($i+1))
done
