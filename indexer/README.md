# README for indexer.c and indextest.c

*Daniel Moder, August 2016*

---
#### Functionality:
> **indexer.c** takes a directory of files from the crawler in the following format:
> > URL
> > 
> > Depth
> > 
> > < HTML >
> > 
> > ... 
>
> and outputs an indexfile of lines in the following format:
> > keyword docID1 count1 docID2 count2 ...
> 
> according to the words found in each page.
> 
> **indextest.c** takes the indexfile from indexer, reconstructs the index, and outputs to another indexfile

---

#### Compiling:
> Each file includes `lib/cs50ds.a` and `common.a`
> 
> (see Makefile for more information)

---
#### Usage examples
> `./indexer ../data/output indexFile.txt`
> 
> `./indextest indexFile.txt newFile.txt`

---
#### Assumptions
1. The first argument to `indexer` must be a directory created by the crawler, and must have files in the specified format
2. The first argument to `indextest` must have only lines with the specified format

