prog:stbrt # B B  !prog:end  N * N * N
prog:stbrt a B B  incr:crr  N * N * N
prog:stbrt b B B  incr:crr  N * N * N

incr:crr * b *	incr:crr  N a R * N
incr:crr * B *	incr:rew  N b L * N
incr:crr * a *	incr:rew  N b L * N
incr:rew * a *	incr:rew  N a L * N
incr:rew * B *	incr:end  N B R * N

incr:end * * *	move:cpy  N * N * N

move:cpy * a B move:cpy  N a R a R
move:cpy * b B move:cpy  N b R b R
move:cpy * B B move:rew  N B L B L
move:rew * a a move:rew  N a L a L
move:rew * b b move:rew  N b L b L
move:rew * B B move:end  N B R B R

move:end * * * fwd:crr  N * N * N

fwd:crr * * b	  fwd:chk  N * N a R
fwd:chk * * b   fwd:rew  N * N b L
fwd:chk * * a   fwd:rew  N * N a L
fwd:chk * * B   fwd:clr  N * N B L
fwd:clr * * a   fwd:clr  N * N B L
fwd:clr * * b   fwd:rew  N * N b L
fwd:clr * * B   fwd:rew  N * N B N
fwd:rew * * a   fwd:rew  N * N a L
fwd:rew * * b   fwd:rew  N * N b L
fwd:rew * * B	  fwd:end  N * N B R
fwd:crr * * a	  fwd:crr  N * N b R

fwd:end * * a   fwd:crr  R * N * N
fwd:end * * b   fwd:crr  R * N * N
fwd:end * * B	  rebd:chk  N * N * N

rebd:chk a * * 	mem.a:skp  R * N * N
rebd:chk b * * 	mem.b:skp  R * N * N
rebd:chk # * * 	mem.#:skp  R * N * N
mem.a:skp a * * 	mem.a:skp  R * N * N
mem.a:skp b * * 	mem.a:skp  R * N * N
mem.a:skp # * * 	move.a:cpy  R * N * N
mem.b:skp a * * 	mem.b:skp  R * N * N
mem.b:skp b * * 	mem.b:skp  R * N * N
mem.b:skp # * * 	move.b:cpy  R * N * N
mem.#:skp a * * 	move.#:cpy  N * N * N
mem.#:skp b * * 	move.#:cpy  N * N * N


move.a:cpy * a B	move.a:cpy  N a R a R
move.a:cpy * b B	move.a:cpy  N b R b R
move.a:cpy * B B	move.a:rew  N B L B L
move.a:rew * a a	move.a:rew  N a L a L
move.a:rew * b b	move.a:rew  N b L b L
move.a:rew * B B	move.a:end  N B R B R

move.a:end * * * 	fwd.a:crr  N * N * N

fwd.a:crr * * b		fwd.a:chk  N * N a R
fwd.a:chk * * b 	fwd.a:rew  N * N b L
fwd.a:chk * * a 	fwd.a:rew  N * N a L
fwd.a:chk * * B 	fwd.a:clr  N * N B L
fwd.a:clr * * a 	fwd.a:clr  N * N B L
fwd.a:clr * * b 	fwd.a:rew  N * N b L
fwd.a:clr * * B 	fwd.a:rew  N * N B N
fwd.a:rew * * a 	fwd.a:rew  N * N a L
fwd.a:rew * * b 	fwd.a:rew  N * N b L
fwd.a:rew * * B		fwd.a:end  N * N B R
fwd.a:crr * * a		fwd.a:crr  N * N b R

fwd.a:end * * B 	cmp.a:chck  N * N * N
fwd.a:end * * a 	fwd.a:crr  R * N * N
fwd.a:end * * b 	fwd.a:crr  R * N * N
cmp.a:chck a * * 	cmp.a:succ  N * N * N
cmp.a:chck b * * 	cmp.a:fbil  N * N * N

move.b:cpy * a B	move.b:cpy  N a R a R
move.b:cpy * b B	move.b:cpy  N b R b R
move.b:cpy * B B	move.b:rew  N B L B L
move.b:rew * a a	move.b:rew  N a L a L
move.b:rew * b b	move.b:rew  N b L b L
move.b:rew * B B	move.b:end  N B R B R

move.b:end * * * 	fwd.b:crr  N * N * N

fwd.b:crr * * b		fwd.b:chk  N * N a R
fwd.b:chk * * b 	fwd.b:rew  N * N b L
fwd.b:chk * * a 	fwd.b:rew  N * N a L
fwd.b:chk * * B 	fwd.b:clr  N * N B L
fwd.b:clr * * a 	fwd.b:clr  N * N B L
fwd.b:clr * * b 	fwd.b:rew  N * N b L
fwd.b:clr * * B 	fwd.b:rew  N * N B N
fwd.b:rew * * a 	fwd.b:rew  N * N a L
fwd.b:rew * * b 	fwd.b:rew  N * N b L
fwd.b:rew * * B		fwd.b:end  N * N B R
fwd.b:crr * * a		fwd.b:crr  N * N b R

fwd.b:end * * B 	cmp.b:chck  N * N * N
fwd.b:end * * a 	fwd.b:crr  R * N * N
fwd.b:end * * b 	fwd.b:crr  R * N * N
cmp.b:chck a * * 	cmp.b:fbil  N * N * N
cmp.b:chck b * * 	cmp.b:succ  N * N * N

move.#:cpy * a B	move.#:cpy  N a R a R
move.#:cpy * b B	move.#:cpy  N b R b R
move.#:cpy * B B	move.#:rew  N B L B L
move.#:rew * a a	move.#:rew  N a L a L
move.#:rew * b b	move.#:rew  N b L b L
move.#:rew * B B	move.#:end  N B R B R

move.#:end * * * 	fwd.#:crr  N * N * N

fwd.#:crr * * b		fwd.#:chk  N * N a R
fwd.#:chk * * b 	fwd.#:rew  N * N b L
fwd.#:chk * * a 	fwd.#:rew  N * N a L
fwd.#:chk * * B 	fwd.#:clr  N * N B L
fwd.#:clr * * a 	fwd.#:clr  N * N B L
fwd.#:clr * * b 	fwd.#:rew  N * N b L
fwd.#:clr * * B 	fwd.#:rew  N * N B N
fwd.#:rew * * a 	fwd.#:rew  N * N a L
fwd.#:rew * * b 	fwd.#:rew  N * N b L
fwd.#:rew * * B		fwd.#:end  N * N B R
fwd.#:crr * * a		fwd.#:crr  N * N b R

fwd.#:end * * B 	comp#:chck  N * N * N
fwd.#:end * * a 	fwd.#:crr  R * N * N
fwd.#:end * * b 	fwd.#:crr  R * N * N
comp#:chck B * * 	!prog:bcc  N * N * N

cmp.a:succ * * * 	rept:rew  L * N * N
cmp.b:succ * * * 	rept:rew  L * N * N
rept:rew a * * 		rept:rew  L * N * N
rept:rew b * * 		rept:rew  L * N * N
rept:rew # * * 		rept:rew  L * N * N
rept:rew B * * 		incr:crr  R * N * N
