
#ifndef __INTERRUPT_TIMER_H__
#define __INTERRUPT_TIMER_H__

extern void start_time (void);
extern void stop_time (void);
extern void register_timer_interrupt (unsigned long function);

#endif /* __INTERRUPT_TIMER_H__ */

