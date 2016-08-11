# README for querier.c

*Daniel Moder, August 2016*

---
#### Functionality:
> **querier.c** takes a crawler directory and an index file as command-line 
arguments, and queries from the user. It will return a list of the documents
from the crawler directory that match the query and scores assigned to them
based on counts of matching words.

> **Query syntax:**
> The queries will be handled as a series of phrases separated by 'or'.
Documents will be said to be "matching" for one of these phrases only if they 
contain each word in the phrase. Documents that match at least one phrase, but
not every phrase, will still match, but documents that match more phrases will
have a higher score.



---

#### Compiling:
> (see Makefile for more information)

---
#### Usage examples
`./querier ../data/output ../data/indexFile.txt`
`> dartmouth college or computer science`

---
#### Assumptions
1. The directory must have been made by the crawler, or contain files in the 
same format. (see crawler for more info)
2. The indexFile must have been made by indexer, or be in the same format.
(see indexer for more info)
3. Query cannot be longer than 199 characters. Any characters beyond the 199th
will be ignored.
4. The query cannot contain non-alphabetic characters, cannot begin or end with
'and'/'or', and cannot contain adjacent 'and'/'or's

---
#### "Non-assumptions"
1. The queried word need not be in index. A warning will be issued if this is
the case, however, and the score of that 'and' clause will be zero.

