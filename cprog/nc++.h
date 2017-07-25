/*
 * nc++.h
 *
 *  Created on: 2017/07/22
 *      Author: sin
 */

#ifndef CPROG_NC___H_
#define CPROG_NC___H_

#include <random>
std::random_device _randev; 		// _randev used only for seed
std::mt19937 _mtrand(_randev()); 	// random number function
std::uniform_int_distribution<int> _coin(0,1);

#define ndif if ( _coin(_mtrand) == 1 )
#define ndswitch(x) switch(_mtrand() % (x))

#endif /* CPROG_NC___H_ */
