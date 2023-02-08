#!/bin/bash

specimen=./s21_cat
original=cat
log=log_cat.txt
texts="txt.txt test.txt Makefile"
flags="-b -e -n -s -t -v"

rm -f $log
counter=0
echo "--------------------------------------------------" >> $log
echo "--------------------------------------------------"
echo "  No Flags One File Test" >> $log
echo "  No Flags One File Test"
echo "--------------------------------------------------" >> $log
echo "--------------------------------------------------"
for text1 in $texts
do
    $specimen $text1 > log1
    $original $text1 > log2
    diff=`diff -s --suppress-common-lines -y log1 log2`
    if [[ $diff != "Files log1 and log2 are identical" ]]; then
        echo $text1 >> $log
        counter=$((counter+1))
    fi
done
echo >> $log
echo Number of testfails = $counter >> $log
echo Number of testfails = $counter
echo >> $log
echo >> $log
total=$((counter+total))
counter=0
echo "--------------------------------------------------" >> $log
echo "--------------------------------------------------"
echo "  One Flag One File Test" >> $log
echo "  One Flag One File Test"
echo "--------------------------------------------------" >> $log
echo "--------------------------------------------------"
for text1 in $texts
do
    for flag1 in $flags
    do
        $specimen $flag1 $text1 > log1
        $original $flag1 $text1 > log2
        diff=`diff -s --suppress-common-lines -y log1 log2`
        if [[ $diff != "Files log1 and log2 are identical" ]]; then
            echo $flag1 $text1 >> $log
            counter=$((counter+1))
        fi
    done
done
echo >> $log
echo Number of testfails = $counter >> $log
echo Number of testfails = $counter
echo >> $log
echo >> $log
total=$((counter+total))
counter=0
echo "--------------------------------------------------" >> $log
echo "--------------------------------------------------"
echo "  One Flag Two Files Test" >> $log
echo "  One Flag Two Files Test"
echo "--------------------------------------------------" >> $log
echo "--------------------------------------------------"
for text1 in $texts
do
    for flag1 in $flags
    do
        for text2 in $texts
        do
            $specimen $flag1 $text1 $text2 > log1
            $original $flag1 $text1 $text2 > log2
            diff=`diff -s --suppress-common-lines -y log1 log2`
            if [[ $diff != "Files log1 and log2 are identical" ]]; then
                echo $flag1 $text1 $text2 >> $log
                counter=$((counter+1))
            fi
        done
    done
done
echo >> $log
echo Number of testfails = $counter >> $log
echo Number of testfails = $counter
echo >> $log
echo >> $log
total=$((counter+total))
counter=0
rm -f log1 log2
echo "--------------------------------------------------" >> $log
echo "          The end for all of the test" >> $log
echo "--------------------------------------------------" >> $log
echo "          Total number of testfails = $total" >> $log
echo "--------------------------------------------------" >> $log
