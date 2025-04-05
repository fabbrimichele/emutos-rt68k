typedef unsigned char   UBYTE;                  /*  Unsigned byte       */
typedef unsigned long   ULONG;                  /*  unsigned 32 bit word*/
typedef int             BOOL;                   /*  boolean, TRUE or FALSE */
typedef short int       WORD;                   /*  signed 16 bit word  */
typedef unsigned short  UWORD;                  /*  unsigned 16 bit word*/
typedef long            LONG;                   /*  signed 32 bit word  */

#define MAKE_UWORD(hi,lo) (((UWORD)(UBYTE)(hi) << 8) | (UBYTE)(lo))
#define MAKE_ULONG(hi,lo) (((ULONG)(UWORD)(hi) << 16) | (UWORD)(lo))
#define LOWORD(x) ((UWORD)(ULONG)(x))
#define HIWORD(x) ((UWORD)((ULONG)(x) >> 16))
#define LOBYTE(x) ((UBYTE)(UWORD)(x))
#define HIBYTE(x) ((UBYTE)((UWORD)(x) >> 8))
#define IS_ODD(x) ((x) & 1)
#define IS_ODD_POINTER(x) IS_ODD((ULONG)(x))
#define IS_32BIT_POINTER(x) ((ULONG)(x) & 0xff000000)