/**
 * @file	  interrupt_timer.h
 *
 * @author	John Steele <EMAIL:programjsteele {at} gmail {dot} com>
 * @version	1.0.0
 *
 * @date
 * 	Created:	Thu 27 Jan 2011 06:17:48 PM PST
 * 	Last Update:	Thu 27 Jan 2011 06:17:48 PM PST 
 *
 * @brief EE427 Lab-2
 *
 * @brief Contains Timer 1 configurations.
 */

#ifndef __INTERRUPT_TIMER_H__
#define __INTERRUPT_TIMER_H__


/**
 * @brief This must agree with what is set up in the P&E Wiggler.
 */
#ifndef MBAR
#define	MBAR 0x20000000 
#endif	/* MBAR */


/*===========================================================================*/
/**
 * @brief Defines for Timer 1. 
 */
/*===========================================================================*/ 
#define	TTMR1 (MBAR+0x00000100)
#define	TTRR1 (MBAR+0x00000104)
#define	TTCR1 (MBAR+0x00000108)
#define	TTCN1 (MBAR+0x0000010c)
#define	TTER1 (MBAR+0x00000111)
#define	TTMR2 (MBAR+0x00000120)
#define	TTRR2 (MBAR+0x00000124)
#define	TTCR2 (MBAR+0x00000128)
#define	TTCN2 (MBAR+0x0000012c)
#define	TTER2 (MBAR+0x00000131)

/*
	TMR1 is defined as
	[15:8] = 0x00 / 0xFF   divide clock by 0 / 256
	[7:6]  = 00            disable interrupt
  [5]    = 0             output = active-low pulse	
	[4]    = 0 / 1         disable / enable ref. interrupt
	[3]    = 0 / 1         free run mode disabled / enabled
	[2:1]  = 10            master clock/16
	[0]    = 1 / 0         timer1 enabled / disabled 

	0xFFEC = 65516
 */


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

