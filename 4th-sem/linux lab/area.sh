echo "\n"

echo -n "Enter the radius of a circle : "
read r
area=$(echo "scale=2;3.14 * ($r * $r)" | bc)
d=$(echo "scale=2;2 * $r"|bc)
echo "Area of circle is : $area"

echo "\n"


echo -n "Enter length  of the rectangle:"
read l
echo -n "Enter breadth rectangle:"
read b
area=$(echo "scale=2;($l*$b)" | bc)
perimeter=$(echo "scale=2;2*($l+$b)" | bc)
echo "Area of the rectangle is : $area"
echo "Perimeter of the rectangle is : $perimeter"
