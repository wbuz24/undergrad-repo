# for i in 090 091 092 093 094 095 096 097 098 099 ; do
for i in 078 096 ; do
  echo $i
  rn=`( echo "" ; echo "" ; echo "" ; echo "" ; echo "" ; echo "" ) | randnum`
  pr=`echo $rn | awk '{ printf "%.2lf\n", $1*.5 }'`
  ij=`echo $rn | awk '{ printf "%.0lf\n", $2*10000.0+1 }'`
  jj=`echo $rn | awk '{ printf "%.0lf\n", $3*10000.0+1 }'`
  mh=`echo $rn | awk '{ printf "%.0lf\n", $4*5000.0+100 }'`
  pl=`echo $rn | awk '{ printf "%.0lf\n", $5*6.0+3 }'`
  nn=`echo $rn | awk '{ printf "%.0lf\n", $6*(12-'$pl')*8 +10 }'`
  echo $ij $jj $pl $mh $pr > $i.cl
  ../random_hero_gen $nn 10000 10000 10000 > $i.txt
  sleep 1
done

# # for i in 006 007 008 009 010 ; do
# #   echo $i
# #   rn=`( echo "" ) | randnum`
# #   pr=`echo $rn | awk '{ printf "%.2lf\n", $1*.3 }'`
# #   echo 10000 10000 5 5000 $pr > $i.cl
# #   ../random_hero_gen 10 10000 10000 10000 > $i.txt
# #   sleep 1
# # done
# 
# for i in 016 \
#          017 \
#          018 \
#          019 \
#          020 ; do
#   echo $i
#   rn=`( echo "" ) | randnum`
#   pr=`echo $rn | awk '{ printf "%.2lf\n", $1*.3 }'`
#   echo 10000 10000 5 200 $pr > $i.cl
#   ../random_hero_gen 10 10000 10000 25 > $i.txt
#   sleep 1
# done

# for i in 011 \
#          012 \
#          013 \
#          014 \
#          015 ; do
#   echo $i
#   rn=`( echo "" ) | randnum`
#   pr=`echo $rn | awk '{ printf "%.2lf\n", $1*.3 }'`
#   echo 2000 10000 5 200 $pr > $i.cl
#   ../random_hero_gen 10 10000 10000 25 > $i.txt
#   sleep 1
# done

# for i in 021 \
#          022 \
#          023 \
#          024 \
#          025 ; do
#   echo $i
#   rn=`( echo "" ) | randnum`
#   pr=`echo $rn | awk '{ printf "%.2lf\n", $1*.3 }'`
#   echo 100 200 3 500 $pr > $i.cl
#   ../random_hero_gen 20 300 300 700 > $i.txt
#   sleep 1
# done

# for i in 026 \
#          027 \
#          028 \
#          029 \
#          030 ; do
#   echo $i
#   rn=`( echo "" ) | randnum`
#   pr=`echo $rn | awk '{ printf "%.2lf\n", $1*.3 }'`
#   echo 100 200 3 500 $pr > $i.cl
#   ../random_hero_gen 40 300 300 700 > $i.txt
#   sleep 1
# done
# 
# for i in 031 \
#          032 \
#          033 \
#          034 \
#          035 ; do
#   echo $i
#   rn=`( echo "" ) | randnum`
#   pr=`echo $rn | awk '{ printf "%.2lf\n", $1*.5 }'`
#   echo 100 200 9 500 $pr > $i.cl
#   ../random_hero_gen 12 300 300 700 > $i.txt
#   sleep 1
# done

# for i in 036 \
#          037 \
#          038 \
#          039 \
#          040 ; do
#   echo $i
#   rn=`( echo "" ) | randnum`
#   pr=`echo $rn | awk '{ printf "%.2lf\n", $1*.5 }'`
#   echo 300 10 50 500 $pr > $i.cl
#   ../random_hero_gen 40 300 300 700 > $i.txt
#   sleep 1
# done

# for i in 041 \
#          042 \
#          043 \
#          044 \
#          045 ; do
#   echo $i
#   rn=`( echo "" ) | randnum`
#   pr=`echo $rn | awk '{ printf "%.2lf\n", $1*.5 }'`
#   echo 300 10 50 500 $pr > $i.cl
#   ../random_hero_gen 200 300 300 700 > $i.txt
#   sleep 1
# done

# for i in 046 \
#          047 \
#          048 \
#          049 \
#          050 ; do
#   echo $i
#   rn=`( echo "" ) | randnum`
#   pr=`echo $rn | awk '{ printf "%.2lf\n", $1*.5 }'`
#   echo 300 10 50 500 $pr > $i.cl
#   ../random_hero_gen 200 300 300 700 > $i.txt
#   sleep 1
# done
# 
