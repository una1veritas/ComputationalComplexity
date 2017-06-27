prog:start # _ _  !prog:end  N * N * N
prog:start 0 _ _  incr1:crr  N * N * N
prog:start 1 _ _  incr1:crr  N * N * N

incr1:crr * 1 *	incr1:crr  N 0 R * N
incr1:crr * _ *	incr1:rew  N 1 L * N
incr1:crr * 0 *	incr1:rew  N 1 L * N
incr1:rew * 0 *	incr1:rew  N 0 L * N
incr1:rew * _ *	incr1:end  N _ R * N

incr1:end * * *	mov1_2:cpy  N * N * N

mov1_2:cpy * 0 _ mov1_2:cpy  N 0 R 0 R
mov1_2:cpy * 1 _ mov1_2:cpy  N 1 R 1 R
mov1_2:cpy * _ _ mov1_2:rew  N _ L _ L
mov1_2:rew * 0 0 mov1_2:rew  N 0 L 0 L
mov1_2:rew * 1 1 mov1_2:rew  N 1 L 1 L
mov1_2:rew * _ _ mov1_2:end  N _ R _ R

mov1_2:end * * * fwd:crr  N * N * N

fwd:crr * * 1	  fwd:chk  N * N 0 R
fwd:chk * * 1   fwd:rew  N * N 1 L
fwd:chk * * 0   fwd:rew  N * N 0 L
fwd:chk * * _   fwd:clr  N * N _ L
fwd:clr * * 0   fwd:clr  N * N _ L
fwd:clr * * 1   fwd:rew  N * N 1 L
fwd:clr * * _   fwd:rew  N * N _ N
fwd:rew * * 0   fwd:rew  N * N 0 L
fwd:rew * * 1   fwd:rew  N * N 1 L
fwd:rew * * _	  fwd:end  N * N _ R
fwd:crr * * 0	  fwd:crr  N * N 1 R

fwd:end * * 0   fwd:crr  R * N * N
fwd:end * * 1   fwd:crr  R * N * N
fwd:end * * _	  read:chk  N * N * N

read:chk 0 * * 	mem.0:skp  R * N * N
read:chk 1 * * 	mem.1:skp  R * N * N
read:chk # * * 	mem.#:skp  R * N * N
mem.0:skp 0 * * 	mem.0:skp  R * N * N
mem.0:skp 1 * * 	mem.0:skp  R * N * N
mem.0:skp # * * 	mov1_2.0:cpy  R * N * N
mem.1:skp 0 * * 	mem.1:skp  R * N * N
mem.1:skp 1 * * 	mem.1:skp  R * N * N
mem.1:skp # * * 	mov1_2.1:cpy  R * N * N
mem.#:skp 0 * * 	mov1_2.#:cpy  N * N * N
mem.#:skp 1 * * 	mov1_2.#:cpy  N * N * N


mov1_2.0:cpy * 0 _	mov1_2.0:cpy  N 0 R 0 R
mov1_2.0:cpy * 1 _	mov1_2.0:cpy  N 1 R 1 R
mov1_2.0:cpy * _ _	mov1_2.0:rew  N _ L _ L
mov1_2.0:rew * 0 0	mov1_2.0:rew  N 0 L 0 L
mov1_2.0:rew * 1 1	mov1_2.0:rew  N 1 L 1 L
mov1_2.0:rew * _ _	mov1_2.0:end  N _ R _ R

mov1_2.0:end * * * 	fwd.0:crr  N * N * N

fwd.0:crr * * 1		fwd.0:chk  N * N 0 R
fwd.0:chk * * 1 	fwd.0:rew  N * N 1 L
fwd.0:chk * * 0 	fwd.0:rew  N * N 0 L
fwd.0:chk * * _ 	fwd.0:clr  N * N _ L
fwd.0:clr * * 0 	fwd.0:clr  N * N _ L
fwd.0:clr * * 1 	fwd.0:rew  N * N 1 L
fwd.0:clr * * _ 	fwd.0:rew  N * N _ N
fwd.0:rew * * 0 	fwd.0:rew  N * N 0 L
fwd.0:rew * * 1 	fwd.0:rew  N * N 1 L
fwd.0:rew * * _		fwd.0:end  N * N _ R
fwd.0:crr * * 0		fwd.0:crr  N * N 1 R

