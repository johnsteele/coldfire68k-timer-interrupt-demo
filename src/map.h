/*
 * File:		map.h
 * Purpose:		Memory map information.
 *
 * Notes:
 *
 * Author:		Michael Norman
 * Date:
 *
 * Modifications:
 *
 *		User: Jeffri Tan		Date:4/19/2000 
 *		- Made modifications to compile under Metrowerks 
 *		  Codewarrior E68k.
 */

#ifndef _MAP_H
#define _MAP_H

/********************************************************************/

#define FLASH_ADDRESS		(0xFFE00000)
#define DRAM_ADDRESS		(0x00000000)

#define IMM_ADDRESS			(0x20000000)

#define EXT_SRAM_ADDRESS	(0x30000000)
#define EXT_SRAM_SIZE		(0x00080000)
#define SRAM_ADDRESS		(0x00400000)
#define SRAM_SIZE			(0x00002000)

/*
 * Macro which returns a pointer to the Internal Memory Map
 */ 
#define mcf5206e_get_immp()	((MCF5206e_IMM *)(IMM_ADDRESS))

/********************************************************************/

#endif /* _MAP_H */
