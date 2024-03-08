if [ $# != 2 ]; then
  echo 'usage: sh Digest-Disk.sh FAT-File Directory-Holding-My-FAT-Program' >&2
  exit 1
fi

DDDir="$2"

if [ ! -f "$1" ]; then
  echo "No file $1" 
  exit 1
fi

if $DDDir/FAT "$1" report > tmp-digest-output.txt 2>&1 ; then
  sbs=`grep 'File Starting Block' tmp-digest-output.txt | awk '{ print $4 }' | sed 's/.$//'`
else
  echo Report Not OK
  exit 1
fi

if [ A"$sbs" = A ]; then
  echo "END FILE INFORMATION" >> tmp-digest-output.txt
  echo "No Files" >> tmp-digest-output.txt
  exit 0
fi

hashes="FILE-HASHES:"
for i in $sbs ; do
  if $DDDir/FAT "$1" export $i tmp.txt ; then
    hash=`openssl md5 tmp.txt | sed 's/.* //'`
    hashes="$hashes $hash"
    echo "File from block $i has a hash of $hash" >> tmp-digest-output.txt
  else 
    echo "Failed to read file starting with block $i"
    exit 1
  fi
done

echo "END FILE INFORMATION" >> tmp-digest-output.txt
echo "" >> tmp-digest-output.txt
echo "SORTED-HASHES" >> tmp-digest-output.txt

( for i in `echo $hashes | sed 's/.*: //'` ; do
  echo $i
done ) | sort >> tmp-digest-output.txt

sed '/BEGIN FILE INFORMATION/,/END FILE INFORMATION/d' < tmp-digest-output.txt > tmp-digest-short.txt

exit 0
