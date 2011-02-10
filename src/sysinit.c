/*
 * File:		sysinit.c
 * Purpose:		Power-on Reset configuration of the mcf5206e.
 *
 */

#include "mcf5206e.h"
#include "map.h"

#ifdef __MWERKS__
asm inline void noop(void)
  {
  nop;
  }
#endif

/********************************************************************/

static int
probe (uint32, uint32);

/********************************************************************/

/*
 * Out of reset, the low-level assembly code calls this routine to
 * obtain the address at which to map the MBAR.
 */
void *
mcf5206e_mbar (void)
{
	return (void *)IMM_ADDRESS;
}

/********************************************************************/

/*
 * Out of reset, the low-level assembly code calls this routine to
 * obtain the address at which to map the RAMBAR.
 */
void *
mcf5206e_rambar (void)
{
	return (void *)SRAM_ADDRESS;
}

/****************************************************************/
void
mcf5206e_sim_init (mcf5206e_IMM *imm)
{
	/*******************************************************
	*
	* This routine executed upon reset to initialize
	* mcf5206e periphs.  An initial stack must have been setup
	* in the SRAM in order for this routine to work.
	*
	*******************************************************/

	/*
	 * Initialize System Protection Resources.  Software Watchdog
	 * disabled, and Bus Monitor enabled.
	 */
	imm->sim.SYPCR = ( 0
		| mcf5206e_SIM_SYPCR_BME		/* yields bus error if no TA */
		| mcf5206e_SIM_SYPCR_BM_1024
		) ;

	/*
	 * Disable Bus monitor and SWT while CPU halted.
	 */
	imm->sim.SIMR = ( 0
		| mcf5206e_SIM_SIMR_FRZ1
		| mcf5206e_SIM_SIMR_FRZ0
		) ;

	/*
	 * Mask all interrupt sources.
	 */
	imm->sim.IMR = (~0);

	/*
	 * Configure multiplexed pins
	 *  - UART2 RTS
	 *  - External interrupts pins are IRQs, not IPLs
	 *  - PST/DDATA not 8bit Parallel Port I/O
	 *  - WE0, WE1, WE2, WE3
	 */

	imm->sim.PAR = ( 0
		| mcf5206e_SIM_PAR_PAR7	
		| mcf5206e_SIM_PAR_PAR5	
		| mcf5206e_SIM_PAR_PAR4	
		) ;

	/*
	 * Setup Interrupt Source Vectors
	 */
	imm->sim.ICR1 = ( 0
		| mcf5206e_SIM_ICR_AVEC		/* IPL/IRQ 1 */
		| mcf5206e_SIM_ICR_IL(1)
		| mcf5206e_SIM_ICR_IP(1)
		) ;

	imm->sim.ICR2 = ( 0
		| mcf5206e_SIM_ICR_AVEC		/* unusable */
		| mcf5206e_SIM_ICR_IL(2)
		| mcf5206e_SIM_ICR_IP(3)
		) ;

	imm->sim.ICR3 = ( 0
		| mcf5206e_SIM_ICR_AVEC		/* unusable */
		| mcf5206e_SIM_ICR_IP(2)
		) ;

	imm->sim.ICR4 = ( 0
		| mcf5206e_SIM_ICR_AVEC	
		| mcf5206e_SIM_ICR_IL(4)	/* IRQ 4, Ethernet */
		| mcf5206e_SIM_ICR_IP(2)
		) ;

	imm->sim.ICR5 = ( 0
		| mcf5206e_SIM_ICR_AVEC		/* unusable */
		| mcf5206e_SIM_ICR_IL(2)
		| mcf5206e_SIM_ICR_IP(1)
		) ;

	imm->sim.ICR6 = ( 0
		| mcf5206e_SIM_ICR_AVEC		/* unusable */
		| mcf5206e_SIM_ICR_IL(2)
		| mcf5206e_SIM_ICR_IP(0)
		) ;

	imm->sim.ICR7 = ( 0
		| mcf5206e_SIM_ICR_AVEC		/* IPL/IRQ 7, Abort/NMI */
		| mcf5206e_SIM_ICR_IL(7)
		| mcf5206e_SIM_ICR_IP(3)
		) ;

	imm->sim.ICR8 = ( 0
		| mcf5206e_SIM_ICR_AVEC		/* Software Watchdog */
		| mcf5206e_SIM_ICR_IL(7)
		| mcf5206e_SIM_ICR_IP(2)
		) ;

	imm->sim.ICR9 = ( 0
		| mcf5206e_SIM_ICR_AVEC		/* Timer 1 */
		| mcf5206e_SIM_ICR_IL(5)
		| mcf5206e_SIM_ICR_IP(3)
		) ;

	imm->sim.ICR10 = ( 0
		| mcf5206e_SIM_ICR_AVEC		/* Timer 2 */
		| mcf5206e_SIM_ICR_IL(5)
		| mcf5206e_SIM_ICR_IP(2)
		) ;

	imm->sim.ICR11 = ( 0
		| mcf5206e_SIM_ICR_AVEC		/* MBUS */
		| mcf5206e_SIM_ICR_IL(3)
		| mcf5206e_SIM_ICR_IP(0)
		) ;

	imm->sim.ICR12 = ( 0
		| mcf5206e_SIM_ICR_AVEC		/* UART 1 */
		| mcf5206e_SIM_ICR_IL(3)
		| mcf5206e_SIM_ICR_IP(2)
		) ;

	imm->sim.ICR13 = ( 0
		| mcf5206e_SIM_ICR_AVEC		/* UART 2 */
		| mcf5206e_SIM_ICR_IL(3)
		| mcf5206e_SIM_ICR_IP(1)
		) ;

	/*
	 * Software Watchdog, not used since disabled above
	 */
	imm->sim.SWIVR = 0x0F;			/* uninitiliazed vector */
	imm->sim.SWSR  = 0x55;
	imm->sim.SWSR  = 0xAA;
}
/****************************************************************/
void 
mcf5206e_pp_init (mcf5206e_IMM *imm)
{
	/*
	 * Init PPDDR to all inputs.
	 */
	imm->pp.PPDDR = 0;

	/*
	 * Initialize PPDAT.
	 */
	imm->pp.PPDAT = 0;
}
/****************************************************************/
void 
mcf5206e_timer_init (mcf5206e_IMM *imm)
{
	/*
	 * Reset timers and disable them
	 */
	imm->timer.TMR1 = ( 0
		| mcf5206e_TIMER_TMR_CLK_STOP
		| mcf5206e_TIMER_TMR_RST
		) ;

	imm->timer.TER1 = ( 0
		| mcf5206e_TIMER_TER_REF
		| mcf5206e_TIMER_TER_CAP
		) ;

	imm->timer.TMR2 = ( 0
		| mcf5206e_TIMER_TMR_CLK_STOP
		| mcf5206e_TIMER_TMR_RST
		) ;

	imm->timer.TER2 = ( 0
		| mcf5206e_TIMER_TER_REF
		| mcf5206e_TIMER_TER_CAP
		) ;
}
/****************************************************************/
void
mcf5206e_uart_init(mcf5206e_IMM *imm)
{
	/************************************************************************/
	/*  UART 1                                                              */
	/************************************************************************/

	imm->uart1.UCR = mcf5206e_UART_UCR_RESET_TX;    /* Transmitter Reset    */
	imm->uart1.UCR = mcf5206e_UART_UCR_RESET_RX;    /* Receiver Reset       */
	imm->uart1.UCR = mcf5206e_UART_UCR_TX_ENABLED;	/* Enable Transmitter	*/ 
	imm->uart1.UCR = mcf5206e_UART_UCR_RX_ENABLED;	/* Enable Receiver		*/ 
	imm->uart1.UCR = mcf5206e_UART_UCR_RESET_MR;    /* Mode Register Reset  */
 
	imm->uart1.UMR = ( 0
		| mcf5206e_UART_UMR1_PM_NONE		/* No parity					*/
		| mcf5206e_UART_UMR1_BC_8			/* 8 bits per character			*/
		) ;
	imm->uart1.UMR = ( 0
		| mcf5206e_UART_UMR2_CM_NORMAL		/* No echo or loopback			*/
		| mcf5206e_UART_UMR2_STOP_BITS(7)	/* 1 stop bit					*/
		) ;
	imm->uart1.USR = ( 0
		| mcf5206e_UART_UCSR_RCS(0xd)		/* Set receiver baud by timer   */
		| mcf5206e_UART_UCSR_TCS(0xd)		/* Set transmitter baud by timer*/
		) ;
	imm->uart1.UIP = ( 0
		| mcf5206e_UART_UACR_CTMS_TIMER		/* Set baud by timers			*/
		) ;
	imm->uart1.UIR = 0;						/* Disable all interrupts       */
                 
	imm->uart1.UBG1 = 0;
	imm->uart1.UBG2 = 0x56;					/* Set baud to 19200, 54MHZ		*/

    /************************************************************************/
    /*  UART 2                                                              */
    /************************************************************************/

    imm->uart2.UCR = ( 0					/* Disable UART 2 */
            | mcf5206e_UART_UCR_TX_DISABLED
            | mcf5206e_UART_UCR_RX_DISABLED
            ) ;
}
/****************************************************************/
void
mcf5206e_cs_init (mcf5206e_IMM *imm)
{
	/*
	 * This routine initializes ChipSelects to setup peripherals
	 * and other board memory devices.
	 */

	/*
	 * ChipSelect 2 - SRAM 
	 */
	imm->cs.CSAR2 = mcf5206e_CS_CSAR_BASE(EXT_SRAM_ADDRESS);

	imm->cs.CSMR2 = ( 0
		| mcf5206e_CS_CSMR_MASK_512K 
		);
	imm->cs.CSCR2 = ( 0
		| mcf5206e_CS_CSCR_WS(0)
		| mcf5206e_CS_CSCR_PS_32
		| mcf5206e_CS_CSCR_AA
		| mcf5206e_CS_CSCR_WR
		| mcf5206e_CS_CSCR_RD
		) ;

	/*
	 * ChipSelect 0 - Boot FLASH
	 *
	 * ChipSelect 0 is the global chip select coming out of system reset.
	 * CS0 is asserted for every access until CSMR0 is written.  Therefore,
	 * the entire ChipSelect must be properly set prior to asserting
	 * CSCR0_V.
	 */
	imm->cs.CSAR0 = mcf5206e_CS_CSAR_BASE(FLASH_ADDRESS);
	imm->cs.CSCR0 = ( 0
		| mcf5206e_CS_CSCR_WS(3)
		| mcf5206e_CS_CSCR_AA		/* TA_ generated internally */
		| mcf5206e_CS_CSCR_PS_16
		| mcf5206e_CS_CSCR_WR
		| mcf5206e_CS_CSCR_RD
		| mcf5206e_CS_CSCR_EMAA
		) ;
	imm->cs.CSMR0 = mcf5206e_CS_CSMR_MASK_1M;

	/*
	 * ChipSelect 1,3,4,5,6 and 7 - Not used
	 */
	imm->cs.CSCR1 = 0;
	imm->cs.CSCR3 = 0;
	imm->cs.CSCR4 = 0;
	imm->cs.CSCR5 = 0;
	imm->cs.CSCR6 = 0;
	imm->cs.CSCR7 = 0;

	imm->cs.DMCR = 0;
}
/********************************************************************/
void
mcf5206e_dramc_init (mcf5206e_IMM *imm)
{
	/*
	 * This routine initializes DRAM Controller and determines size
	 * of installed DRAM.
	 */
	uint32 dram_size, bank_two, junk;

#ifdef CHANGE_DRAM_WIDTH
	uint32 dccr, dcmr;
#endif
	/*
	 * DRAM Controller Refresh Register calculation:
	 *
	 * Refresh cycle time = RC * 16 * ( 1 / System Frequency )
	 *
	 * 15.6us = RC * 16 * ( 1 / 54MHz )
	 *     52 = RC
	 */
	imm->dramc.DCRR = 0x0000;

	imm->dramc.DCTR = ( 0
		| mcf5206e_DRAMC_DCTR_EDO 
		| mcf5206e_DRAMC_DCTR_RCD 
		| mcf5206e_DRAMC_DCTR_RSH_2 
		| mcf5206e_DRAMC_DCTR_CRP_25
         	| mcf5206e_DRAMC_DCTR_CAS
		); 
	imm->dramc.DCAR0 = mcf5206e_DRAMC_DCAR_BASE(DRAM_ADDRESS);
	imm->dramc.DCMR0 = mcf5206e_DRAMC_DCMR_MASK_16M;
	imm->dramc.DCCR0 = ( 0
		| mcf5206e_DRAMC_DCCR_PS_32
		| mcf5206e_DRAMC_DCCR_BPS_512B
		| mcf5206e_DRAMC_DCCR_PM_BURSTPAGE   
		| mcf5206e_DRAMC_DCCR_WR
		| mcf5206e_DRAMC_DCCR_RD
		) ;

	imm->dramc.DCAR1 = 0;
	imm->dramc.DCMR1 = 0;
	imm->dramc.DCCR1 = 0;

	/*
	 * Determine size of DRAM Bank 0
	 */
	if (probe(DRAM_ADDRESS,0x00800000))
	{
		dram_size = 0x01000000;
	}
	else
	{
		imm->dramc.DCMR0 = mcf5206e_DRAMC_DCMR_MASK_4M;
		if (probe(DRAM_ADDRESS,0x00100000))
		{
			dram_size = 0x00400000;
		}
		else
		{
			imm->dramc.DCMR0 = mcf5206e_DRAMC_DCMR_MASK_1M;
			dram_size = 0x00100000;
		}
	}

	/*
	 * Now check DRAM Bank 1 for existance by enabling identical
	 * to DRAM Bank 0, and probing
	 */
	imm->dramc.DCCR1 = imm->dramc.DCCR0;
	imm->dramc.DCMR1 = imm->dramc.DCMR0;
	imm->dramc.DCAR1 = (uint16)mcf5206e_DRAMC_DCAR_BASE(dram_size);
	if (probe(DRAM_ADDRESS+dram_size,4))
		bank_two = TRUE;
	else
		bank_two = FALSE;

	imm->dramc.DCAR1 = 0;
	imm->dramc.DCMR1 = 0;
	imm->dramc.DCCR1 = 0;

#ifdef CHANGE_DRAM_WIDTH
	dccr = imm->dramc.DCCR0;
	dcmr = imm->dramc.DCMR0;
	dccr &= ~mcf5206e_DRAMC_DCCR_PS_MASK;
	switch (board_get_dramw())
	{
		case 8:
			dccr |= mcf5206e_DRAMC_DCCR_PS_8;
			dcmr >>= 2;
			break;
		case 16:
			dccr |= mcf5206e_DRAMC_DCCR_PS_16;
			dcmr >>= 1;
			break;
		case 32:
			dccr |= mcf5206e_DRAMC_DCCR_PS_32;
			dcmr >>= 0;
			break;
	}
	imm->dramc.DCCR0 = dccr;
	imm->dramc.DCMR0 = dcmr;
#endif

	/*
	 * Prime the pump, dummy reads and writes
	 */
	junk = *(uint32 *)0x00000000;
	*(uint32 *)0x00000000 = junk;
	junk = *(uint32 *)0x00000004;
	*(uint32 *)0x00000004 = junk;
	junk = *(uint32 *)0x00000008;
	*(uint32 *)0x00000008 = junk;
	junk = *(uint32 *)0x0000000C;
	*(uint32 *)0x0000000C = junk;
	junk = *(uint32 *)0x00000010;
	*(uint32 *)0x00000010 = junk;
	junk = *(uint32 *)0x00000014;
	*(uint32 *)0x00000014 = junk;
	junk = *(uint32 *)0x00000018;
	*(uint32 *)0x00000018 = junk;
	junk = *(uint32 *)0x0000001C;
	*(uint32 *)0x0000001C = junk;

	if (bank_two)
	{
		imm->dramc.DCCR1 = imm->dramc.DCCR0;
		imm->dramc.DCMR1 = imm->dramc.DCMR0;
		imm->dramc.DCAR1 = (uint16)mcf5206e_DRAMC_DCAR_BASE(dram_size);

		/*
		 * Prime the pump, dummy reads and writes
		 */
		junk = *(uint32 *)(dram_size + 0x00000000);
		*(uint32 *)(dram_size + 0x00000000) = junk;
		junk = *(uint32 *)(dram_size + 0x00000004);
		*(uint32 *)(dram_size + 0x00000004) = junk;
		junk = *(uint32 *)(dram_size + 0x00000008);
		*(uint32 *)(dram_size + 0x00000008) = junk;
		junk = *(uint32 *)(dram_size + 0x0000000C);
		*(uint32 *)(dram_size + 0x0000000C) = junk;
		junk = *(uint32 *)(dram_size + 0x00000010);
		*(uint32 *)(dram_size + 0x00000010) = junk;
		junk = *(uint32 *)(dram_size + 0x00000014);
		*(uint32 *)(dram_size + 0x00000014) = junk;
		junk = *(uint32 *)(dram_size + 0x00000018);
		*(uint32 *)(dram_size + 0x00000018) = junk;
		junk = *(uint32 *)(dram_size + 0x0000001C);
		*(uint32 *)(dram_size + 0x0000001C) = junk;
	}
}
/********************************************************************/

