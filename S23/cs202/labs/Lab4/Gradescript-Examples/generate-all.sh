n=100
while [ $n -lt 20 ]; do
  echo $n
  sh generate.sh $n 10 20 5 10 8
  n=$(($n+1))
  sleep 1
done

while [ $n -lt 30 ]; do
  echo $n
  sh generate.sh $n 10 20 10 20 8
  n=$(($n+1))
  sleep 1
done

while [ $n -lt 40 ]; do
  echo $n
  sh generate.sh $n 20 40 20 30 15
  n=$(($n+1))
  sleep 1
done

while [ $n -lt 50 ]; do
  echo $n
  sh generate.sh $n 30 60 20 30 15
  n=$(($n+1))
  sleep 1
done

while [ $n -lt 60 ]; do
  echo $n
  sh generate.sh $n 50 100 70 150 35
  n=$(($n+1))
  sleep 1
done

while [ $n -lt 90 ]; do
  echo $n
  sh generate.sh $n 50 100 100 300 40
  echo TP >> "0$n.txt"
  n=$(($n+1))
  sleep 1
done


while [ $n -le 100 ]; do
  echo $n
  sh generate.sh $n 1000 10000 5000 6000 40
  echo TP >> "0$n.txt"
  n=$(($n+1))
  sleep 1
done

