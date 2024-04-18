/* since c-- isnt a real language, heres just an example test to analyze with */

extern int printf(char *format, ...);

int add(int a, int b) {
    return a + b;
}

void main() {
    int x = 5;
    int y = 10;
    int z = add(x, y);
    printf("Result: %d\n", z);
}
