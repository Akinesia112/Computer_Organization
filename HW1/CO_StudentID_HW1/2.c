#include <stdio.h>

int main() {
    int a[10] = {0}, b[10] = {0}, c[10] = {0};
    int arr_size = 10;
    FILE *input = fopen("../input/2.txt", "r");
    
    for(int i = 0; i < arr_size; i++) fscanf(input, "%d", &a[i]);
    for(int i = 0; i < arr_size; i++) fscanf(input, "%d", &b[i]);
    for(int i = 0; i < arr_size; i++) fscanf(input, "%d", &c[i]);
    fclose(input);
    int *p_a = &a[0];
    int *p_b = &b[0];
    int *p_c = &c[0];

    /* Original C code segment
    for (int i = 0; i < arr_size; i++){
    *p_c++ = *p_a++ / *p_b++;
    }
    */

    for (int i = 0; i < arr_size; i++) {

        asm volatile(
            "lw t0, 0(%1)\n\t"        // Load value at p_a into register t0
            "lw t1, 0(%2)\n\t"        // Load value at p_b into register t1
            "div t2, t0, t1\n\t"      // Divide t0 by t1, result in t2
            "sw t2, 0(%0)\n\t"        // Store result from t2 to the address at p_c
            : // No outputs, as we are manipulating memory directly
            : "r" (p_c), "r" (p_a), "r" (p_b) // Input pointers
            : "t0", "t1", "t2", "memory" // Clobber list
        );
        p_a++;
        p_b++;
        p_c++;
    }

    p_c = &c[0];
    for (int i = 0; i < arr_size; i++) {
        printf("%d ", *p_c++);
    }
    printf("\n");
    return 0;
}