#define PATTERN_1	(0xA55A9669)
#define PATTERN_2	(0xF0F0F0F0)

static int
probe (uint32 base, uint32 offset)
{
	/*
	 * This routine non-destructively probes a memory address to
	 * determine if physical memory exists, or if the address
	 * is shadowed or non-existant at all.  A return value of 1
	 * indicates physical memory (that is not shadowed) exists at
	 * the address, a return value of 0 indicates that no physical
	 * memory is present.
	 */
	uint32 base_orig;
	uint32 offset_orig;
	uint32 data;

	/*
	 * Step 1) Retain original values of address contents.
	 */
	base_orig = *(uint32 *)(base);

#ifdef __MWERKS__
	noop();
#else
	asm ("	nop");
#endif

	offset_orig = *(uint32 *)(base + offset);

#ifdef __MWERKS__
	noop();
#else
	asm ("	nop");
#endif

	/*
	 * Step 2) Write Pattern 2 to 'offset'
	 */
	*(uint32 *)(base + offset) = PATTERN_2;

#ifdef __MWERKS__
	noop();
#else	
	asm ("	nop");
#endif
	/*
	 * Step 3) Pattern 1 'base' in order to detect shadow.
	 */
	*(uint32 *)(base) = PATTERN_1;
	
#ifdef __MWERKS__
	noop();
#else	
	asm ("	nop");
#endif

	/*
	 * Step 4) Read 'offset'
	 */
	data = *(uint32 *)(base + offset);

#ifdef __MWERKS__
	noop();
#else
	asm ("	nop");
#endif

	/*
	 * Step 5) Restore original values
	 */
	*(uint32 *)(base + offset) = offset_orig;

#ifdef __MWERKS__
	noop();
#else	
	asm ("	nop");
#endif

	*(uint32 *)(base) = base_orig;

#ifdef __MWERKS__
	noop();
#else	
	asm ("	nop");
#endif

	if (data == PATTERN_2)
	{
		/*
		 * Real physical memory exists at address
		 */
		return 1;
	}
	else
	{
		/*
		 * No physical memory exists at physical address
		 */
		return 0;
	}
}
/********************************************************************/

