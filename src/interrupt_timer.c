/**
 * @file	  interrupt_timer.c
 *
 * @author	John Steele <EMAIL:programjsteele {at} gmail {dot} com>
 * @version	1.0.0
 *
 * @date
 * 	Created:	Thu 27 Jan 2011 06:20:08 PM PST \n
 * 	Last Update:	Thu 27 Jan 2011 06:20:08 PM PST
 *
 * @brief EE427 Lab-2
 *
 * @brief Contains interrupt functionality for Timer 1 on the ColdFire.
 */

#include "interrupt_timer.h"

/**
 * @brief Used for accessing register addresses.
 */
typedef unsigned short WORD; 


/*===========================================================================*/
/**
 * @brief Sets up the Interrupt Service Routine. 
 */
/*===========================================================================*/
inline asm void setupisr ()
{
	move.b #0x9E,D0
	move.b D0,0x20000001C
	move.w #0x2000,SR
} /* end setupisr () */



/*===========================================================================*/
/**
 * @brief Registers the provided function for a Timer 1 interrupt.
 *
 * @param function The function to register as ISR. 
 */
/*===========================================================================*/
void register_timer_interrupt (unsigned long function) 
{
	unsigned long *autovector;
	setupisr ();
	autovector  = (unsigned long *)0x7C;
	*autovector = function;
} /* end register_timer_interrupt () */



/*===========================================================================*/
/**
 * @brief Starts Timer 1.
 */
/*===========================================================================*/
void start_time ()
{
	volatile WORD *pMem;

	/* Clear the (Timer 1 Mode Register), also stops Timer 1 if it is running. */
	pMem  = (WORD *)TMR1;
	*pMem = (WORD)0x0000;

	/* Clear the (Timer 1 Counter Register). Sets counter to zero. */
	pMem  = (WORD *)TCN1;
	*pMem = (WORD)0x0000;

	/* 
	 * Set (Timer 1 Reference Register) to a reference value. This value will be 
	 * compared with the free-running timer counter (TCN1). TCN1 will count up to
	 * this number to determine when to stop and/or interrupt.  
	 */
	pMem  = (WORD *)TRR1;
	*pMem = (WORD)0x337F;

	/* Set and start the timer */
	pMem  = (WORD *)TMR1;
	*pMem = (WORD)TMR_CFG; 
} /* end start_time () */ 



/*===========================================================================*/
/**
 * @brief Stops Timer 1.
 */
/*===========================================================================*/
void stop_time () 
{ 
	volatile WORD *pMem;
	/* Clear (Timer 1 Mode Register) and stop the timer. */
	pMem  = (WORD *)TMR1;
	*pMem = (WORD)0x0000;	
} /* end stop_time () */

