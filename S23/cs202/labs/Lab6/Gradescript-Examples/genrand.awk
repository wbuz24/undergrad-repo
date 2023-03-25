{ n=rand()* 100 + 1
  for (i = 0; i < n; i++) {
    if (rand() < .50) printf("MULTIPLY "); else printf("DIVIDE ");
    printf("%.1lf\n", rand() + .1);
    if (rand() < .10) print "PRINT"
    if (rand() < .10) print "CALCULATE"
  }
  print "PRINT"
  print "CALCULATE"
}
