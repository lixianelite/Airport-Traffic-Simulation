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

//this function was used to get the airplane's name;
char* airplane_getName(Airplane* airplane);

//function used to get the airport the airplane depart from;
Airport* airplane_getSource(Airplane* airplane);

//function used to get the airport the airplane flies to;
Airport* airplane_getDestination(Airplane* airplane);

//function used to created the airplane;
/* param:
 * name, airplane's name;
 * speed, airplane's fly speed;
 * num, the capacity of the passenger this airplane can carry
 */
Airplane* createAirplane(char* name, double speed, int num);

//function used to get the passenger's number in the airplane;
int airplane_getPassengerNum(Airplane* airplane);

/*
 * function used to set the number of passenger;
 */
void airplane_setPassenger(Airplane* airplane);


//get the airplane's speed
double airplane_getSpeed(Airplane* airplane);

//set the airplane's destination;
void airplane_setDestination(Airplane* airplane, Airport* airport);

//set the airplane's departure airport;
void airplane_setSource(Airplane* airplane, Airport* airport);

//get the capacity of the airplane, maximum number of passengers this airplane can carry
int airplane_getCapacity(Airplane* airplane);

//get the label of the runway, this airplane occupies.
int airplane_getRunwayOccupied(Airplane* airplane);

//set the runway label this airplane will occupy.
void airplane_setRunwayOccupied(Airplane* airplane, int num);

#endif
