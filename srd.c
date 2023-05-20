#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "srd.h"

#define MAX_VALUE_LEN 128

static int search_name(const char *name,
		       const struct srd_info_t *srd, const int n)
{
    int i, ret;
    ret = -1;

    for(i = 0; i < n; i++) {
	if(strcmp(name, srd[i].name) == 0) {
	    ret = i;
	    break;
	}
    }
    return ret;
}
int srd1(FILE *fp, const void *buf, const struct srd_info_t *srd,
	 struct srd_field_t *fl, const int n)
{
    int ret, i, en, idx;
    uint8_t *buf8 = (uint8_t *)buf;
    char name[MAX_NAME_LEN_STRUCT_MEMBER];
    char value[MAX_VALUE_LEN];
    typeof(srd) e;
    if(fp == NULL || n <= 0 || srd == NULL || buf == NULL) {
	printf("bad arg to srd\n");
	ret = -2;
	goto finish;
    }
    while(1) {
    start:
	fscanf(fp, "%*[ \t\r\n]");
	if(fscanf(fp, "%[^:\t ]%*[:\t ]", name) <= 0) {
	    ret = 0;
	    goto finish;
	}
	if((name[0] == '/') && (name[1] == '/')) {
	    fscanf(fp, "%*[^\r\n]%*[\r\n]");
	    goto start;
	}
	if((idx = search_name(name, srd, n)) < 0) {
	    ret = -1;
	    goto finish;
	}
	e = &srd[idx];
	//printf("Reading %s\n", e->name);
	if(fl != NULL)
	    strcpy(fl[idx].name, e->name);
	en = 0;
	while(fscanf(fp, "%[^\t\r\n,;]%*[ \t,;]", value) > 0) {
	    //printf("Reading value=%s, with fmt=%s\n", value, e->fmt);
	    if(sscanf(value, e->fmt,
		      buf8 + e->offset + en*e->elem_sz) > 0) {
		en++;
	    }
	}
    }

finish:
    return ret;
}
