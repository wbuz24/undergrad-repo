for i in *_sort ; do
  seed=`echo $i | sed 's/_sort$//'`
  echo $i >&2
  sh do_timing.sh $seed
done
