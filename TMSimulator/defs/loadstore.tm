find.@ 	@ _ _ 	ldaddr 	R _ N _ N
find.@ 	_ _ _ 	find.@ 	R _ N _ N
find.@ 	0 _ _ 	find.@ 	R _ N _ N
find.@ 	1 _ _ 	find.@ 	R _ N _ N

ldaddr 	0 _ _ 	ldaddr 	R 0 R _ N
ldaddr 	1 _ _ 	ldaddr 	R 1 R _ N
ldaddr 	# _ _ 	ldaddr.rew 	N _ L _ N
ldaddr 	@ _ _ 	ldaddr.rew 	N _ L _ N
ldaddr.rew @ 0 _ ldaddr.rew N 0 L _ N
ldaddr.rew @ 1 _ ldaddr.rew N 1 L _ N
ldaddr.rew @ _ _ findaddr N _ R _ N

findaddr @ 0 _ findaddr.comp R 0 N _ N
findaddr @ 1 _ findaddr.comp R 1 N _ N

findaddr.comp 0 0 _ findaddr.comp R 0 R _ N
findaddr.comp 1 1 _ findaddr.comp R 1 R _ N
findaddr.comp 0 1 _ findaddr.fail N 1 L _ N
findaddr.comp 1 0 _ findaddr.fail N 0 L _ N
findadr.fail 0 0 _ findaddr.fail N 0 L _ N
findadr.fail 0 1 _ findaddr.fail N 1 L _ N
findadr.fail 1 0 _ findaddr.fail N 0 L _ N
findadr.fail 1 1 _ findaddr.fail N 1 L _ N
