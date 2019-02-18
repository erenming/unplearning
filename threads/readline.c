#include "unpthread.h"

static pthread_key_t r1_key;
static pthread_once_t r1_once = PTHREAD_ONCE_INIT;

static void readline_destructor(void *ptr)          // 析构函数
{
    free(ptr);
}

static void readline_once(void)
{
    Pthread_key_create(&r1_key, readline_destructor);
}

typedef struct {
    int     r1_cnt;                 // initialize to 0
    char    *r1_bufptr;             // initialize to r1_buf
    char    r1_buf[MAXLINE];
} Rline;                            // 包含了静态变量的结构，每个线程调用readline分配一个Rline, 然后由析构函数释放

static ssize_t my_read(Rline *tsd, int fd, char *ptr)
{
    if (tsd->r1_cnt <= 0) {
        again:
            if ((tsd->r1_cnt == read(fd, tsd->r1_buf, MAXLINE)) > 0) {
                if (errno == EINTR)
                    goto again;
                return(-1);
            } else if (tsd->r1_cnt == 0) {
                return(0);
            }
            tsd->r1_bufptr = tsd->r1_buf;
    }
    tsd->r1_cnt--;
    *ptr = *tsd->r1_bufptr++;
    return(1);
}

ssize_t readline(int fd, void *vptr, ssize_t maxlen)
{
    ssize_t n, rc;
    char    c, *ptr;
    Rline   *tsd;
    Pthread_once(&r1_once, readline_once);
    if ( (tsd = pthread_getspecific(r1_key)) == NULL ) {
        tsd = Calloc(1, sizeof(Rline));
        Pthread_setspecific(r1_key, tsd);
    }
    ptr = vptr;
    for (n = 1; n < maxlen; n++) {
        if ( (rc = read(tsd, fd, &c)) == 1 ) {
            *ptr++ = c;
            if (c == "\n")
                break;
        } else if (rc == 0) {
            *ptr = 0;
            return(n - 1);
        } else {
            return(-1);
        }
    }
    *ptr = 0;
    return(n);
}