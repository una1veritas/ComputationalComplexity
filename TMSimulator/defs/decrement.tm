s0	* *	c0 N * N

c0 0 _	c0 R 0 R
c0 1 _	c0 R 1 R
c0 _ _	c1 N _ L
c1 _ 0	c1 N 0 L
c1 _ 1	c1 N 1 L
c1 _ _	cx N _ R

cx * * d0 N * N

d0 _ 1 d1 N 0 R
d1 _ 1 d3 N 1 L
d1 _ 0 d3 N 0 L
d1 _ _ d2 N _ L
d2 _ 0 d3 N _ L
d0 _ 0 d0 N 1 R
d3 _ 0 d3 N 0 L
d3 _ 1 d3 N 1 L
d3 _ _ dx N _ R


dx _ _ zero    N _ N
dx _ 1 d0 N 1 N
dx _ 0 d0 N 0 N
