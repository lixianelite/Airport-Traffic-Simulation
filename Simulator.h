//
//  Simulator.h
//  Assignment5
//
//  Created by Bravado on 11/23/17.
//  Copyright © 2017 Bravado. All rights reserved.
//

#ifndef Simulator_h
#define Simulator_h

#include <stdio.h>
#include "Airport.h"
#include "PriorityQueue.h"

void Schedule(AirportEvent* event);

Airport* getDestination(Airport* source);

double getCurrentTime();

#endif
