awk '{ printf "echo %.0lf %.0lf %.0lf %s %.0lf > %s.txt\n", $2*10, $3*15, $4*6+1, $5, $6*10+1, $1 }' < gr.txt
