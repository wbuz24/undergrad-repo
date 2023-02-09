cat $1 | awk '{ print $1, $2, $4, $5, $3 }' > junk.txt ; mv junk.txt $1
