#include <stdio.h>
// This code is for utilising SIMD operations
// Danil Lykov, 07/2018
//

float * SIMD_add(float * a, float *b)
{
	//printf("simd adding two vecs at %p, %p\n",a,b);
	static float res[4];
	// Perform vector addition
	// SSE registers are for 4-len float vectors
	//
	// This can be optimised for memory
	__asm__ volatile
	(
	 "movups %[a], %%xmm0\n\t"
	 "movups %[b], %%xmm1\n\t"
	 "addps %%xmm1, %%xmm0\n\t"
	 "movups %%xmm0, %[res]\n\t"
	 : [res]"=m"(*res)
	 : [a]"m"(*a), [b]"m"(*b)
	 : "%xmm0","%xmm1"
	);

	return res;
}

float * just_add(float * a, float *b)
{
	//printf("adding vecs in loop at %p, %p\n",a,b);
	// TODO:does value wiped without static?
	static float res[4];
	//for (int i=0;i<4;i++)
	for (int i=3;i>=0; --i)
	{
		res[i] = a[i]+b[i];
	}
	return res;
}
char * vec2s(float *v)
{
	char *s = malloc(30);
	if (!s)
		return NULL;

	s[0]='[';
	for (char i=0; i<4; i++){
		// This fails when called from python but ok from unix
		// TODO: get rid of self referencing s
		sprintf(s, "%s %4.2f",s,v[i]);
	}
	sprintf(s, "%s]",s);
	return s;
}

