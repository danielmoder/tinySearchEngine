# TESTING.md for crawler.c
*Daniel Moder, July 2016*


**Testing crawler at depth 0** 

*seed url: http://old-www.cs.dartmouth.edu/~cs50/index.html*
>
-  0   Fetched: http://old-www.cs.dartmouth.edu/~cs50/index.html
-  0     Saved: http://old-www.cs.dartmouth.edu/~cs50/index.html


*Files in output directory:*  1


----



**Testing crawler at depth 1** 

*seed url: http://old-www.cs.dartmouth.edu/~cs50/index.html*
>
-  0   Fetched: http://old-www.cs.dartmouth.edu/~cs50/index.html
-  0     Saved: http://old-www.cs.dartmouth.edu/~cs50/index.html
-  0     Added: http://old-www.cs.dartmouth.edu/~cs50/
-  0  EXTERNAL: https://canvas.dartmouth.edu/courses/15260
-  0  EXTERNAL: https://piazza.com/dartmouth/summer2016/cs50/home
-  0  EXTERNAL: https://gitlab.cs.dartmouth.edu
-  0  EXTERNAL: http://old-www.cs.dartmouth.edu/~cs50/Schedule.pdf
-  0     Added: http://old-www.cs.dartmouth.edu/~cs50/Lectures/
-  0     Added: http://old-www.cs.dartmouth.edu/~cs50/Reading/
-  0     Added: http://old-www.cs.dartmouth.edu/~cs50/examples/
-  0     Added: http://old-www.cs.dartmouth.edu/~cs50/Logistics/
-  0     Added: http://old-www.cs.dartmouth.edu/~cs50/Resources/
-  0     Added: http://old-www.cs.dartmouth.edu/~cs50/Labs/
-  0     Added: http://old-www.cs.dartmouth.edu/~cs50/Project/
-  0  EXTERNAL: http://tools.ietf.org/html/rfc1983
-  0  EXTERNAL: http://www.cs.dartmouth.edu/~ccpalmer/classes/cs55/Content/Purpose.html
-  0     Added: http://old-www.cs.dartmouth.edu/~cs50/Labs/Lab0-Preliminaries.html
-  0     Added: http://old-www.cs.dartmouth.edu/~xia/
-  1    Fetched: http://old-www.cs.dartmouth.edu/~xia/
-  1      Saved: http://old-www.cs.dartmouth.edu/~xia/
-  1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/Labs/Lab0-Preliminaries.html
-  1      Saved: http://old-www.cs.dartmouth.edu/~cs50/Labs/Lab0-Preliminaries.html
-  1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/Project/
-  1      Saved: http://old-www.cs.dartmouth.edu/~cs50/Project/
-  1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/Labs/
-  1      Saved: http://old-www.cs.dartmouth.edu/~cs50/Labs/
-  1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/Resources/
-  1      Saved: http://old-www.cs.dartmouth.edu/~cs50/Resources/
-  1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/Logistics/
-  1      Saved: http://old-www.cs.dartmouth.edu/~cs50/Logistics/
-  1     FAILED: http://old-www.cs.dartmouth.edu/~cs50/examples/
-  1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/Reading/
-  1      Saved: http://old-www.cs.dartmouth.edu/~cs50/Reading/
-  1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/Lectures/
-  1      Saved: http://old-www.cs.dartmouth.edu/~cs50/Lectures/
-  1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/
-  1      Saved: http://old-www.cs.dartmouth.edu/~cs50/


*Files in output directory:*  10


----



**Testing crawler at depth 0** 

*seed url: http://old-www.cs.dartmouth.edu/~cs50/index.html*
>
-  0   Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/index.html
-  0     Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/index.html


*Files in output directory:*  1


----



**Testing crawler at depth 1** 

*seed url: http://old-www.cs.dartmouth.edu/~cs50/index.html*
>
-  0   Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/index.html
-  0     Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/index.html
-  0     Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Computer_science.html
-  0     Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/C_(programming_language).html
-  0     Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Unix.html
-  0     Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Dartmouth_College.html
-  0     Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Hash_table.html
-  0     Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Linked_list.html
-  1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Linked_list.html
-  1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Linked_list.html
-  1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Hash_table.html
-  1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Hash_table.html
-  1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Dartmouth_College.html
-  1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Dartmouth_College.html
-  1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Unix.html
-  1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Unix.html
-  1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/C_(programming_language).html
-  1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/C_(programming_language).html
-  1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Computer_science.html
-  1      Saved: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Computer_science.html


*Files in output directory:*  7


----



