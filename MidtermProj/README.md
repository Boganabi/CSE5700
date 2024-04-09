# To run this code:

If you do not see `lex.yy.c`:
- run `flex scanner.l` (you may need to use `sudo apt install flex` if you haven't already)

If you do not see `parser.tab.c` or `parser.tab.h`:
- run `bison -d parser.y` (you may need to use `sudo apt install bison` if you haven't already)

Compile everything: `gcc -o compile lex.yy.c parser.tab.c main.c -lfl`

Run: `cat foo.c | ./compile`