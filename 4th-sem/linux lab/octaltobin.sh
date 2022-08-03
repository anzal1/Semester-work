ch1="yes"
while [ $ch1 = "yes" ]
do
echo "1.Convert Decimal To Binary"
echo "2.Convert Decimal To Octal"
echo "3.Convert Decimal To Hexadecaimal"
echo "4.Exit"

echo -n "Enter your Choice :- "
read ch

case $ch in

1)echo -n "Enter A No. To Convert:- "
read no1
  b=`echo "obase=2 ; $no1" | bc`
echo "Binary Form Of $no1 :- $b";;

2)echo -n "Enter A No. To Convert :- "
read no1
  b=`echo "obase=8 ; $no1 " | bc`
echo "Octal Form Of $no1 :- $b";;

3)echo "Enter A No. To Convert"read no1
  b=`echo "obase=16 ; $no1" | bc`
echo "Hexadecimal Form Of $no1 :- $b";;

4)exit;;
*)echo "Invalid Choice"

esac

echo "Do You Want To Continue"
read ch1
done