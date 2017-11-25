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

//used to schedule the event.
void Schedule(AirportEvent* event);

//assign airplane's destination.
Airport* getDestination(Airport* source);

//get current time, used to schedule next event.
double getCurrentTime();

#endif
