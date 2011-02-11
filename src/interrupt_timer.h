/**
 * @file interrupt_timer.h
 *
 * @author John Steele <EMAIL:programjsteele {at} gmail {dot} com>
 * @version 1.0.0
 *
 * @date
 * 	Created: Thu 27 Jan 2011 06:17:48 PM PST
 * 	Last Update: Thu 10 Feb 2011 010:17:48 AM PST 
 *
 * @brief EE427 Lab-2
 *
 * @brief Contains Timer 1 configurations.
 */
#include "seven_segment.h"

#ifndef __INTERRUPT_TIMER_H__
#define __INTERRUPT_TIMER_H__



/**
 * @brief TMR (Timer Mode Register) is a 16-bit memory-mapped register. This 
 * 	  register programs the various timer modes and is cleared by reset.
 * 	  The TMR is used to initialize the timer and control the timer 
 * 	  behavior. This is the most complicated register. It is also the one 
 * 	  you need to be familiar with.
 */
#define	TMR1 (MBAR+0x00000100)

/** 
 * @brief Timer 1 configuration. Used to set up the Timer Mode Register. 
 * 	  Used to set and start the timer (1111111100011101).
 */
#define TMR_CFG (0xFF1D)

/**
 * @brief The TRR (Timer Reference Register) is a 16-bit register containing
 * 	  the reference value that is compared with the free-running timer counter
 * 	  (TCN) as part of the output-compare function. TRR is a memory-mapped 
 * 	  read/write register.
 *
 * 	  The TRR takes a user-supplied value that is compared to the Timer Counter
 * 	  to determine when to stop and/or interrupt. The timer counts up to this 
 * 	  number. You tell it how fast to count and what to do when it gets to the 
 * 	  reference number.
 */ 
#define	TRR1 (MBAR+0x00000104)

/**
 * @brief TCN (Timer Counter Register) is a memory-mapped 16-bit counter that
 * 	  you can read at any time. A read cycle to TCN yields the current timer 
 * 	  value and does not affect the counting operation. 
 *
 * 	  A write of any value to TCN causes it to reset to all zeros. TCN register
 * 	  keeps the current count of the timer. Duh!
 */ 
#define	TCN1 (MBAR+0x0000010c)

/** 
 * @brief Timer configuration. Used to set up the Timer Mode Register. 
 *        Used to set and start the timer (1111111100011101).
 *
 *        TMR1 is defined as
 *	  [15:8] = 0x00 / 0xFF   divide clock by 0 / 256
 *	  [7:6]  = 00            disable interrupt
 *        [5]    = 0             output = active-low pulse	
 *	  [4]    = 0 / 1         disable / enable ref. interrupt
 *	  [3]    = 0 / 1         free run mode disabled / enabled
 *	  [2:1]  = 10            master clock/16
 *	  [0]    = 1 / 0         timer1 enabled / disabled 
 */
#define TMR_CFG (0xFF1D)

/**
 * @brief Interrupt Control Register (ICR) for Timer 1, ICR9. 
 */
#define ICR9 (MBAR+0x01C)

/**
 * @brief The Interrupt Mask Register. 
 */
#define IMR (MBAR+0x36)

/**
 * @brief Chip select register 3 and 1 need to be set. 
 */
#define CSAR3 (MBAR+0x088)
#define CSAR1 (MBAR+0x070)

/**
 * @brief The Vector Base Register (VBR). 
 */
#define VBR (0x30000000)

/**
 * @brief The location of the autovector handler for Timer 1 interrupt. 
 *        The lower 20 bits are zero. 
 */
#define	HANDER_ENTRY (VBR+0x070)

/**
 * @brief Used for clearing bits. 
 */
#define CLEAR (0x0000)

/**
 * @brief The Timter 1 reference value. 
 */
#define TA_REF_VAL (0x337F)

/**
 * @brief Used for initializing Timer 1. 
 */
extern short *pTRR1;
extern short *pTMR1;
extern short *pTCN1; 


/**
 * @brief Registers the provided function for a Timer 1 interrupt.
 *
 * @param function The function to register. 
 */
extern void register_timer_interrupt (unsigned long function);

/**
 * @brief Starts Timer 1.
 */
extern void start_time (void);

/**
 * @brief Stops Timer 1.
 */
extern void stop_time  (void);

#endif  /* __INTERRUPT_TIMER__H__ */

