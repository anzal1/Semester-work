echo enter two number 
read a
echo  entered number 1:$a 
read b
echo entered number 2:$b
c=`expr $a + $b`
echo the sum is:"$c"