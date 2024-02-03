#include <stdio.h>

void process_int(int num) {
    printf("Processing integer: %d\n", num);
}

void process_float(float num) {
    printf("Processing float: %f\n", num);
}

void process_string(const char* str) {
    printf("Processing string: %s\n", str);
}

#define process(x) _Generic((x), \
    int: process_int, \
    float: process_float, \
    const char*: process_string \
)(x)

int main() {
    int a = 10;
    float b = 3.14;
    const char* c = "Hello, World!";

    process(a);  // Calls process_int
    process(b);  // Calls process_float
    process(c);  // Calls process_string

    return 0;
}
