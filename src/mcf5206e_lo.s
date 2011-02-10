/*
 * File:	mcf5206e_lo.s
 * Purpose:	Lowest level routines for mcf5206e.
 *
 *
 *
 */
 
    .extern __SP_INIT
    .extern VECTOR_TABLE
    .extern _mcf5206e_mbar
    .extern _mcf5206e_rambar
    .extern _mcf5206e_init
    .extern __start
 
    .global asm_startmeup
    .global _asm_startmeup
    .global cpu_cache_flush
    .global _cpu_cache_flush
	.global	mcf5206e_wr_vbr
	.global _mcf5206e_wr_vbr
	.global	mcf5206e_wr_cacr
	.global _mcf5206e_wr_cacr
	.global	mcf5206e_wr_acr0
	.global _mcf5206e_wr_acr0
	.global	mcf5206e_wr_acr1
	.global _mcf5206e_wr_acr1
	.global	mcf5206e_wr_rambar
	.global _mcf5206e_wr_rambar
	.global	mcf5206e_wr_mbar
	.global _mcf5206e_wr_mbar

	.equ	SRAMsize,8192	/* 8K bytes */

	.text

/********************************************************************/

/*
 * This is the main entry point upon hard reset.
 */
asm_startmeup:
_asm_startmeup:

	move.w		#0x2700,SR
	move.l      #VECTOR_TABLE,d0
	movec       d0,VBR

	/* Invalidate the cache and disable it */
	move.l	#0x01000000,d0
//	.dc.l	0x4e7b0002		/* movec d0,cacr */
	movec	d0, cacr
	
	/* Disable ACRs */
	moveq.l	#0,d0
//	.dc.l	0x4e7b0004		/* movec d0,ACR0 */
//	.dc.l	0x4e7b0005		/* movec d0,ACR1 */
	movec	d0, ACR0
	movec	d0, ACR1
	
	/* Initialize SRAMBAR */
	move.l	#0xE0000001,d0	/* locate SRAM, validate it! */
//	.dc.l	0x4e7b0C04		/* movec d0,SRAMBAR */
	movec	d0, RAMBAR
	
	nop
	nop

	/*
	 * Point SP into SRAM (temporarily).  SRAM is used as stack space
	 * while initializing the mcf5206e periphs and memory controller.
	 */
	move.l	#0xE0000000+SRAMsize,SP

	/* Obtain pointer to where MBAR is to be mapped */
	jsr		_mcf5206e_mbar


/* MWERKS - added since CW returns (void *) to A0 instead */
	move.l	a0, d6 
//	move.l	d0,d6
/* MWERKS - added since CW returns (void *) to A0 instead */

	/* Obtain pointer to where RAMBAR is to be mapped */

	jsr		_mcf5206e_rambar

	/* Adjust SP to (soon to be valid) SRAM */
	
/* MWERKS - changed since CW returns (void *) to A0 instead */	
//	move.l	d0,a0	
	move.l	a0,d0	
/* MWERKS - changed since CW returns (void *) to A0 instead */
	
	lea		SRAMsize(a0),SP

	/* Map RAMBAR and MBAR */
	addq.l	#1,d0			/* Set Valid bit */
//	.dc.l	0x4e7b0C04		/* movec d0,RAMBAR */
	movec	d0, RAMBAR
	
	move.l	d6,d0
	addq.l	#1,d0			/* Set Valid bit */
//	.dc.l	0x4e7b0C0F		/* movec d0,MBAR */
	movec	d0, MBAR
	
	/* Initialize mcf5206e periphs, etc */
	move.l	d6,-(sp)		/* pointer to internal resources */
	jsr		_mcf5206e_init
	lea		4(sp),sp

	/*
	 * Point SP to DRAM.  DRAM may only be visible once CS0 
	 * de-activated as global chipselect.
	 */
	move.l	#__SP_INIT,sp

	nop
	nop

	jmp		__start			/* jump to __start in runtime */

/********************************************************************/
/*
 * mcf5206e has Icache only
 */
cpu_cache_flush:
_cpu_cache_flush:
	nop						/* sync */
	move.l	#0x01000000,d0
//	.dc.l	0x4e7b0002		/* movec d0,cacr */
	movec	d0, cacr
	nop						/* sync */
//	.dc.l	0x4e7b0002		/* movec d0,cacr */
	movec	d0, cacr
	rts

/********************************************************************/
/*
 * These routines write to the special purpose registers in the ColdFire
 * core.  Since these registers are write-only in the supervisor model,
 * no corresponding read routines exist.
 */
mcf5206e_wr_vbr:
_mcf5206e_wr_vbr:
	move.l	4(sp),d0
	andi.l	#0xFFF00000,d0	/* align to 1M boundary	 */
	movec	d0,VBR
	nop
	rts

mcf5206e_wr_cacr:
_mcf5206e_wr_cacr:
    move.l  4(sp),d0
//    .dc.l    0x4e7b0002      /* movec d0,cacr	 */
	movec	d0, cacr
    nop
    rts

mcf5206e_wr_acr0:
_mcf5206e_wr_acr0:
    move.l  4(sp),d0
//    .dc.l    0x4e7b0004      /* movec d0,ACR0	*/
	movec	d0, ACR0
    nop
    rts

mcf5206e_wr_acr1:
_mcf5206e_wr_acr1:
    move.l  4(sp),d0
//    .dc.l    0x4e7b0005      /* movec d0,ACR1	*/
	movec	d0, ACR1
    nop
    rts

mcf5206e_wr_rambar:
_mcf5206e_wr_rambar:
    move.l  4(sp),d0
//    .dc.l    0x4e7b0C04      /* movec d0,RAMBAR	*/
	movec	d0, RAMBAR
    nop
    rts

mcf5206e_wr_mbar:
_mcf5206e_wr_mbar:
    move.l  4(sp),d0
//    .dc.l    0x4e7b0C0F      /* movec d0,MBAR	*/
	movec	d0, MBAR
    nop
    rts

	.end

