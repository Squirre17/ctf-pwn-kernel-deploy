#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define __USE_COLOR__
#ifdef __USE_COLOR__

#define cBLK "\x1b[0;30m"  /* black  */    
#define cRED "\x1b[0;31m"  /* red    */   
#define cGRE "\x1b[0;32m"  /* green  */   
#define cORA "\x1b[0;33m"  /* orange */   
#define cBLU "\x1b[0;34m"  /* blue   */   
#define cPUR "\x1b[0;35m"  /* purple */   
#define cCYA "\x1b[0;36m"  /* cyan   */   
#define cWHI "\x1b[0;37m"  /* white  */   

#define cBLKp "\x1b[1;90m"  /* black  plus */ 
#define cREDp "\x1b[1;91m"  /* red    plus */ 
#define cGREp "\x1b[1;92m"  /* green  plus */ 
#define cORAp "\x1b[1;93m"  /* orange plus */ 
#define cBLUp "\x1b[1;94m"  /* blue   plus */ 
#define cPURp "\x1b[1;95m"  /* purple plus */ 
#define cCYAp "\x1b[1;96m"  /* cyan   plus */ 
#define cWHIp "\x1b[1;97m"  /* white  plus */ 
#define cRST  "\x1b[0m"      /* reset       */

#endif /* __USE_COLOR__ */


#define SAY(x...)     printf(x) 
#define SAYL(x...)    {printf(x); puts("");}

/* Show a prefixed warning. */

#define WARN(x...) do { \
    SAY(cORA "[!] " cWHIp "WARNING: " cRST x); \
    SAY(cRST "\n"); \
  } while (0)

/* Show a prefixed "doing something" message. */

#define ACT(x...) do { \
    SAY(cBLU "[*] " cRST x); \
    SAY(cRST "\n"); \
  } while (0)

/* Show a prefixed "success" message. */

#define OK(x...) do { \
    SAY(cGRE "[+] " cRST x); \
    SAY(cRST "\n"); \
  } while (0)

/* Show a prefixed "debug" message. */

#define DBG(x...) do {                        \
    SAY(cPUR "[x] " cRST);                    \
    SAY("%s(), %s:%u : ",                     \
        __FUNCTION__, __FILE__, __LINE__ );   \
    SAY(cRST x "\n");                         \
  } while (0)

/* Show a prefixed fatal error message . */

#define ERR(x...) do {                        \
    SAY(cRED "\n[-] " cRST);                    \
    SAY("%s(), %s:%u : ",                     \
        __FUNCTION__, __FILE__, __LINE__ );   \
    SAYL(cRST x);                         \
  } while (0)
/* Die with a verbose non-OS fatal error message. */

#define FATAL(x...) do { \
    SAY(cRED "\n[-] PROGRAM ABORT : " cWHI x); \
    SAY(cRED "\n         Location : " cRST "%s(), %s:%u\n\n", \
         __FUNCTION__, __FILE__, __LINE__); \
    exit(1); \
  } while (0)

/* Die by calling abort() to provide a core dump. */

#define ABORT(x...) do { \
    SAY(cREDp "\n[-] PROGRAM ABORT : " cWHI x); \
    SAY(cREDp "\n    Stop location : " cRST "%s(), %s:%u\n\n", \
         __FUNCTION__, __FILE__, __LINE__); \
    abort(); \
  } while (0)

/* Die with a verbose OS fatal error message. */

#define PANIC(x...) do { \
    fflush(stdout); \
    SAY(cREDp "\n[-]  SYSTEM ERROR : " \
         cWHI x); \
    SAY(cREDp "\n    Stop location : " cRST "%s(), %s:%u\n", \
         __FUNCTION__, __FILE__, __LINE__); \
    SAY(cREDp "       OS message : " cRST "%s\n", strerror(errno)); \
    exit(1); \
  } while (0)

/* Die with FAULT() or PFAULT() depending on the value of res (used to
   interpret different failure modes for read(), write(), etc). */

#define RPFATAL(res, x...) do { \
    if (res < 0) PANIC(x); else FATAL(x); \
  } while (0)

/* Error-checking versions of read() and write() that call RPFATAL() as
   appropriate. */

#define ck_write(fd, buf, len, fname) do { \
    u32 _len = (len); \
    i32 _res = write(fd, buf, _len); \
    if (_res != _len) RPFATAL(_res, "Short write to %s", fname); \
  } while (0)

#define ck_read(fd, buf, len, fname) do { \
    u32 _len = (len); \
    i32 _res = read(fd, buf, _len); \
    if (_res != _len) RPFATAL(_res, "Short read from %s", fname); \
  } while (0)

/* powerful assert equal */
#define ASSERT_EQ(varl, varr) do {                             \
    if(varl != varr) {                                         \
        SAY(cREDp "\n[-] Assert failed :" cRST " %p == %p\n"   \
            ,varl, varr                                        \
        );                                                     \
        assert(varl == varr);                                  \
    }                                                          \
  } while (0)

/* powerful assert not equal */
#define ASSERT_NEQ(varl, varr) do {                            \
    if(varl == varr) {                                         \
        SAY(cREDp "\n[-] Assert failed :" cRST " %p != %p\n"   \
            ,varl, varr                                        \
        );                                                     \
        assert(varl != varr);                                  \
    }                                                          \
  } while (0)
#endif /* __DEBUG_H__ */