fwd.0:end * * _ 	cmp.0:chck  N * N * N
fwd.0:end * * 0 	fwd.0:crr  R * N * N
fwd.0:end * * 1 	fwd.0:crr  R * N * N
cmp.0:chck 0 * * 	cmp.0:succ  N * N * N
cmp.0:chck 1 * * 	cmp.0:fail  N * N * N

mov1_2.1:cpy * 0 _	mov1_2.1:cpy  N 0 R 0 R
mov1_2.1:cpy * 1 _	mov1_2.1:cpy  N 1 R 1 R
mov1_2.1:cpy * _ _	mov1_2.1:rew  N _ L _ L
mov1_2.1:rew * 0 0	mov1_2.1:rew  N 0 L 0 L
mov1_2.1:rew * 1 1	mov1_2.1:rew  N 1 L 1 L
mov1_2.1:rew * _ _	mov1_2.1:end  N _ R _ R

mov1_2.1:end * * * 	fwd.1:crr  N * N * N

fwd.1:crr * * 1		fwd.1:chk  N * N 0 R
fwd.1:chk * * 1 	fwd.1:rew  N * N 1 L
fwd.1:chk * * 0 	fwd.1:rew  N * N 0 L
fwd.1:chk * * _ 	fwd.1:clr  N * N _ L
fwd.1:clr * * 0 	fwd.1:clr  N * N _ L
fwd.1:clr * * 1 	fwd.1:rew  N * N 1 L
fwd.1:clr * * _ 	fwd.1:rew  N * N _ N
fwd.1:rew * * 0 	fwd.1:rew  N * N 0 L
fwd.1:rew * * 1 	fwd.1:rew  N * N 1 L
fwd.1:rew * * _		fwd.1:end  N * N _ R
fwd.1:crr * * 0		fwd.1:crr  N * N 1 R

fwd.1:end * * _ 	cmp.1:chck  N * N * N
fwd.1:end * * 0 	fwd.1:crr  R * N * N
fwd.1:end * * 1 	fwd.1:crr  R * N * N
cmp.1:chck 0 * * 	cmp.1:fail  N * N * N
cmp.1:chck 1 * * 	cmp.1:succ  N * N * N

mov1_2.#:cpy * 0 _	mov1_2.#:cpy  N 0 R 0 R
mov1_2.#:cpy * 1 _	mov1_2.#:cpy  N 1 R 1 R
mov1_2.#:cpy * _ _	mov1_2.#:rew  N _ L _ L
mov1_2.#:rew * 0 0	mov1_2.#:rew  N 0 L 0 L
mov1_2.#:rew * 1 1	mov1_2.#:rew  N 1 L 1 L
mov1_2.#:rew * _ _	mov1_2.#:end  N _ R _ R

mov1_2.#:end * * * 	fwd.#:crr  N * N * N

fwd.#:crr * * 1		fwd.#:chk  N * N 0 R
fwd.#:chk * * 1 	fwd.#:rew  N * N 1 L
fwd.#:chk * * 0 	fwd.#:rew  N * N 0 L
fwd.#:chk * * _ 	fwd.#:clr  N * N _ L
fwd.#:clr * * 0 	fwd.#:clr  N * N _ L
fwd.#:clr * * 1 	fwd.#:rew  N * N 1 L
fwd.#:clr * * _ 	fwd.#:rew  N * N _ N
fwd.#:rew * * 0 	fwd.#:rew  N * N 0 L
fwd.#:rew * * 1 	fwd.#:rew  N * N 1 L
fwd.#:rew * * _		fwd.#:end  N * N _ R
fwd.#:crr * * 0		fwd.#:crr  N * N 1 R

fwd.#:end * * _ 	comp#:chck  N * N * N
fwd.#:end * * 0 	fwd.#:crr  R * N * N
fwd.#:end * * 1 	fwd.#:crr  R * N * N
comp#:chck _ * * 	!prog:acc  N * N * N

cmp.0:succ * * * 	rept:rew  L * N * N
cmp.1:succ * * * 	rept:rew  L * N * N
rept:rew 0 * * 		rept:rew  L * N * N
rept:rew 1 * * 		rept:rew  L * N * N
rept:rew # * * 		rept:rew  L * N * N
rept:rew _ * * 		incr1:crr  R * N * N
