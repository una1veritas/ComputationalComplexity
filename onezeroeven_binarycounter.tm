# -rw
skip0 0 *	inc:0 0 N * N
skip0 1 *	skip0 1 R * N
skip0 _ *	rewnd _ L * N
rewnd 0 *	rewnd 0 L * N

inc:0 0 1	inc:0 0 N 0 R
inc:0 0 _ 	inc:1 0 N 1 L
inc:0 0 0 	inc:1 0 N 1 L
inc:1 0 0 	inc:1 0 N 0 L
inc:1 0 _ 	skip0 0 R _ R

rewnd 0 * 	rewnd 0 L * N
rewnd 1 * 	rewnd 1 L * N
rewnd _ * 	skip1 _ R * N

skip1 1 *	dec:0 1 N * N
skip1 0 *	skip1 0 R * N
skip1 _ _	!accpt _ N * N

dec:0 1 1 	dec:1 1 N 0 R
dec:1 1 1 	dec:3 1 N 1 L
dec:1 1 0 	dec:3 1 N 0 L
dec:1 1 _ 	dec:2 1 N _ L
dec:2 1 0 	dec:3 1 N _ L
dec:0 1 0 	dec:0 1 N 1 R
dec:3 1 0 	dec:3 1 N 0 L
dec:3 1 1 	dec:3 1 N 1 L
dec:3 1 _ 	skip1 1 R _ R
