#include <stdio.h>
#include "simd.c"


int main(void){
	printf("testing the simd addition\n\n");
	float a[4] = {1.2, 3, 0, -4.};
	float b[4] = {-1.2, 9, 1.2, -8.};
	float * c;

	c = just_add(a,b);
	printf("%s plus %s is %s\n",
			vec2s(a),vec2s(b),vec2s(c));
	c = SIMD_add(a,b);
	printf("%s plus %s is %s\n",
			vec2s(a),vec2s(b),vec2s(c));
}
	
