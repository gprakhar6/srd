#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "srd.h"

struct my_struct {
    char test[128];
    double x;
    float y;
    double arr[3];
    uint8_t t;
    double rmat[3][3];
};
#define LEN(x) (sizeof(x)/sizeof(x[0]))

#define SRD_STRUCT struct my_struct
struct srd_info_t my_struct_info[] =
{
    SRD_INFO_ELEM("test", test),
    SRD_INFO_ELEM("x", x),
    SRD_INFO_ELEM("y", y),
    SRD_INFO_ELEM("arr", arr),
    SRD_INFO_ELEM("t", t),
    SRD_INFO_ELEM("rmat", rmat)
};
#undef SRD_STRUCT

int main()
{
    int i, j;
    FILE *fp;
    struct my_struct d;
    fp = fopen("inp.txt", "r");
    if(fp == NULL) {
	printf("cvannot open inp.txt");
	exit(-1);
    }
    srd(fp, &d, my_struct_info, LEN(my_struct_info));
    printf("name = %s\n", d.test);
    printf("x = %lf\n", d.x);
    printf("y = %lf\n", d.y);
    for(i = 0; i < 3; i++)
	printf("arr[%d] = %lf\n", i, d.arr[i]);
    printf("t = %u\n", (uint32_t)d.t);
    for(i = 0; i < 3; i++) {
	for(j = 0; j < 3; j++) {
	    printf("%lf ", d.rmat[i][j]);
	}
	printf("\n");
    }
    return 0;
}
