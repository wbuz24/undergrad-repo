for i in `cat junk3.txt` ; do
  ../ss_random_game 3 6 5 y > $i
  sleep 1
  echo $i
done
