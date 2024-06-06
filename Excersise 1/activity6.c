#include <stdio.h>

/* function-like macro implementation of SUM(A,B) */
#define SUM(A, B) (A + B)
/* end function-like macro implementation */

int main(void)
{
	int a, b, s;
	scanf("%d %d", &a, &b);
	s = SUM(a, b);
	printf("%d", s);
}
