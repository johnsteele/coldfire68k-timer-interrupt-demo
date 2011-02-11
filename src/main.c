/**
 * @file main.c
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


/**
 * @brief The Timer 1 ISR. Updates the 7-segment display with the next value. 
 *        digit.  
 */
void write_digit (void); 

/**
 * @brief The current value displayed on the 7-segment display. 
 *        Used by the write_digit ISR. 
 */
volatile static int seven_seg_value;


/*===========================================================================*/
/**
 * @brief Initializes the seven segment display and Timer 1 interrupts, then
 * 				runs in endless loop. 
 *
 * @return Zero for success.  		  
 */
/*===========================================================================*/
int main (void)
{
	/*
	 * Initialize seven segment display value. 
	 */	
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


/*===========================================================================*/
/**
 * @brief The Timer 1 ISR. Updates the 7-segment display with the next value. 
 */ 
/*===========================================================================*/
__declspec (interrupt) void write_digit (void)
{
	/*
	 * Restart count to zero if current value is F. 
	 */
	if (seven_seg_value == HEX_MAX) seven_seg_value = 0;

	/*
	 * Write the next value to the 7-segment display. 
	 */
	seven_seg_write_hexdigit (seven_seg_value++);

	stop_time ();
	start_time ();	
} /* end write_digit () */

