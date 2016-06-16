s0 0 *	i0 0 N * N
s0 1 *	s0 1 R * N
s0 _ *	r0 _ L * N
r0 0 *	r0 0 L * N

i0 0 1	i0 0 N 0 R
i0 0 _ 	i1 0 N 1 L
i0 0 0 	i1 0 N 1 L
i1 0 0 	i1 0 N 0 L
i1 0 _ 	s0 0 R _ R

r0 0 *  r0 0 L * N
r0 1 *  r0 1 L * N
r0 _ *  s1 _ R * N

s1 1 *	d0 1 N * N
s1 0 *	s1 0 R * N
s1 _ _	!x0 _ N * N

d0 1 1 d1 1 N 0 R
d1 1 1 d3 1 N 1 L
d1 1 0 d3 1 N 0 L
d1 1 _ d2 1 N _ L
d2 1 0 d3 1 N _ L
d0 1 0 d0 1 N 1 R
d3 1 0 d3 1 N 0 L
d3 1 1 d3 1 N 1 L
d3 1 _ s1 1 R _ R

# one zero even check by binary counter.
# sx --- Skip x
# ix --- increment
# dx --- decrement
# r0 --- rewind
# x0 --- the accept state
