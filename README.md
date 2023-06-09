# Reads a simple C structure from a file


``` cat inp.txt
MEMBER_NAME_1 : VALUE_1
// Comments start like this. Single line per comment
MEMBER_NAME_2 : VALUE_2
// can have this initial space
// and delimeter is either of [;, ]. Use it as per visual convenience
  MEMBER_NAME_3 : VALUE_3[0], VALUE_3[1], VALUE_3[2]
```

see inp.txt for example

If you want to read a structure, you have declare an array
of srd_info_t. First member tells the identifier used in the file
and second is the member name. You also have to wrap this declaration
around #define SRD_STRUCT and make sure to #undef it, so that further
such declaration are possible without mixup. See example below.
```c
struct my_struct {
    char test[128];
    double x;
    float y;
    double arr[3];
    uint8_t t;
    double rmat[3][3];
};

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
```

This program mostly uses the preprocessor capabilities of C11.

Use the following call to fill the structure passed as buf. Open
the FILE *fp and pass it to this funciton. It does not close the
fp
```c
/**
 * fp: file descriptor
 * buf: Where to read the input. Pass the structure you want to fill
 * srd: is the srd_info_t array you need to declare
 * n: it is the sizeof the srd array
*/
int srd(FILE *fp, const void *buf, const struct srd_info_t *srd,
	const int n);
	
```