//
//  Airplane.h
//  Assignment5
//
//  Created by Bravado on 11/23/17.
//  Copyright © 2017 Bravado. All rights reserved.
//


#ifndef Airplane_h
#define Airplane_h

#include <stdio.h>
#include "Airport.h"
#include "publicInterface.h"

char* airplane_getName(Airplane* airplane);

Airport* airplane_getSource(Airplane* airplane);

Airport* airplane_getDestination(Airplane* airplane);

Airplane* createAirplane(char* name, double speed, int num);

int airplane_getPassengerNum(Airplane* airplane);

void airplane_setPassenger(Airplane* airplane);

double airplane_getSpeed(Airplane* airplane);

void airplane_setDestination(Airplane* airplane, Airport* airport);

void airplane_setSource(Airplane* airplane, Airport* airport);

int airplane_getCapacity(Airplane* airplane);

int airplane_getRunwayOccupied(Airplane* airplane);

void airplane_setRunwayOccupied(Airplane* airplane, int num);

#endif
