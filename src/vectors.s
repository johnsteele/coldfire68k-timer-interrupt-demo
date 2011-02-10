/*
 * File:	vectors.s
 * Purpose:	MCF5200 vector table for CW ROM stationery.
 *
 * 
 *
 */

	.global VECTOR_TABLE
	.global _VECTOR_TABLE
	.global ___init
	.global ___fini
	.global start

	.extern _asm_startmeup
	.extern __SP_INIT
	.extern _exception_handler
	.extern _irq_handler

	.section .reset

/*
 * Exception Vector Table
 */
VECTOR_TABLE:
_VECTOR_TABLE:
INITSP:		.dc.l	__SP_INIT				/* Initial SP			*/
INITPC:		.dc.l	start					/* Initial PC			*/
vector02:	.dc.l	_exception_handler		/* Access Error			*/
vector03:	.dc.l	_exception_handler		/* Address Error		*/
vector04:	.dc.l	_exception_handler		/* Illegal Instruction	*/
vector05:	.dc.l	_exception_handler		/* Reserved				*/
vector06:	.dc.l	_exception_handler		/* Reserved				*/
vector07:	.dc.l	_exception_handler		/* Reserved				*/
vector08:	.dc.l	_exception_handler		/* Privilege Violation	*/
vector09:	.dc.l	_exception_handler		/* Trace				*/
vector0A:	.dc.l	_exception_handler		/* Unimplemented A-Line	*/
vector0B:	.dc.l	_exception_handler		/* Unimplemented F-Line	*/
vector0C:	.dc.l	_exception_handler		/* Debug Interrupt		*/
vector0D:	.dc.l	_exception_handler		/* Reserved				*/
vector0E:	.dc.l	_exception_handler		/* Format Error			*/
vector0F:	.dc.l	_exception_handler		/* Unitialized Int.		*/
vector10:	.dc.l	_exception_handler		/* Reserved				*/
vector11:	.dc.l	_exception_handler		/* Reserved				*/
vector12:	.dc.l	_exception_handler		/* Reserved				*/
vector13:	.dc.l	_exception_handler		/* Reserved				*/
vector14:	.dc.l	_exception_handler		/* Reserved				*/
vector15:	.dc.l	_exception_handler		/* Reserved				*/
vector16:	.dc.l	_exception_handler		/* Reserved				*/
vector17:	.dc.l	_exception_handler		/* Reserved				*/
vector18:	.dc.l	_exception_handler		/* Spurious Interrupt	*/
vector19:	.dc.l	_irq_handler			/* Autovector Level 1	*/
vector1A:	.dc.l	_irq_handler			/* Autovector Level 2	*/
vector1B:	.dc.l	_irq_handler			/* Autovector Level 3	*/
vector1C:	.dc.l	_irq_handler			/* Autovector Level 4	*/
vector1D:	.dc.l	_irq_handler			/* Autovector Level 5	*/
vector1E:	.dc.l	_irq_handler			/* Autovector Level 6	*/
vector1F:	.dc.l	_irq_handler			/* Autovector Level 7	*/
vector20:	.dc.l	_exception_handler		/* TRAP #0				*/
vector21:	.dc.l	_exception_handler		/* TRAP #1				*/
vector22:	.dc.l	_exception_handler		/* TRAP #2				*/
vector23:	.dc.l	_exception_handler		/* TRAP #3				*/
vector24:	.dc.l	_exception_handler		/* TRAP #4				*/
vector25:	.dc.l	_exception_handler		/* TRAP #5				*/
vector26:	.dc.l	_exception_handler		/* TRAP #6				*/
vector27:	.dc.l	_exception_handler		/* TRAP #7				*/
vector28:	.dc.l	_exception_handler		/* TRAP #8				*/
vector29:	.dc.l	_exception_handler		/* TRAP #9				*/
vector2A:	.dc.l	_exception_handler		/* TRAP #10				*/
vector2B:	.dc.l	_exception_handler		/* TRAP #11				*/
vector2C:	.dc.l	_exception_handler		/* TRAP #12				*/
vector2D:	.dc.l	_exception_handler		/* TRAP #13				*/
vector2E:	.dc.l	_exception_handler		/* TRAP #14				*/
vector2F:	.dc.l	_exception_handler		/* TRAP #15				*/
vector30:	.dc.l	_exception_handler		/* Reserved				*/
vector31:	.dc.l	_exception_handler		/* Reserved				*/
vector32:	.dc.l	_exception_handler		/* Reserved				*/
vector33:	.dc.l	_exception_handler		/* Reserved				*/
vector34:	.dc.l	_exception_handler		/* Reserved				*/
vector35:	.dc.l	_exception_handler		/* Reserved				*/
vector36:	.dc.l	_exception_handler		/* Reserved				*/
vector37:	.dc.l	_exception_handler		/* Reserved				*/
vector38:	.dc.l	_exception_handler		/* Reserved				*/
vector39:	.dc.l	_exception_handler		/* Reserved				*/
vector3A:	.dc.l	_exception_handler		/* Reserved				*/
vector3B:	.dc.l	_exception_handler		/* Reserved				*/
vector3C:	.dc.l	_exception_handler		/* Reserved				*/
vector3D:	.dc.l	_exception_handler		/* Reserved				*/
vector3E:	.dc.l	_exception_handler		/* Reserved				*/
vector3F:	.dc.l	_exception_handler		/* Reserved				*/
vector40:	.dc.l	_irq_handler			/* User Defined Int.	*/
vector41:	.dc.l	_irq_handler
vector42:	.dc.l	_irq_handler
vector43:	.dc.l	_irq_handler
vector44:	.dc.l	_irq_handler
vector45:	.dc.l	_irq_handler
vector46:	.dc.l	_irq_handler
vector47:	.dc.l	_irq_handler
vector48:	.dc.l	_irq_handler
vector49:	.dc.l	_irq_handler
vector4A:	.dc.l	_irq_handler
vector4B:	.dc.l	_irq_handler
vector4C:	.dc.l	_irq_handler
vector4D:	.dc.l	_irq_handler
vector4E:	.dc.l	_irq_handler
vector4F:	.dc.l	_irq_handler
vector50:	.dc.l	_irq_handler
vector51:	.dc.l	_irq_handler
vector52:	.dc.l	_irq_handler
vector53:	.dc.l	_irq_handler
vector54:	.dc.l	_irq_handler
vector55:	.dc.l	_irq_handler
vector56:	.dc.l	_irq_handler
vector57:	.dc.l	_irq_handler
vector58:	.dc.l	_irq_handler
vector59:	.dc.l	_irq_handler
vector5A:	.dc.l	_irq_handler
vector5B:	.dc.l	_irq_handler
vector5C:	.dc.l	_irq_handler
vector5D:	.dc.l	_irq_handler
vector5E:	.dc.l	_irq_handler
vector5F:	.dc.l	_irq_handler
vector60:	.dc.l	_irq_handler
vector61:	.dc.l	_irq_handler
vector62:	.dc.l	_irq_handler
vector63:	.dc.l	_irq_handler
vector64:	.dc.l	_irq_handler
vector65:	.dc.l	_irq_handler
vector66:	.dc.l	_irq_handler
vector67:	.dc.l	_irq_handler
vector68:	.dc.l	_irq_handler
vector69:	.dc.l	_irq_handler
vector6A:	.dc.l	_irq_handler
vector6B:	.dc.l	_irq_handler
vector6C:	.dc.l	_irq_handler
vector6D:	.dc.l	_irq_handler
vector6E:	.dc.l	_irq_handler
vector6F:	.dc.l	_irq_handler
vector70:	.dc.l	_irq_handler
vector71:	.dc.l	_irq_handler
vector72:	.dc.l	_irq_handler
vector73:	.dc.l	_irq_handler
vector74:	.dc.l	_irq_handler
vector75:	.dc.l	_irq_handler
vector76:	.dc.l	_irq_handler
vector77:	.dc.l	_irq_handler
vector78:	.dc.l	_irq_handler
vector79:	.dc.l	_irq_handler
vector7A:	.dc.l	_irq_handler
vector7B:	.dc.l	_irq_handler
vector7C:	.dc.l	_irq_handler
vector7D:	.dc.l	_irq_handler
vector7E:	.dc.l	_irq_handler
vector7F:	.dc.l	_irq_handler
vector80:	.dc.l	_irq_handler
vector81:	.dc.l	_irq_handler
vector82:	.dc.l	_irq_handler
vector83:	.dc.l	_irq_handler
vector84:	.dc.l	_irq_handler
vector85:	.dc.l	_irq_handler
vector86:	.dc.l	_irq_handler
vector87:	.dc.l	_irq_handler
vector88:	.dc.l	_irq_handler
vector89:	.dc.l	_irq_handler
vector8A:	.dc.l	_irq_handler
vector8B:	.dc.l	_irq_handler
vector8C:	.dc.l	_irq_handler
vector8D:	.dc.l	_irq_handler
vector8E:	.dc.l	_irq_handler
vector8F:	.dc.l	_irq_handler
vector90:	.dc.l	_irq_handler
vector91:	.dc.l	_irq_handler
vector92:	.dc.l	_irq_handler
vector93:	.dc.l	_irq_handler
vector94:	.dc.l	_irq_handler
vector95:	.dc.l	_irq_handler
vector96:	.dc.l	_irq_handler
vector97:	.dc.l	_irq_handler
vector98:	.dc.l	_irq_handler
vector99:	.dc.l	_irq_handler
vector9A:	.dc.l	_irq_handler
vector9B:	.dc.l	_irq_handler
vector9C:	.dc.l	_irq_handler
vector9D:	.dc.l	_irq_handler
vector9E:	.dc.l	_irq_handler
vector9F:	.dc.l	_irq_handler
vectorA0:	.dc.l	_irq_handler
vectorA1:	.dc.l	_irq_handler
vectorA2:	.dc.l	_irq_handler
vectorA3:	.dc.l	_irq_handler
vectorA4:	.dc.l	_irq_handler
vectorA5:	.dc.l	_irq_handler
vectorA6:	.dc.l	_irq_handler
vectorA7:	.dc.l	_irq_handler
vectorA8:	.dc.l	_irq_handler
vectorA9:	.dc.l	_irq_handler
vectorAA:	.dc.l	_irq_handler
vectorAB:	.dc.l	_irq_handler
vectorAC:	.dc.l	_irq_handler
vectorAD:	.dc.l	_irq_handler
vectorAE:	.dc.l	_irq_handler
vectorAF:	.dc.l	_irq_handler
vectorB0:	.dc.l	_irq_handler
vectorB1:	.dc.l	_irq_handler
vectorB2:	.dc.l	_irq_handler
vectorB3:	.dc.l	_irq_handler
vectorB4:	.dc.l	_irq_handler
vectorB5:	.dc.l	_irq_handler
vectorB6:	.dc.l	_irq_handler
vectorB7:	.dc.l	_irq_handler
vectorB8:	.dc.l	_irq_handler
vectorB9:	.dc.l	_irq_handler
vectorBA:	.dc.l	_irq_handler
vectorBB:	.dc.l	_irq_handler
vectorBC:	.dc.l	_irq_handler
vectorBD:	.dc.l	_irq_handler
vectorBE:	.dc.l	_irq_handler
vectorBF:	.dc.l	_irq_handler
vectorC0:	.dc.l	_irq_handler
vectorC1:	.dc.l	_irq_handler
vectorC2:	.dc.l	_irq_handler
vectorC3:	.dc.l	_irq_handler
vectorC4:	.dc.l	_irq_handler
vectorC5:	.dc.l	_irq_handler
vectorC6:	.dc.l	_irq_handler
vectorC7:	.dc.l	_irq_handler
vectorC8:	.dc.l	_irq_handler
vectorC9:	.dc.l	_irq_handler
vectorCA:	.dc.l	_irq_handler
vectorCB:	.dc.l	_irq_handler
vectorCC:	.dc.l	_irq_handler
vectorCD:	.dc.l	_irq_handler
vectorCE:	.dc.l	_irq_handler
vectorCF:	.dc.l	_irq_handler
vectorD0:	.dc.l	_irq_handler
vectorD1:	.dc.l	_irq_handler
vectorD2:	.dc.l	_irq_handler
vectorD3:	.dc.l	_irq_handler
vectorD4:	.dc.l	_irq_handler
vectorD5:	.dc.l	_irq_handler
vectorD6:	.dc.l	_irq_handler
vectorD7:	.dc.l	_irq_handler
vectorD8:	.dc.l	_irq_handler
vectorD9:	.dc.l	_irq_handler
vectorDA:	.dc.l	_irq_handler
vectorDB:	.dc.l	_irq_handler
vectorDC:	.dc.l	_irq_handler
vectorDD:	.dc.l	_irq_handler
vectorDE:	.dc.l	_irq_handler
vectorDF:	.dc.l	_irq_handler
vectorE0:	.dc.l	_irq_handler
vectorE1:	.dc.l	_irq_handler
vectorE2:	.dc.l	_irq_handler
vectorE3:	.dc.l	_irq_handler
vectorE4:	.dc.l	_irq_handler
vectorE5:	.dc.l	_irq_handler
vectorE6:	.dc.l	_irq_handler
vectorE7:	.dc.l	_irq_handler
vectorE8:	.dc.l	_irq_handler
vectorE9:	.dc.l	_irq_handler
vectorEA:	.dc.l	_irq_handler
vectorEB:	.dc.l	_irq_handler
vectorEC:	.dc.l	_irq_handler
vectorED:	.dc.l	_irq_handler
vectorEE:	.dc.l	_irq_handler
vectorEF:	.dc.l	_irq_handler
vectorF0:	.dc.l	_irq_handler
vectorF1:	.dc.l	_irq_handler
vectorF2:	.dc.l	_irq_handler
vectorF3:	.dc.l	_irq_handler
vectorF4:	.dc.l	_irq_handler
vectorF5:	.dc.l	_irq_handler
vectorF6:	.dc.l	_irq_handler
vectorF7:	.dc.l	_irq_handler
vectorF8:	.dc.l	_irq_handler
vectorF9:	.dc.l	_irq_handler
vectorFA:	.dc.l	_irq_handler
vectorFB:	.dc.l	_irq_handler
vectorFC:	.dc.l	_irq_handler
vectorFD:	.dc.l	_irq_handler
vectorFE:	.dc.l	_irq_handler
vectorFF:	.dc.l	_irq_handler

start:
	move.w	#0x2700,SR
	jmp		_asm_startmeup

___init:
	rts

___fini:
	rts

	.end
