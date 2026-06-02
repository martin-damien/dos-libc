#ifndef TYPES_H
#define TYPES_H

typedef signed char     int8_t;     /* -128             +127           */
typedef unsigned char   uint8_t;    /* 0                +255           */
typedef signed short    int16_t;    /* -32768           +32767         */
typedef unsigned short  uint16_t;   /* 0                +65 535        */
typedef signed long     int32_t;    /* -2 147 483 648   +2 147 483 647 */
typedef unsigned long   uint32_t;   /* 0                +4 294 967 295 */

typedef int bool;
#define true  1
#define false 0

#define STATIC_ASSERT(cond, name) \
    typedef char static_assert_##name[(cond) ? 1 : -1]

STATIC_ASSERT(sizeof(int8_t)  == 1, int8_wrong_size);
STATIC_ASSERT(sizeof(int16_t) == 2, int18_wrong_size);
STATIC_ASSERT(sizeof(int32_t) == 4, int32_wrong_size);

#endif
