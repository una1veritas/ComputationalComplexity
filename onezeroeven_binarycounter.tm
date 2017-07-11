// 6 state increment for 0s decrement for 1s machine
//
inc0 1 *	inc0 	R * N 	// skip 1s
inc0 0 1	inc0 	N 0 R 	// carry up
inc0 0 _ 	inc0rew N 1 L 
inc0 0 0 	inc0rew N 1 L
inc0rew 0 0 inc0rew N 0 L
inc0rew 0 _ inc0 	R _ R 	// to the next char
inc0 _ *	rew 	L * N 	// rewind input tape head

rew 0 *		rew 	L * N
rew 0 * 	rew  	L * N
rew 1 * 	rew 	L * N
rew _ * 	dec1 	R * N

dec1 0 *	dec1 	R * N 	// skip 0s
dec1 1 0 	dec1 	N 1 R 	// borrow from higher bit
dec1 1 1 	dec1chk N 0 R 	// check whether msb
dec1chk 1 1 dec1rew N 1 L 	// was not msb
dec1chk 1 0 dec1rew N 0 L 	// was not msb
dec1chk 1 _ dec1clr N _ L 	// was msb
dec1clr 1 0 dec1rew N _ L 	// erase the prev. msb
dec1rew 1 0 dec1rew N 0 L
dec1rew 1 1 dec1rew N 1 L
dec1rew 1 _ dec1 	R _ R

dec1 _ _	!accpt 	N * N

