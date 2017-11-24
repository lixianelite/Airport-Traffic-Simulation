//
//  Airport.h
//  Assignment5
//
//  Created by Bravado on 11/23/17.
//  Copyright © 2017 Bravado. All rights reserved.
//

#ifndef Airport_h

#define Airport_h

#include <stdio.h>
#include <stdbool.h>
#include "Airplane.h"
#include "PriorityQueue.h"
#include "publicInterface.h"
#include "Simulator.h"

Airport* CreateAirport(char* name, double runwayTimeToLand, double requiredTimeOnGround, double takeOffTime, int num_runway, double coordinate_X, double coordinate_Y);

double calculate_distance(Airport* airport1, Airport* airport2);

void Airport_handle(Airport* airport, AirportEvent* event);

char* airport_getName(Airport* airport);

double event_getTime(AirportEvent* event);

Airport* event_getAirport(AirportEvent* event);

int event_getType(AirportEvent* event);

Airplane* event_getAirplane(AirportEvent* event);

AirportEvent* eventGenerator(Airplane* m_airplane, double ts);


#endif






