#include<stdio.h>
int main()
{ 
    int f, i, j;
    int h[9] = {0}, x[6] = {0}, y[6] = {0}; 
    FILE *input = fopen("../input/3.txt", "r");
    for(i = 0; i < 9; i++) fscanf(input, "%d", &h[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &x[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &y[i]);
    fclose(input);
    int *p_x = &x[0] ;
    int *p_h = &h[0] ;
    int *p_y = &y[0] ;
    for (i = 0; i < 3; i++){ 
        for (j = 0; j < 2; j++){        	
            for (f = 0; f < 3; f++)
                asm volatile (
                    "lw t0, 0(%1)\n\t"          // Load h[i*3 + f] into t0
                    "lw t1, 0(%2)\n\t"          // Load x[f*2 + j] into t1
                    "mul t2, t0, t1\n\t"        // Multiply t0 and t1, result in t2
                    "lw t3, 0(%0)\n\t"          // Load y[i*2 + j] into t3
                    "add t3, t3, t2\n\t"        // Add t2 to t3
                    "sw t3, 0(%0)"              // Store t3 into y[i*2 + j]
                    : // No output operands, we are directly modifying memory through pointers
                    : "r" (p_y + i*2 + j), "r" (p_h + i*3 + f), "r" (p_x + f*2 + j) // Input operands
                    : "t0", "t1", "t2", "t3", "memory" // Clobbered registers and memory
                );


	}
    }
    p_y = &y[0];
    for(i = 0; i < 6; i++)
    printf("%d ", *p_y++);
    printf("\n");
    return 0; 
 
}