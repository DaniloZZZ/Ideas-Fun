#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// This code is for utilising SIMD operations
// Danil Lykov, 07/2018
//

float * SIMD_add(float * a, float *b)
{
	//printf("simd adding two vecs at %p, %p\n",a,b);
	static float res[4];
	//
	// Perform vector addition using AVX(Advanced Vector Extensions)
	// SSE registers are for 4-len float vectors
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
	// This can be optimised for memory
	return res;
}

float * just_add(float * a, float *b)
{
	//printf("adding vecs in loop at %p, %p\n",a,b);
	// TODO:does value wiped without static?
	static float res[4];

	// The downcounting variant seems to be not optimised by GCC
	//for (int i=0;i<4;i++)
	for (int i=3;i>=0; --i)
	{
		res[i] = a[i]+b[i];
	}
	return res;
}
char * vec2s(float *v)
{
	char *s = (char*)malloc(30);
	char t[10];
	if (!s)
		return NULL;

	s[0]='[';
	for (int i=0; i<4; i++){
		// This fails when called from python but ok from unix
		// TODO: get rid of self referencing s
		sprintf(t, " %4.2f,",v[i]);
		strcat(s,t);
	}
	strcat(s, "]");
	return s;
}

