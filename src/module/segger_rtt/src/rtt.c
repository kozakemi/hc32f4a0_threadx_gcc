#include <stdbool.h>
#include <stdarg.h>
#include "rtt.h"
#include "SEGGER_RTT.h"

void rtt_init()
{
    SEGGER_RTT_Init();
}

void rtt_printf(bool is_on, char *fmt, ...)
{
    if (is_on)
    {
        va_list args;
        va_start(args, fmt);
        SEGGER_RTT_vprintf(0, fmt, &args);
        va_end(args);
    }
}