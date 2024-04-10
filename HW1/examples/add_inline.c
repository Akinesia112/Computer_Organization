#include <stdio.h>

int main ()
{
	int a=10, b=5;	
	//a = a + b;
	asm volatile(
		"add %[a], %[a], %[b]\n\t"	//AssemblerTemplate
		:[a] "+r"(a)			//OutputOperands, "=r" means write-only, "+r" means read/write
		:[b] "r"(b)			//InputOperands 
	);
	printf("%d\n", a);
	return 0;
}
