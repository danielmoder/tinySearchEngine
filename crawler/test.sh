#!/bin/bash
make clean>/dev/null
make>/dev/null

SEEDURL1="http://old-www.cs.dartmouth.edu/~cs50/index.html"
SEEDURL2="http://old-www.cs.dartmouth.edu/~cs50/data/tse/index.html"
#cat TESTING.md | grep -i saved | sort | uniq -c
echo "# TESTING.md for crawler.c"
echo "*Daniel Moder, July 2016*"
echo $'\n'


for i in `seq 0 1`;
do
    echo "**Testing crawler at depth" $i"**"  $'\n'
    echo $"*seed url: $SEEDURL1*"
    mkdir output1_$i
    echo ">"
    ./crawler $SEEDURL1 output1_$i $i

    OUT=`ls -l output1_$i | wc -l`
    COUNT=`expr $OUT - 1`

    echo $'\n'
    echo $"*Files in output directory:* " $COUNT
    echo $'\n'
    echo ----
    echo $'\n\n'
    
done

for i in `seq 0 1`;
do
    echo "**Testing crawler at depth" $i"**" $'\n'
    echo $"*seed url: $SEEDURL1*"
    mkdir output2_$i
    echo ">"
    ./crawler $SEEDURL2 output2_$i $i

    OUT=`ls -l output2_$i | wc -l`
    COUNT=`expr $OUT - 1`

    echo $'\n'
    echo $"*Files in output directory:* " $COUNT
    echo $'\n'
    echo ----
    echo $'\n\n'

done


make clean>/dev/null
rm -f output*/*
rm -d output*
