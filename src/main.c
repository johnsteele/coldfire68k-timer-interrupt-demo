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
 *  			digits to a seven segment display using the ColdFire 68k processor on a 
 *  			MCF5206eLite development board. 
 */


/*
 * The MBAR (Module Base Address Register) defines where in memory the other 
 * peripheral registers appear in the memory space of the processor.
 */
#define MBAR (0x10000000) 

/*
 * TCN (Timer Counter Register) is a memory-mapped 16-bit up counter that you 
 * can read at any time. A read cycle to TCN yields the current timer value 
 * and does not affect the counting operation. 
 *
 * A write of any value to TCN causes it to reset to all zeros.
 * TCN register keeps the current count of the timer. Duh!
 */
#define TCN1 (MBAR+0x10C) // Timer 1 counter

/*****************************************************************************
 *								Timer Registers
 *
 * The ColdFire's timers are both composed of five memory-mapped registers. 
 * You deal with the timers by reading and writing to these registers.
 ******************************************************************************/
/*
 * TMR 1 (Timer Mode Register) is a 16-bit memory-mapped register. This register 
 * programs the various timer modes and is cleared by reset.
 * The TMR is used to initialize the timer and control the timer behavior. 
 * This is the most complicated register. It is also the one you need to be 
 * familiar with.
 */
#define TMR1 (MBAR+0x100) 

/* 
 * The TRR (Timer Reference Register) is a 16-bit register containing
 * the reference value that is compared with the free-running timer counter (TCN) 
 * as part of the output-compare function. TRR is a memory-mapped read/write register.
 *
 * The TRR takes a user-supplied value that is compared to the Timer Counter to determine 
 * when to stop and/or interrupt. The timer counts up to this number. You tell it how 
 * fast to count and what to do when it gets to the reference number.
 */
#define TRR1 (MBAR+0x104) // Timer 1 reference register

/* 
 * Timer configuration.
 * Used to set up the Timer Mode Register. 
 * Used to set and start the timer (1111111100011101).
 */
#define TMR_CFG (0xFF1D)


/* Used to initialize the timer */
short *pTRR1;
short *pTMR1;
short *pTCN1; 

void timer_init(void); 
void write_digit (void);

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


	/*
	 * Start the timer, and run in an endless loop.
	 */
	

	return 0;
} /* end main () */


__declspec (interrupt) void write_digit (void)
{
	static int i = 0;
	if (i == HEX) {i = 0;}
	seven_seg_write_hex (i++);
	stop_time ();
	start_time ();	
} /* end write_digit () */

