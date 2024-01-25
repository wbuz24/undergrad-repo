if [ $# -ne 3 ]; then
  echo 'usage: sh do_it.sh key file divisor' >&2
  exit 1
fi

$clab3/lab3/huff_create_code-2 < "$2" > $1-code.txt $3
$clab3/lab3/huff_enc < "$2" $1-code.txt $1-input.txt
