#!/bin/bash
#Bamphiane Annie Phongphouthai
#bp8qg
#October 17, 2017
#averagetime.sh

echo "Please enter Dictionary file name:"
read dictionary
echo "Please enter grid file name:"
read grid

#store times of all the runs
time1=`./a.out $dictionary $grid | tail -1`
time2=`./a.out $dictionary $grid | tail -1`
time3=`./a.out $dictionary $grid | tail -1`
time4=`./a.out $dictionary $grid | tail -1`
time5=`./a.out $dictionary $grid | tail -1`

#calculate total
echo "Total Time:"
total=`expr $time1 + $time2`
total=`expr $total + $time3`
total=`expr $total + $time4`
total=`expr $total + $time5`
echo $total

#calculate average
average=`expr $total / 5`
echo "Average time in milliseconds: "
echo $average
