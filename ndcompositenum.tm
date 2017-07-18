cp 0 _ _ cp R 0 R _ N
cp 1 _ _ cp R 1 R _ N
cp # _ _ rew N _ L _ N
rew # 0 _ rew N 0 L _ N
rew # 1 _ rew N 1 L _ N
rew # _ _ ndmul N _ R _ N

ndmul # * _ add N * N _ N
ndmul # * 0 add N * N 0 N
ndmul # * 1 add N * N 1 N
ndmul # * 0 cmp N * N * N
ndmul # * 1 cmp N * N * N


add		* 0 0 add 	N 0 R 	0 R
add 	* 0 1 add 	N 0 R 	1 R
add		* 0 _ add 	N 0 R 	0 R
add 	* 1 0 add 	N 1 R 	1 R
add 	* 1 1 addc	N 1 R 	0 R
add 	* 1 _ add 	N 1 R 	1 R
add		* _ 0 add 	N _ N 	0 R
add 	* _ 1 add 	N _ N 	1 R
add 	* _ _ addrw	N _ L 	_ L

addc 	* 0 0 add 	N 0 R 	1 R
addc 	* 0 _ add 	N 0 R 	1 R
addc 	* _ 0 add 	N _ N 	1 R
addc 	* _ _ addrw 	N _ L 	1 L
addc 	* 0 1 addc	N 0 R 	0 R
addc 	* _ 1 addc	N _ N 	0 R
addc 	* 1 0 addc 	N 1 R 	0 R
addc 	* 1 _ addc 	N 1 R 	0 R
addc 	* 1 1 addc 	N 1 R 	1 R

addrw 	* 0 0 addrw 	N 0 L 0 L
addrw 	* 0 1 addrw 	N 0 L 1 L
addrw 	* 1 0 addrw 	N 1 L 0 L
addrw 	* 1 1 addrw 	N 1 L 1 L
addrw 	* _ 0 addrw 	N _ N 0 L
addrw 	* _ 1 addrw 	N _ N 1 L
addrw 	* _ _ ndmul 	N _ R _ R
