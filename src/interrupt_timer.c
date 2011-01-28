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

/*===========================================================================*/
/*===============================[ Includes ]================================*/
/*===========================================================================*/
#include "interrupt_timer.h"
#include "seven_segment.h"



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
	autovector  = (unsigned long *)0x7c;
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
	pMem  = (WORD *)TTMR1;
	*pMem = (WORD)0x0000;

	pMem  = (WORD *)TTCN1;
	*pMem = (WORD)0x0000;

	pMem  = (WORD *)TTRR1;
	*pMem = (WORD)0x337F;

	pMem  = (WORD *)TTMR1;
	*pMem = (WORD)0xFF1D; 
} /* end start_time () */ 



/*===========================================================================*/
/**
 * @brief Stops Timer 1.
 */
/*===========================================================================*/
void stop_time () 
{
	volatile WORD *pMem;
	pMem  = (WORD *)TTMR1;
	*pMem = (WORD)TTMR1;	
} /* end stop_time () */

