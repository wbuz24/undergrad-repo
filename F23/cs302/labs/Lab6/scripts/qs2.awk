BEGIN { print "<pre>" }
END { print "</pre>" }
/^S/ { st=$2; sz=$3 
       printf "S: %5d %5d %5s", st, sz, ""
       for (i = 4; i <= NF; i++) {
            f = i-4
            if ((f >= st) && (f < (st + sz))) {
              if (sz > 2 && (f == st || f == st+sz-1 || f == st+sz/2)) {
                printf(" <font color=blue>%5.2lf</font>", $i);
              } else if (sz > 0) {
                printf(" <font color=red>%5.2lf</font>", $i);
              } else {
                printf(" %5.2lf", $i);
              }
            } else {
                printf(" %5.2lf", $i);
            }
        }
            printf "\n"
        }
/^M/ { st=$2; sz=$3 ; p=$4
       printf "M: %5d %5d %5s", st, sz, $4
       for (i = 5; i <= NF; i++) {
            f = i-5
            if (f == st) {
              if (sz > 2) {
                printf(" <font color=blue>%5.2lf</font>", $i);
              } else if (sz > 0) {
                printf(" <font color=red>%5.2lf</font>", $i);
              } else {
                printf(" %5.2lf", $i);
              }
            } else if ((f > st) && (f < (st + sz))) {
                printf(" <font color=red>%5.2lf</font>", $i);
            } else {
                printf(" %5.2lf", $i);
            }
        }
            printf "\n"
        }
/^P/ { st=$2; sz=$3; p=$4
       printf "P: %5d %5d %5d", st, sz, p
       for (i = 5; i <= NF; i++) {
            f = i-5
            if (f == p) {
              printf(" <font color=blue>%5.2lf</font>", $i);
            } else if ((f >= st) && (f < (st + sz))) {
                printf(" <font color=red>%5.2lf</font>", $i);
            } else {
                
                printf(" %5.2lf", $i);
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
