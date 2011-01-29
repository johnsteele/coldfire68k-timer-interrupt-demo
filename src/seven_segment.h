/**
 * @file seven_segment.h
 *
 * @author	John Steele <EMAIL:programjsteele {at} gmail {dot} com>
 * @version	1.0.0
 *
 * @date
 * 	Created:	Thu 27 Jan 2011 05:59:49 PM PST \n
 * 	Last Update:	Thu 27 Jan 2011 05:59:49 PM PST
 *
 * 	@brief Contains the 7-segment display specifics for lab-2 of EE427.
 */

#ifndef __SEVEN_SEGMENT_H__
#define __SEVEN_SEGMENT_H__


#define	MBAR (0x20000000)

/** 
 * @brief The 7-segment display is an LED digital display. 
 *  			dBug automatically initializes it. It is accessed through memory 
 *  			mapping since it's an external device on the eval board. 
 * 
 * 				The display is changed by writing a new value to the address 0x40000000.
 */
#define SEVEN_SEG_DISPLAY (0x40000000)

/**
 * @brief The (Chip Select Control Register) is used for writing to the 
 *  			7-segment display. 
 */
#define CSCR3 (MBAR+0x92)

/**
 * @brief The (Chip Select Mask Register).
 */
#define CSMR3 (MBAR+0x8C) 

/**
 * @brief Chip Select Control Mode for the display. Used to initialize CSCR3.
 * 					AA - Auto-Acknowledge
 *					R - Read Enabled
 *					W - Write Enabled
 * 				See the MCF5206e User's Manual Section 9-32.
 */ 
#define CS_AA_R_W (0x0183)



/*===========================================================================*/ 
/**
 * @brief Values for the seven segment display consists of an 8-bit number, 
 * 			  each bit representing an on/off flag for a particular segment of the 
 * 			  display. The below are which bits are associated with which segment 
 * 			  (numbers are zerobase bit indexes).
 */
/*===========================================================================*/ 
#define SEG_TOP_CENTER		(0x01)
#define SEG_TOP_RIGHT		  (0x02)
#define SEG_BOTTOM_RIGHT	(0x04)
#define SEG_BOTTOM_CENTER	(0x08)
#define SEG_BOTTOM_LEFT		(0x10)
#define SEG_TOP_LEFT	   	(0x20)
#define SEG_MIDDLE		  	(0x40)
#define SEG_DOT				    (0x80)



/*===========================================================================*/ 
/**
 * @brief Defines for different hexadecimal values for seven-segment display.
 */
/*===========================================================================*/ 
#define ZERO	((unsigned char) (SEG_TOP_CENTER|SEG_TOP_RIGHT|SEG_TOP_LEFT|SEG_BOTTOM_CENTER|SEG_BOTTOM_RIGHT|SEG_BOTTOM_LEFT))
#define ONE		((unsigned char)(SEG_TOP_RIGHT|SEG_BOTTOM_RIGHT))
#define TWO		((unsigned char)(SEG_TOP_CENTER|SEG_TOP_RIGHT|SEG_MIDDLE|SEG_BOTTOM_LEFT|SEG_BOTTOM_CENTER))
#define THREE	((unsigned char) (SEG_TOP_CENTER|SEG_TOP_RIGHT|SEG_MIDDLE|SEG_BOTTOM_RIGHT|SEG_BOTTOM_CENTER))
#define FOUR	((unsigned char) (SEG_TOP_LEFT|SEG_MIDDLE|SEG_TOP_RIGHT|SEG_BOTTOM_RIGHT))
#define FIVE	((unsigned char) (SEG_TOP_CENTER|SEG_TOP_LEFT|SEG_MIDDLE|SEG_BOTTOM_RIGHT|SEG_BOTTOM_CENTER))
#define SIX		((unsigned char) (SEG_TOP_LEFT|SEG_BOTTOM_LEFT|SEG_MIDDLE|SEG_BOTTOM_CENTER|SEG_BOTTOM_LEFT|SEG_BOTTOM_RIGHT))
#define SEVEN	((unsigned char) (SEG_TOP_CENTER|SEG_TOP_RIGHT|SEG_BOTTOM_RIGHT))
#define EIGHT	((unsigned char) (SEG_TOP_CENTER|SEG_TOP_RIGHT|SEG_TOP_LEFT|SEG_MIDDLE|SEG_BOTTOM_CENTER|SEG_BOTTOM_RIGHT|SEG_BOTTOM_LEFT))
#define NINE	((unsigned char) (SEG_TOP_CENTER|SEG_TOP_RIGHT|SEG_TOP_LEFT|SEG_MIDDLE|SEG_BOTTOM_RIGHT))
#define A	  	((unsigned char) (SEG_TOP_CENTER|SEG_TOP_RIGHT|SEG_TOP_LEFT|SEG_MIDDLE|SEG_BOTTOM_RIGHT|SEG_BOTTOM_LEFT))
#define B	  	((unsigned char) (SEG_TOP_CENTER|SEG_TOP_RIGHT|SEG_TOP_LEFT|SEG_MIDDLE|SEG_BOTTOM_CENTER|SEG_BOTTOM_RIGHT|SEG_BOTTOM_LEFT))
#define C	  	((unsigned char) (SEG_TOP_CENTER|SEG_TOP_LEFT|SEG_BOTTOM_CENTER|SEG_BOTTOM_LEFT))
#define D	  	((unsigned char) (SEG_TOP_CENTER|SEG_TOP_RIGHT|SEG_TOP_LEFT|SEG_BOTTOM_CENTER|SEG_BOTTOM_RIGHT|SEG_BOTTOM_LEFT))
#define E	  	((unsigned char) (SEG_TOP_CENTER|SEG_TOP_LEFT|SEG_MIDDLE|SEG_BOTTOM_CENTER|SEG_BOTTOM_LEFT))
#define F	  	((unsigned char) (SEG_TOP_CENTER|SEG_TOP_LEFT|SEG_MIDDLE|SEG_BOTTOM_LEFT))

#define	HEX_MAX 15

/**
 * @brief Pointer to the seven-segment display. Used to writing hex digits.
 */
extern unsigned char *pDisplay; 

/**
 * @brief Initializes the seven segment display. 
 */ 
extern void seven_seg_init(void);

/**
 * @brief Writes the digit in hexadecimal on the seven segment display. 
 *
 * @param digit The digit to display as hexadecimal.
 */ 
extern void seven_seg_write_hexdigit (int digit);

/**
 * @brief Clears the seven segment display. 
 */
extern void seven_seg_clear_display (void);

/**
 * @brief Writes a dot to the seven segment display. 
 */ 
extern void seven_seg_write_dot (void);

#endif /* __SEVEN_SEGMENT_H__ */

