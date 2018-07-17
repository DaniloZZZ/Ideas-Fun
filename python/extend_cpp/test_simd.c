#include <stdio.h>
#include <time.h>
#include "simd.c"


int main(void){
	printf("testing the simd addition\n\n");
	int times = 100000000;
	float a[4] = {1.2, 3, 0, -4.};
	float b[4] = {-1.2, 9, 1.2, -8.};
	float * c;

	c = just_add(a,b);
	printf("%s plus %s is %s\n",
			vec2s(a),vec2s(b),vec2s(c));
	c = SIMD_add(a,b);
	printf("%s plus %s is %s\n",
			vec2s(a),vec2s(b),vec2s(c));

	printf("Now looping for %d times\n",times);
	int  volatile i = 0;
	//time_t start,end;
	clock_t start,end;
	double dif;

	//time (&start);
	start = clock();
	while(i<times){
		i++;
		c = SIMD_add(a,b);
	}
	end = clock();
	//time (&end);
	//dif = difftime (end,start);
	dif = (end-start)/(double)CLOCKS_PER_SEC;
	printf ("SIMD took %.5f seconds to run.\n", dif );

	//time (&start);
	start = clock();
	i=0;
	while(i<times){
		i++;
		c = just_add(a,b);
	}
	end = clock();
	//time (&end);
	//dif = difftime (end,start);
	dif = (end-start)/(double)CLOCKS_PER_SEC;
	printf ("Loop took %8.5f seconds to run.\n", dif );
	printf ("the iter time is %e\n",dif/(double)times);
}
	
