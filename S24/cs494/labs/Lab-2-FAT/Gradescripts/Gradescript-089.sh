sh /home/jplank/cs494/labs/Lab-2-FAT/Import-Grader.sh /home/jplank/cs494/labs/Lab-2-FAT t8.jdisk jdisk_test.c | tail -n 1 | awk '{ print $NF }'
