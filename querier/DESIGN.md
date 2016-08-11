### DESIGN.md for querier
*Daniel Moder, August 2016*

# Requirement Specs

The querier shall:

- execute from a command line with usage syntax
`./querier pageDirectory indexFilename`
- where pageDirectory is a directory produced by the crawler, and
where indexFilename is an index file produced by the indexer.
- load the index from indexFilename into an internal data structure.

- read search queries from stdin, one per line, until EOF.
- clean and parse each query according to the syntax described below.
- print the ‘clean’ query for user to see.
- use the index to identify the set of documents that satisfy the query, as described below.
if no documents satisfy the query, print No documents match.
otherwise, rank the resulting set of documents according to its score, as described below, and print the set of documents in decreasing rank order; for each, list the score, document ID and URL. (Obtain the URL by reading the first line of the relevant document file from the pageDirectory.)
The querier shall validate its command-line arguments:

> `pageDirectory` is a directory produced by the crawler, and
> 
> `indexFilename` is the name of a readable file.

The querier may assume that the input directory and files follow the designated formats.

- `pageDirectory` has files named 1, 2, 3, …, without gaps.
- The content of document files in pageDirectory follow the format as defined in the crawler specs; thus your code (to read a document file) need not have extensive error checking.
- The content of the file named by indexFilename follows our Index file format; thus your code (to recreate an index structure by reading a file) need not have extensive error checking.

# Design Specs
The querier is the culmination of the other programs and data types in this
project. The querier uses a directory full of text documents created and
formatted by **crawler** for retrieving URLS, and an indexFile created by
**indexer** to access the counts of each word in each document.



# Testing Plan
The following cases will be tested:
- a leading/trailing 'and'/'or'
- adjacent 'and'/'or's
- non-alphabetic characters
- nonsense words or words unlikely to be in the index
- valid entries of varying length




