#include <stdio.h>

/* function implementation of calculate_area(length, width) */
float calculate_area(float b, float c)
{
        return (b * c);
}
/* end function implementation */

int main(void)
{
	float l, w, a;
	scanf("%f %f", &l, &w);
	a = calculate_area(l, w);
	printf("%f", a);
}
