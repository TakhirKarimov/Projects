#!/bin/sh

specimen=./s21_grep
original=grep
pat1="test.txt"
pat2="test.txt"
log=log_grep.txt
texts="test_2.txt test.txt"
flags="-e -i -v -c -l -n -h -s"

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
    for pattern1 in $pat1
    do
        $specimen $pattern1 $text1 > log1
        $original $pattern1 $text1 > log2
        diff=`diff -s --suppress-common-lines -y log1 log2`
        if ! [[ $diff == "Files log1 and log2 are identical" ]]; then
            echo $pattern1 $text1 >> $log
            counter=$((counter+1));
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
echo "  One Flag One File Test" >> $log
echo "  One Flag One File Test"
echo "--------------------------------------------------" >> $log
echo "--------------------------------------------------"
for text1 in $texts
do
    for flag1 in $flags
    do
        for pattern1 in $pat1
        do
            $specimen $flag1 $pattern1 $text1 > log1
            $original $flag1 $pattern1 $text1 > log2
            diff=`diff -s --suppress-common-lines -y log1 log2`
            if ! [[ $diff == "Files log1 and log2 are identical" ]]; then
                echo $flag1 $pattern1 $text1 >> $log
                counter=$((counter+1));
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
            for pattern1 in $pat1
            do
                $specimen $flag1 $pattern1 $text1 $text2 > log1
                $original $flag1 $pattern1 $text1 $text2 > log2
                diff=`diff -s --suppress-common-lines -y log1 log2`
                if ! [[ $diff == "Files log1 and log2 are identical" ]]; then
                    echo $flag1 $pattern1 $text1 $text2 >> $log
                    counter=$((counter+1));
                fi
            done
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
echo "--------------------------------------------------" >> $log
echo "--------------------------------------------------"
echo "  Two Flags One Files (Two for '-e' flag) Test" >> $log
echo "  Two Flags One Files (Two for '-e' flag) Test"
echo "--------------------------------------------------" >> $log
echo "--------------------------------------------------"
for text1 in $texts
do
    for flag1 in $flags
    do
        for flag2 in $flags
        do
            for pattern1 in $pat1
            do
                for pattern2 in $pat2
                do
                    $specimen $flag1 $pattern1 $flag2 $pattern2 $text1 > log1
                    $original $flag1 $pattern1 $flag2 $pattern2 $text1 > log2
                    diff=`diff -s --suppress-common-lines -y log1 log2`
                    if ! [[ $diff == "Files log1 and log2 are identical" ]]; then
                        echo $flag1 $pattern1 $flag2 $pattern2 $text1 >> $log
                        counter=$((counter+1));
                    fi
                done
            done
        done
    done
done
echo >> $log
echo Number of testfails = $counter >> $log
echo Number of testfails = $counter
echo >> $log
echo >> $log
total=$((counter+total))
rm -f log1 log2
echo "--------------------------------------------------" >> $log
echo "          The end for all of the test" >> $log
echo "--------------------------------------------------" >> $log
echo "          Total number of testfails = $total" >> $log
echo "--------------------------------------------------" >> $log
