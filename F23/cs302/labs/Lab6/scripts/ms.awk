BEGIN { print "<pre>" }
END { print "</pre>" }
/^[BE]/  { st=$2; sz=$3 
       printf "%s %5d %5d %5s", $1, st, sz, ""
       if ($1 == "B:") {
         fc = "#ffaaaa"
       } else {
         fc = "#ffff00"
       }
       for (i = 4; i <= NF; i++) {
            f = i-4
            if ((f >= st) && (f < (st + sz))) {
                printf("<font  style=\"background-color: %s\">%6.2lf</font>", fc, $i);
            } else {
                printf("%6.2lf", $i);
            }
        }
            printf "\n"
        }
/^ / { 
       printf "   %5s %5s %5s", "", "", ""
       for (i = 1; i <= NF; i++) {
          printf(" %5.2lf", $i);
        }
           printf "\n"
        }
            
       
