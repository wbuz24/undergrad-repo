sh /home/jplank/cs494/labs/Lab-2-FAT/Import-Grader.sh /home/jplank/cs494/labs/Lab-2-FAT t2.jdisk FATRW | tail -n 1 | awk '{ print $NF }'
