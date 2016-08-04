The indexer shall:
- execute from a command line with usage syntax:
`./indexer pageDirectory indexFilename`
- where pageDirectory is a directory produced by the crawler, and
- where indexFilename is the name of a file into which the index should be written.
- read documents from the pageDirectory, each of which has a unique document ID, wherein the document id starts at 1 and increments for each new document, and the filename is of form pageDirectory/id,
    and the first line of the file is the URL,
    and the second line of the file is the depth,
    and the rest of the file is the page content.
- build an inverted-index data structure mapping from words to (documentID, count) pairs, wherein each count represents the number of occurrences of the given word in the given document. Ignore words with fewer than three characters, and NormalizeWord before indexing.
    create a file indexFilename and write the index to that file, in the format described below.
- The indexer shall validate its command-line arguments:
`pageDirectory` is a directory produced by the crawler (see below), and
`indexFilename` is the name of a writeable file.

The indexer may assume that:
- pageDirectory has files named 0, 1, 2, 3, …, without gaps.
- The content of files in pageDirectory follow the format as defined in the crawler specs; thus your code (to create a WebPage by reading a file) need not have extensive error checking.

The index tester shall:
- execute from a command line with usage syntax:
`./indextest oldIndexFilename newIndexFilename`
where oldIndexFilename is the name of a file produced by the indexer, and
where newIndexFilename is the name of a file into which the index should be written.
- load the index from the oldIndexFilename into an inverted-index data structure.
- create a file newIndexFilename and write the index to that file, in the format described below.
- It need not validate its command-line arguments other than to ensure that it receives precisely two arguments; it may simply try to open the oldIndexFilename for reading and, later, try to open the newIndexFilename for writing. You may use indextest.sh (provided) to verify that the output is identical to (or equivalent to) the input.

The index tester may assume that
- The content of the index file follows the format specified below; thus your code (to recreate an index structure by reading a file) need not have extensive error checking.