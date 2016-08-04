# Testing for indexer.c and indextest.c:

*Daniel Moder, August 2016*



Test script `test.sh`:
```
#!/bin/bash

touch indexFile.txt 					# make sure file exists
./indexer ../data/output indexFile.txt	# run indexer
cat indexFile.txt

touch newFile.txt						# make sure file exists
./indextest indexFile.txt newFile.txt	# run indextest
cat indexFile.txt

sort indexFile.txt > s1.txt				# sort
sort newFile.txt > s2.txt

echo "sweet, sweet nothing: \n"
echo $(diff s2.txt s1.txt)				# find the differences
echo "see..? nope!\n"
```

indexFile.txt and newFile.txt samples:

- implementation 8 1 
- pete 7 1 
- retry 7 1 
- johannes 7 2 
- verbose 7 1 
- bullet 7 1 
- dan 7 1 
- magical 7 1 
- linker 7 1 

...

- in 0 9 1 17 2 2 4 2 5 20 6 40 7 1 8 1 9 9
- project 0 2 1 2 2 1 3 3 4 1 5 1 6 16 7 1 8 1 9 2
- labs 0 1 2 1 3 1 4 3 5 1 6 4 7 2 8 1 9 1
- reading 0 1 2 1 3 1 4 1 5 1 6 5 7 2 8 1 9 1
- lectures 0 1 2 1 3 1 4 1 5 1 6 5 7 4 8 3 9 1
- gitlab 0 1 2 1 3 1 4 1 5 3 6 6 7 1 8 2 9 1


### Output:
>Diff'ing...
>
>Sweet, sweet nothing:
>
>see..? nope!




