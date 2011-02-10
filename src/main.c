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


void write_digit (void);


volatile static int seven_seg_value;

int main (void)
{ 
	seven_seg_value = 0;	
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
	if (seven_seg_value == HEX_MAX) seven_seg_value = 0;
	seven_seg_write_hexdigit (seven_seg_value++);
	stop_time ();
	start_time ();	
} /* end write_digit () */

