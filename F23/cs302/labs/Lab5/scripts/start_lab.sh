if [ -d src ]; then
  echo "The directory 'src' already exists.  Move it or delete it before running this." >&2
  exit 1
fi

if [ -d bin ]; then
  echo "The directory 'bin' already exists.  Move it or delete it before running this." >&2
  exit 1
fi

if [ -d scripts ]; then
  echo "The directory 'scripts' already exists.  Move it or delete it before running this." >&2
  exit 1
fi

mkdir bin
cp -r /home/jplank/cs302/Labs/Lab5/src .
cp -r /home/jplank/cs302/Labs/Lab5/scripts .
cp /home/jplank/cs302/Labs/Lab5/makefile .
