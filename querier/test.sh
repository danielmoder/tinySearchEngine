#!/bin/bash

echo "Test queries:"
while read line; do
    echo $line
done < testQueries.txt
echo

echo "Respective outputs:"
echo 
./querier ../data/output ../data/indexFile < testQueries.txt

