for i in \
   060 \
   061 \
   062 \
   063 \
   064 \
   065 \
   066 \
   067 \
   068 \
   069 ; do
   head -n 200 $i-clear.txt | $clab3/lab3/huff_enc $i-code.txt $i-input.txt 
done

