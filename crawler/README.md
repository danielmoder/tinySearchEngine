# README.md for crawler.c
*Daniel Moder, July 2016*

---

**1. Functionality:**

This crawler is designed to automatically navigate the web and save the html
of the pages it visits. 

It takes 3 arguments: 
1. the seed url, the page at which to start the crawl
2. the output directory, to which it will write the html, and
3. the max depth of the crawl, starting at 0

---

**2. Compiling:** *(see Makefile for more information)*

`gcc -Wall -pedantic -std=c11 -ggdb   -c -o crawler.o crawler.c`

---

**3. Usage:**

Example command lines:

`./crawler http://old-www.cs.dartmouth.edu/~cs50/index.html output 3 `
`./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/index.html output 3 `

---

**4. Assumptions:**

1. Assigned depth must be greater than 0 and less than 4
2. Output directory must exist prior to execution

---

**5. Limitations:**

1. Due to the one-second latency between page retrievals, deep crawls should be expected to take a long time

---

