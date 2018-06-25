load	0 _ load 	R 	0 R
load	1 _ load 	R 	1 R
load 	+ _ rew		N 	_ L

rew 	+ 0	rew 	N 	0 L
rew 	+ 1	rew 	N 	1 L
rew 	+ _ add		R 	_ R

add		0 0 add 	R 	0 R
add 	0 1 add 	R 	1 R
add		0 _ add 	R 	0 R
add 	1 0 add 	R 	1 R
add 	1 1	addc	R 	0 R
add 	1 _ add 	R 	1 R
add		_ 0 add 	N 	0 R
add 	_ 1 add 	N 	1 R
add 	_ _ rew		N 	_ L

addc 	0 0 add 	R 	1 R
addc 	0 _ add 	R 	1 R
addc 	_ 0 add 	N 	1 R
addc 	_ _ rew 	N 	1 L
addc 	0 1 addc	R 	0 R
addc 	_ 1 addc	N 	0 R
addc 	1 0 addc 	R 	0 R
addc 	1 _ addc 	R 	0 R
addc 	1 1 addc 	R 	1 R

rew 	_ 0 rew 	N 	0 L
rew 	_ 1 rew 	N 	1 L
rew 	_ _ !stop 	N 	_ R
