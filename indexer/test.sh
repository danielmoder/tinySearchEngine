#!/bin/bash

touch indexFile.txt 
./indexer ../data/output indexFile.txt


touch newFile.txt 
./indextest indexFile.txt newFile.txt


sort indexFile.txt > s1.txt
sort newFile.txt > s2.txt
echo "Diff'ing..." 
echo "Sweet, sweet nothing:"
echo $(diff s2.txt s1.txt)
echo "see..? nope!"
