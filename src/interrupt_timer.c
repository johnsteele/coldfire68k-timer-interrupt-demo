/**
 * @file interrupt_timer.c
 *
 * @author	John Steele <EMAIL:programjsteele {at} gmail {dot} com>
 * @version	1.0.0
 *
 * @date
 * 	Created:	Thu 27 Jan 2011 06:20:08 PM PST \n
 * 	Last Update:	Thu 27 Jan 2011 06:20:08 PM PST
 *
 * @brief EE427 Lab-2.
 *
 * @brief Contains interrupt functionality for Timer 1 on the ColdFire.
 */

#include "interrupt_timer.h"


/**
 * @brief For accessing register addresses.
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
 * @brief Point the vector base register (VBR) to the table in RAM. 
 * 				By default it points the copy in ROM.  
 */
/*===========================================================================*/ 
inline asm void init_vbr ()
{
	/* 
	 * A copy of the vector table has been made at 0x30000000 in RAM.
	 * But the vector base register (VBR) does not point to it, but to 
	 * the original table in ROM. So set the VBR to the copy in RAM. 
	 */
	move.l #0x30000000,A0
	movec  A0,vbr
} /* end init_vector_table () */


/*===========================================================================*/ 
/**
 * @brief The Interrupt Control Register (ICR) is used to assign the level
 *        and priority of the interrupt sources. Each ICR is an 8-bit register.
 */
/*===========================================================================*/ 
inline asm void init_icr () 
{
	/*
	 * Move ICR for Timer 1 (ICR9) into register. 
	 */
	movea.l #ICR9,A1 
	/*
	 * Set interrupt to level 4, priority 1 Autovector. 
	 */	
	move.b  #0x90,(A1) 
} /* end init_icr () */


/*===========================================================================*/ 
/**
 * @brief Sets up the vector table; however, the IDE already does it. 
 */
/*===========================================================================*/ 
inline asm void init_vector_table ()
{
 	// The IDE generates a vector.s, which does this for me.
} /* end init_vector_table () */


/*===========================================================================*/ 
/**
 * @brief The Interrupt Priority Mask (IPM) occupies bits 8,9,10 (zero based)
 *        in the Status Register (SR). These three bits form a number between
 *        0 and 7, which is used to mask output interrupts. With the bits
 *        set to 000, no interrupts will be masked. 
 */
/*===========================================================================*/ 
inline asm void init_ipm () 
{
	// Clear bit 8, 9, 10 of status register. 
	move.w sr,D0
	bclr   #8,D0
	bclr   #9,D0
	bclr   #10,D0
	move.w D0,sr
} /* end init_ipm () */


/*===========================================================================*/ 
/**
 * @brief The Interrupt Mask Register allows for enable/disabling interrupts
 *        individually, rather than just by level within the Status Register
 *        using the Interrupt Priory Mask. So for example you can disable 
 *        interrupts for just Timer 1. 
 *        The IMR consists of 16-bits, each bit corresponding to an individual
 *        interrupt source (e.g., Timer 1, Timer 2, UART, etc). More specifically,
 *        each bit corresponds to an Interrupt Control Register. Timer 1 is bit
 *        9. To enable interrupts on Timer 1, you have to clear the appropriate 
 *        IMR bit. You should preserve the state of other bits. 
 */
/*===========================================================================*/ 
inline asm void init_imr ()
{ 
	move.l #IMR,A1
	move.w (A1),D2
	bclr   #9,D2
	move.w D2,(A1)
} /* end init_imr () */


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
	// init_vector_table (); --> IDE does it for me. 
	init_vbr ();
	init_ipm ();
	init_icr ();
	init_imr ();
	setupisr ();
	
 	// Location of the handler for Timer 1 interrupt. 
	autovector  = (unsigned long *)HANDER_ENTRY; 
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

	/* 
	 * Clear the (Timer 1 Mode Register), also stops Timer 1 if it is running. 
	 */
	pMem  = (WORD *) TMR1;
	*pMem = (WORD) CLEAR;

	/* 
	 * Clear the (Timer 1 Counter Register). Sets counter to zero. 
	 */
	pMem  = (WORD *) TCN1;
	*pMem = (WORD) CLEAR;

	/* 
	 * Set (Timer 1 Reference Register) to a reference value. This value will be 
	 * compared with the free-running timer counter (TCN1). TCN1 will count up to
	 * this number to determine when to stop and/or interrupt.  
	 */
	pMem  = (WORD *) TRR1;
	*pMem = (WORD) TA_REF_VAL; 

	/*
	 * Set chip select address register 3 and 1. 
	 */	
	pMem = (WORD *) CSAR3;
	*pMem = 0x4000;
	pMem = (WORD *) CSAR1;
	*pMem = 0;

	/* 
	 * Set and start the timer 
	 */
	pMem  = (WORD *) TMR1;
	*pMem = (WORD) TMR_CFG; 
} /* end start_time () */ 


/*===========================================================================*/
/**
 * @brief Stops Timer 1.
 */
/*===========================================================================*/
void stop_time () 
{ 
	volatile WORD *pMem;

	/* 
	 * Clear (Timer 1 Mode Register) and stop the timer. 
	 */
	pMem  = (WORD *) TMR1;
	*pMem = (WORD) CLEAR;	
} /* end stop_time () */

