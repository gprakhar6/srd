#ifndef __STRUCT_READ_H__
#define __STRUCT_READ_H__

#include <stdint.h>
#include <stddef.h>

#define MAX_NAME_LEN_STRUCT_MEMBER (128)

struct srd_info_t {
    char name[MAX_NAME_LEN_STRUCT_MEMBER];
    char fmt[16];
    int elem_sz;
    int offset;
};

// char* is read as %[^n], we are assumig file to have one string only
#define SRD_FMT(x) (_Generic(((SRD_STRUCT *)0)->x,		\
			     char		: "%c",		\
			     char*		: "%[^\n]",	\
			     uint8_t		: "%hhu",	\
			     uint8_t*		: "%hhu",	\
			     uint8_t(*)[]	: "%hhu",	\
			     uint16_t		: "%hu",	\
			     uint16_t*		: "%hu",	\
			     uint16_t(*)[]	: "%hu",	\
			     uint32_t		: "%u",		\
			     uint32_t*		: "%u",		\
			     uint32_t(*)[]	: "%u",		\
			     uint64_t		: "%lu",	\
			     uint64_t*		: "%lu",	\
			     uint64_t(*)[]	: "%lu",	\
			     int8_t		: "%hhd",	\
			     int8_t*		: "%hhd",	\
			     int8_t(*)[]	: "%hhd",	\
			     int16_t		: "%hd",	\
			     int16_t*		: "%hd",	\
			     int16_t(*)[]	: "%hd",	\
			     int32_t		: "%d",		\
			     int32_t*		: "%d",		\
			     int32_t(*)[]	: "%d",		\
			     int64_t		: "%ld",	\
			     double		: "%lf",	\
			     double*		: "%lf",	\
			     double(*)[]	: "%lf",	\
			     float		: "%f",		\
			     float*		: "%f",		\
			     float(*)[]		: "%f",		\
			     default    : ""))

// sizeof(char *) has no meaning. so putting 0
#define SRD_ELEM_SZ(x) _Generic(((SRD_STRUCT *)0)->x,			\
			        char*	        : 0,			\
				uint8_t*	: sizeof(uint8_t),	\
				uint8_t(*)[]	: sizeof(uint8_t),	\
				uint16_t*	: sizeof(uint16_t),	\
				uint16_t(*)[]	: sizeof(uint16_t),	\
				uint32_t*	: sizeof(uint32_t),	\
				uint32_t(*)[]	: sizeof(uint32_t),	\
				uint64_t*	: sizeof(uint64_t),	\
				uint64_t(*)[]	: sizeof(uint64_t),	\
				int8_t*		: sizeof(int8_t),	\
				int8_t(*)[]	: sizeof(int8_t),	\
				int16_t*	: sizeof(int16_t),	\
				int16_t(*)[]	: sizeof(int16_t),	\
				int32_t*	: sizeof(int32_t),	\
				int32_t(*)[]	: sizeof(int32_t),	\
				double*		: sizeof(double),	\
				double(*)[]	: sizeof(double),	\
				float*		: sizeof(float),	\
				float(*)[]	: sizeof(float),	\
				default		: sizeof(((SRD_STRUCT *)0)->x))

#define SRD_INFO_ELEM(n, x) {n, SRD_FMT(x), SRD_ELEM_SZ(x),	\
	    offsetof(SRD_STRUCT, x)}

int srd(FILE *fp, const void *buf, const struct srd_info_t *srd,
	const int n);

#endif
