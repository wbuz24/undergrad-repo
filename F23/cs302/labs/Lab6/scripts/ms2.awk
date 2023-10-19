BEGIN { i = 1000 }
/^B/  { if (i == 1000) {
          printf "newgraph xaxis min 0 max %d nodraw\n", $3
          printf "yaxis min 0 max 1000 nodraw\n"
        }
        printf("newline poly pcfill .5 0 0 pts %d %d %d %d %d %d %d %d\n", \
           $2, i, $2, i-1, $2+$3, i-1, $2+$3, i)
        i-- }
/^E/  { printf("newline poly pcfill 1 1 0 pts %d %d %d %d %d %d %d %d\n", \
           $2, i, $2, i-1, $2+$3, i-1, $2+$3, i)
        i-- }
END   { printf "yaxis min %d\n", i }
