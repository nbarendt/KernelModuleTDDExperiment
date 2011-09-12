#include <printkSpy.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_PRINTK_LENGTH 1000
#define MAX_NUMBER_PRINTKS 1000

static char messages[MAX_NUMBER_PRINTKS][MAX_PRINTK_LENGTH];

static int msg_count;
static int next_msg;

void printkSpy_Create(void)
{
    int i;

    for(i=0; i < MAX_NUMBER_PRINTKS; i++) {
        memset(&(messages[i]), 0, MAX_PRINTK_LENGTH);
    }
    msg_count = 0;
    next_msg = 0;
}

void printkSpy_Destroy(void)
{
}

int printkSpy_get_len(void)
{
    return msg_count;
}

const char *printkSpy_get_next(void)
{
    return (const char*)messages[next_msg++];
}


int printk(const char *fmt, ...)
{
    char msg[MAX_PRINTK_LENGTH];
    va_list ap;
    int formatted_chars = 0;


    // we'll just explode if we fill up the message list - until we
    //   need something fancier

    va_start(ap, fmt);
    formatted_chars = vsnprintf(msg, sizeof(msg), fmt, ap);
    assert( msg_count < MAX_NUMBER_PRINTKS - 1);
    assert(formatted_chars > 0);
    strncpy(messages[msg_count++], msg, sizeof(messages[msg_count]));
    return formatted_chars;
}


