#include <stdio.h>
int main ()
{
    int a, b;
    FILE *input = fopen("../input/1.txt", "r");
    fscanf(input, "%d %d", &a, &b);
    fclose(input);
    //a = a / b;
    asm volatile(
        "div %[a], %[a], %[b]\n\t"    // Divide 'a' by 'b', result in 'a'
        : [a] "+r" (a)                // Output operand, 'a' can both read and write
        : [b] "r" (b)                 // Input operand, 'b'
        :                             // No clobbered registers specified
    );
    printf("%d\n", a);
    return 0;
}
