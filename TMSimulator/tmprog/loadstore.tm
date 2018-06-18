#
#
addrcpy 0 _	addrcpy R 0 R
addrcpy 1 _ 	addrcpy R 1 R
addrcpy % _ 	addrrew N _ L

addrrew % 0 	addrrew N 0 L
addrrew % 1 	addrrew N 1 L
addrrew % _ 	searcha R _ R

searcha 0 ? 	searcha R ? N
searcha 1 ? 	searcha R ? N
searcha _ ? 	searcha R ? N
searcha + ? 	searcha R ? N
searcha @ ? 	matcha 	R ? N
searcha % ?		!newaddr N ? N

matcha 	0 0 	matcha 	R 0 R
matcha  0 1 	failrew N 1 L
matcha 	1 1 	matcha 	R 1 R
matcha  1 0 	failrew N 0 L
matcha  0 B 	failrew N B L
matcha  1 B 	failrew N B L
matcha  + 0 	failrew N 0 L
matcha  + 1 	failrew N 1 L

failrew ? 0 	failrew N 0 L
failrew ? 1 	failrew N 1 L
failrew ? _ 	searcha R _ R

matcha  + _ 	matchrew  N _ L

matchrew + 0 	matchrew  N 0 L
matchrew + 1 	matchrew  N 1 L
matchrew + _ 	valcpy	  R _ R

valcpy 0 ? 	valcpy  R 0 R
valcpy 1 ? 	valcpy  R 1 R

valcpy @ 0 	valcpy  N _ R
valcpy @ 1 	valcpy  N _ R
valcpy @ _ 	valback N _ L
valcpy _ 0 	valcpy  N _ R
valcpy _ 1 	valcpy  N _ R
valcpy _ _ 	valback N _ L
valback ? _ 	valback N _ L
valback ? 0 	valrew  N 0 L
valback ? 1 	valrew  N 1 L

valrew  ? 0 	valrew  N 0 L
valrew  ? 1 	valrew  N 1 L
valrew  ? _ 	return 	N _ R
