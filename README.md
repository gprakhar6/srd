# Reads a simple structure of format

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