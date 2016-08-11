# README for querier.c

*Daniel Moder, August 2016*

---
#### Functionality:
>   **querier.c** 


---

#### Compiling:
> (see Makefile for more information)

---
#### Usage examples
`./querier ../data/output ../data/indexFile.txt`
> `dartmouth college or computer science`

---
#### Assumptions
1. The directory must have been made by the crawler, or contain files in the 
same format. (see crawler for more info)
2. The indexFile must have been made by indexer, or be in the same format.
(see indexer for more info)
3. Query cannot be longer than 199 characters. Any characters beyond the 199th
will be ignored.

---
#### "Non-assumptions"
1. The queried word need not be in index. A warning will be issued if this is
the case, however, and the score of that 'and' clause will be zero.

