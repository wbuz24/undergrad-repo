if [ $# -ne 6 ]; then
  echo 'usage: sh generate.sh number min-ts max-ts min-events max-events hash_length'
  exit 1
fi

num=`echo $1 | awk '{ printf "%03d\n", $1 }'`
mints=$2
maxts=$3
minev=$4
maxev=$5
hl=$6

i=0
s=""
while [ $i -lt $hl ]; do
  s="$s""."
  i=$(($i+1))
done

random_names $maxev > tmp-names.txt
sed 's/\(.*\)/echo "\1" | openssl sha1/' < tmp-names.txt | sh | sed 's/.*= \('$s'\).*/\1/' > tmp-hashes.txt
echo $maxev | awk '{ for (i = 0; i < $1*2; i++) print "" }' | randnum > tmp-rn.txt


rn=`sed -n 1p tmp-rn.txt`
ts=`echo $mints $maxts $rn | awk '{ printf "%.0f\n", $1 + ($2+1-$1)*$3 }'`
fxn=`sed -n 2p tmp-rn.txt | awk '{ print ($1 < .5) ? "Last7" : "XOR" }'`
coll=`sed -n 3p tmp-rn.txt | awk '{ print ($1 < .5) ? "Linear" : "Double" }'`
echo $ts $fxn $coll > $num.cli
rn=`sed -n 4p tmp-rn.txt`
nev=`echo $minev $maxev $rn | awk '{ printf "%.0f\n", $1 + ($2+1-$1)*$3 }'`

(
r=5
a=0
e=$maxev

i=0
while [ $i -lt $nev ]; do
  rn=`sed -n "$r"p tmp-rn.txt`
  r=$(($r+1))
  command=`echo $rn | awk '{ if ($1 < 0.1 ) print "TP"; else if ($1 < .7) print "A"; else print "F" }'`
  if [ $command = "F" -a $a = 0 ]; then
    command="A"
  fi
  if [ $command = "TP" ]; then
    echo TP
  elif [ $command = "A" ]; then
    a=$(($a+1))
    name=`sed -n "$a"p tmp-names.txt`
    hash=`sed -n "$a"p tmp-hashes.txt`
    echo A $hash $name
  else
    rn=`sed -n "$r"p tmp-rn.txt`
    r=$(($r+1))
    new=`echo $rn | awk '{ if ( $1 < .75 ) print ($1/0.75) ; else print "YES" }'`
    if [ $new = "YES" ]; then
      hash=`sed -n "$e"p tmp-hashes.txt` 
      e=$(($e-1))
    else 
      hashn=`echo $new $a | awk '{ printf "%.0f\n", $1*($2)+1 }'`
      hash=`sed -n "$hashn"p tmp-hashes.txt`
    fi
    echo F $hash
  fi
  i=$(($i+1))
done

echo "P" ) > $num.txt
