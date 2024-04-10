#include<stdio.h>
int main()
{ 
    int i = 0;
    int h[9] = {0}, x[6] = {0}, y[6] = {0}; 
    FILE *input = fopen("../input/4.txt", "r");
    for(i = 0; i < 9; i++) fscanf(input, "%d", &h[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &x[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &y[i]);
    fclose(input);
    
    int *p_x = &x[0];
    int *p_h = &h[0];
    int *p_y = &y[0];
    
    asm volatile (
        "mv t1, %0\n"         // t1 points to h
        "mv t2, %1\n"         // t2 points to x
        "mv t3, %2\n"         // t3 points to y

        // Compute y[0] = h[0]*x[0] + h[1]*x[2] + h[2]*x[4]
        "lw a1, 0(t1)\n"
        "lw a2, 0(t2)\n"
        "mul a3, a1, a2\n"
        "lw a1, 4(t1)\n"
        "lw a2, 8(t2)\n"
        "mul a4, a1, a2\n"
        "add a3, a3, a4\n"
        "lw a1, 8(t1)\n"
        "lw a2, 16(t2)\n"
        "mul a4, a1, a2\n"
        "add a3, a3, a4\n"
        "sw a3, 0(t3)\n"

        // Compute y[1] = h[0]*x[1] + h[1]*x[3] + h[2]*x[5]
        "lw a1, 0(t1)\n"
        "lw a2, 4(t2)\n"
        "mul a3, a1, a2\n"
        "lw a1, 4(t1)\n"
        "lw a2, 12(t2)\n"
        "mul a4, a1, a2\n"
        "add a3, a3, a4\n"
        "lw a1, 8(t1)\n"
        "lw a2, 20(t2)\n"
        "mul a4, a1, a2\n"
        "add a3, a3, a4\n"
        "sw a3, 4(t3)\n"

        // Compute y[2] = h[3]*x[0] + h[4]*x[2] + h[5]*x[4]
        "lw a1, 12(t1)\n"
        "lw a2, 0(t2)\n"
        "mul a3, a1, a2\n"
        "lw a1, 16(t1)\n"
        "lw a2, 8(t2)\n"
        "mul a4, a1, a2\n"
        "add a3, a3, a4\n"
        "lw a1, 20(t1)\n"
        "lw a2, 16(t2)\n"
        "mul a4, a1, a2\n"
        "add a3, a3, a4\n"
        "sw a3, 8(t3)\n"

        // Compute y[3] = h[3]*x[1] + h[4]*x[3] + h[5]*x[5]
        "lw a1, 12(t1)\n"
        "lw a2, 4(t2)\n"
        "mul a3, a1, a2\n"
        "lw a1, 16(t1)\n"
        "lw a2, 12(t2)\n"
        "mul a4, a1, a2\n"
        "add a3, a3, a4\n"
        "lw a1, 20(t1)\n"
        "lw a2, 20(t2)\n"
        "mul a4, a1, a2\n"
        "add a3, a3, a4\n"
        "sw a3, 12(t3)\n"

        // Compute y[4] = h[6]*x[0] + h[7]*x[2] + h[8]*x[4]
        "lw a1, 24(t1)\n"
        "lw a2, 0(t2)\n"
        "mul a3, a1, a2\n"
        "lw a1, 28(t1)\n"
        "lw a2, 8(t2)\n"
        "mul a4, a1, a2\n"
        "add a3, a3, a4\n"
        "lw a1, 32(t1)\n"
        "lw a2, 16(t2)\n"
        "mul a4, a1, a2\n"
        "add a3, a3, a4\n"
        "sw a3, 16(t3)\n"

        // Compute y[5] = h[6]*x[1] + h[7]*x[3] + h[8]*x[5]
        "lw a1, 24(t1)\n"
        "lw a2, 4(t2)\n"
        "mul a3, a1, a2\n"
        "lw a1, 28(t1)\n"
        "lw a2, 12(t2)\n"
        "mul a4, a1, a2\n"
        "add a3, a3, a4\n"
        "lw a1, 32(t1)\n"
        "lw a2, 20(t2)\n"
        "mul a4, a1, a2\n"
        "add a3, a3, a4\n"
        "sw a3, 20(t3)\n"
        : 
        : "r"(h), "r"(x), "r"(y)
        : "a1", "a2", "a3", "a4", "t1", "t2", "t3"
    );


    p_y = &y[0];
    for(i = 0; i < 6; i++)
        printf("%d ", *p_y++);
    printf("\n");
    return 0; 
 
}
