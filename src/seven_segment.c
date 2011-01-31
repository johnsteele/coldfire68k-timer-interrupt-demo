/**
 * @file	  seven_segment.c 
 *
 * @author	John Steele <EMAIL:programjsteele {at} gmail {dot} com>
 * @version	1.0.0
 *
 * @date
 * 	Created:	Thu 27 Jan 2011 05:59:49 PM PST \n
 * 	Last Update:	Thu 27 Jan 2011 05:59:49 PM PST
 *
 * 	@brief This file contains the functions for controlling the 7-seg display.
 */

#include	"seven_segment.h"

/**
 * @brief The different values to render on 7-seg display.
 */
unsigned char display [] = {DOT, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, A, B, C, D, E, F};

/**
 * @brief Pointer to the seven-segment display. Used to writing hex digits.
 */
unsigned char *pDisplay; 


/*===========================================================================*/ 
/**
 * @brief Initializes the seven segment display. 
 */ 
/*===========================================================================*/ 
void seven_seg_init (void) 
{
	short *pCSCR3 = (short*) CSCR3;
	short *pCSMR3 = (short*) CSMR3;

	/* Set Chip Select Control Register 3 */
	*pCSCR3 = (short)CS_AA_R_W;

	/* Clear Chip Select Mask Register 3 */
	*pCSMR3 = (short)0;

	/* For assigning values to 7-seg display */
	pDisplay = (unsigned char *) SEVEN_SEG_DISPLAY;
} /* end seven_seg_init () */



/*===========================================================================*/ 
/**
 * @brief Writes the digit in hexadecimal on the seven segment display. 
 *
 * @param digit The digit to display as hexadecimal.
 */
/*===========================================================================*/ 
void seven_seg_write_hexdigit (int digit)
{
	*pDisplay = display [digit];
} /* end seven_seg_write_hexdigit () */


/*===========================================================================*/ 
/**
 * @brief Clears the seven segment display. 
 */
/*===========================================================================*/ 
void seven_seg_clear_display (void)
{
	*pDisplay = 0;
} /* end seven_seg_clear_display () */


/*===========================================================================*/ 
/**
 * @brief Writes a dot to the seven segment display. 
 */
/*===========================================================================*/ 
void seven_seg_write_dot (void)
{
	*pDisplay = DOT;
} /* end seven_seg_write_dot () */

