#ifndef __RTT_H__
#define __RTT_H__
#include <stdbool.h>
#include <stdarg.h>
void rtt_init();
void rtt_printf(bool is_on, char *fmt, ...);

#endif /* __RTT_H__ */
