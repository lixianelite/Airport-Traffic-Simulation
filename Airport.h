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

//used to create the airport
//name, create the airport's name;
//runwayTimetoLand, the time needed for the airplane to land.
//requiredtimeOnGround, time needed for airplane to stay in this airport.
//takeofftime, time needed for airplane to take off, i.e the time this airplane needs to occupy the runway.
Airport* CreateAirport(char* name, double runwayTimeToLand, double requiredTimeOnGround, double takeOffTime, int num_runway, double coordinate_X, double coordinate_Y);

//create the distance between diffrent airport, used to set another plane arrival event.
double calculate_distance(Airport* airport1, Airport* airport2);

//handler used to handle the airport event.
/*
 * param:
 * airport, which airport needs to handle the event.
 * event, the event needs to be handled.
 */
void Airport_handle(Airport* airport, AirportEvent* event);

//get the airport name.
char* airport_getName(Airport* airport);

//get the event timestamp.
double event_getTime(AirportEvent* event);

//get the event's airport. used to decide which airport need to handle the event.
Airport* event_getAirport(AirportEvent* event);

//get the event's type, i.e arrival, land, takeoff, departure.
int event_getType(AirportEvent* event);

//get the airplane this event involves in.
Airplane* event_getAirplane(AirportEvent* event);

//generate the event, used to initialize the event at the beginning.
AirportEvent* eventGenerator(Airplane* m_airplane, double ts);


#endif