/*
 * Out of reset, the low-level assembly code calls this routine to
 * initialize the mcf5206e for this board. A temporary stack has been
 * setup in the internal SRAM, and the stack pointer will be changed
 * to point to DRAM once this routine returns.
 */
void
mcf5206e_init (mcf5206e_IMM *imm)
{
	/*
	 * This routine executed upon reset to initialize
	 * mcf5206e periphs.  An initial stack must have been setup
	 * in the SRAM in order for this routine to work.
	 */
	
	/* 
	 * The VECTOR_TABLE is defined in vectors.s 
	 */
	extern ADDRESS VECTOR_TABLE[];

	mcf5206e_sim_init(imm);
	mcf5206e_pp_init(imm);
	mcf5206e_timer_init(imm);
	mcf5206e_cs_init(imm);
	mcf5206e_dramc_init(imm);
//	mcf5206e_uart_init(imm);

    /*
     * Point VBR to the vector table - MUST be aligned to 1M boundary
     */
    mcf5206e_wr_vbr((uint32)VECTOR_TABLE);
 
    /*
     * Invalidate the cache and disable it
     */
    mcf5206e_wr_cacr(mcf5206e_CACR_CINV);

	/*
	 * Setup SRAMBAR and MBAR
	 */
    mcf5206e_wr_rambar( 0
		| mcf5206e_SRAMBAR_BASE(SRAM_ADDRESS)
		| mcf5206e_SRAMBAR_AS_CI
		| mcf5206e_SRAMBAR_V
		) ;

    mcf5206e_wr_mbar( 0
		| mcf5206e_MBAR_BASE(IMM_ADDRESS)
		| mcf5206e_MBAR_V
		) ;

	*(uint32 *)(0) = 0;	/* good for detecting NULL dereferences */

}
/********************************************************************/

	
void __declspec(interrupt) exception_handler (void) 
{
	/* empty */
}

 
void __declspec(interrupt) irq_handler (void) 
{
	/* empty */
}