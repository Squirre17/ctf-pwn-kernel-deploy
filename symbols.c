#include <stdint.h>
typedef struct sofiri_head {
    char unk[0x70];
    struct sofiri_list *next;
    int total_count;
}sofiri_head;

typedef struct sofiri_list {
    struct list *next;
    char data[256];
}sofiri_list;

typedef struct list_head {
  struct list_head *next, *prev;
}list_head;

typedef struct msg_msg {
  struct list_head list;
  long m_type;
  uint64_t m_ts;    /* message text size */
  void *next;     /* struct msg_msgseg *next; */
  void *security; 
                  /* the actual message follows immediately */
}msg_msg;

int main() {
    struct sofiri_head a;
    struct sofiri_list b;
    struct msg_msg msg;
}
/*
gcc -g -shared -fPIC symbols.c  -o symbols.so
 objcopy --only-keep-debug symbols.so symbols.sym
*/
