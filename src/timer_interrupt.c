#include "interrupt_timer.h"
#include "seven_segment.h"

typedef unsigned short WORD;

/* This must agree with what is set-up. */
#define MBAR 0x20000000 

/* Defines for ColdFire 5206e Timer 1 */
#define TTMR1 (MBAR + 0x00000100)
#define TTRR1 (MBAR + 0x00000104)
#define TTCR1 (MBAR + 0x00000108)
#define TTCN1 (MBAR + 0x0000010c)
#define TTER1 (MBAR + 0x00000111)

#define TTMR2 (MBAR + 0x00000120)
#define TTRR2 (MBAR + 0x00000124)
#define TTCR2 (MBAR + 0x00000128)
#define TTCN2 (MBAR + 0x0000012c)
#define TTER2 (MBAR + 0x00000131)

/* 
 TMR1 is defined as 
 [15:8] = 0x00 / 0xFF divide clock by 0 /256
 [7:6]  = 00          disable interrupt
 [5]    = 0           output = active-low pulse
 [4]    = 0 / 1       disable / enable ref. interrupt
 [3]    = 0 / 1       free run mode disabled / enabled
 [2:1]  = 10          master clock/16
 [0]    = 1 / 0       timer1 enabled / disabled

 0xFFEC = 65516
*/

inline asm void setup_isr ()
{
	move.b #0x9E, D0
	move.b D0, 0x2000001C
	move.w #0x20000, SR
} /* end setup_isr () */


void register_timer_interrupt (unsigned long function)
{
	unsigned long *auto_vector;
	setup_isr ();

	auto_vector  = (unsigned long *) 0x7c;
	*auto_vector = function;
} /* end register_timer_interrupt () */


void start_time () 
{
	volatile WORD *mem_ptr;

	mem_ptr  = (WORD *) TTMR1; 
	*mem_ptr = (WORD) 0x0000;
	
	mem_ptr  = (WORD *) TTCN1;
	*mem_ptr = (WORD) 0x0000;

	mem_ptr  = (WORD *) TTRR1;
	*mem_ptr = (WORD) 337F;

	mem_ptr  = (WORD *) TTMR1;
	*mem_ptr = (WORD) 0xFF1D;
} /* end start_time () */

void stop_time ()
{
	volatile WORD *mem_ptr;
	mem_ptr = (WORD *) TTMR1;
	*mem_ptr = (WORD) 0x0000;
} /* end stop_time () */




