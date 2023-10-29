#ifndef DEF_TIME_H
#define DEF_TIME_H

/* Timer defines */

#define CONTROL_8253        0x43
#define CONTROL_WORD        0x3C
#define COUNTER_0           0x40
#define TIME_KEEPER_INT     0x1C 
#define TIMER_18HZ          0xFFFF
#define LOW_BYTE(n)         (n & 0x00ff)
#define HIGH_BYTE(n)        ((n>>8) & 0x00ff)
#define TIMER_1000HZ        1193

#endif /* DEF_TIME_H */
