/**
 * @file	  main.c
 *
 * @author	John Steele <EMAIL:programjsteele {at} gmail {dot} com>
 * @version	1.0.0
 *
 * @date
 * 	Created:	Thu 27 Jan 2011 05:59:49 PM PST \n
 * 	Last Update:	Thu 27 Jan 2011 05:59:49 PM PST
 *
 * @brief EE427 lab-2. 
 *
 * @brief Demonstrates the use of timers and interrupts by writing hexadecimal
 *  			digits to a seven segment display using the ColdFire 68k processor on 
 *  			a MCF5206eLite development board. 
 */

#include	"seven_segment.h"   /* 7-segment display */
#include	"interrupt_timer.h" /* Timer 1 interrupt */

int main (void)
{ 
	/* 
	 * Initialize the seven segment display. 
	 */
	seven_seg_init ();

	/*
	 * Clear the seven segment display.
	 */
	seven_seg_clear_display ();

	/*
	 * Register the write_digit () for the interrupt.
	 */
	register_timer_interrupt ((unsigned long) write_digit);

	/*
	 * Start the timer, and run in an endless loop.
	 */
	start_time (); 

	while (1);

	return 0; 
} /* end main () */


__declspec (interrupt) void write_digit (void)
{
	static int i = 0;
	if (i == HEX_MAX) i = 0;
	seven_seg_write_hex (i++);
	stop_time ();
	start_time ();	
} /* end write_digit () */

