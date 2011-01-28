
void write_digit (void);

int main (void)
{

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

