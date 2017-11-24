//
//  Airplane.c
//  Assignment5
//
//  Created by Bravado on 11/23/17.
//  Copyright © 2017 Bravado. All rights reserved.
//

#include "Airplane.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct Airplane {
    char* m_name;
    int passenger_capacity;
    int num_of_passengers;
    double m_speed;
    int runwayOccupied;
    Airport* source;
    Airport* destination;
}Airplane;

char* airplane_getName(Airplane* airplane){
    return airplane -> m_name;
}

int airplane_getRunwayOccupied(Airplane* airplane){
    return airplane -> runwayOccupied;
}

void airplane_setRunwayOccupied(Airplane* airplane, int num){
    airplane -> runwayOccupied = num;
}

int airplane_getPassengerNum(Airplane* airplane){
    return airplane -> num_of_passengers;
}

void airplane_setPassenger(Airplane* airplane){
    int capacity = airplane -> passenger_capacity;
    int r = rand() % capacity;
    airplane -> num_of_passengers = r;
}

double airplane_getSpeed(Airplane* airplane){
    return airplane -> m_speed;
}

void airplane_setDestination(Airplane* airplane, Airport* airport){
    airplane -> destination = airport;
}

Airport* airplane_getDestination(Airplane* airplane){
    return airplane -> destination;
}


void airplane_setSource(Airplane* airplane, Airport* airport){
    airplane -> source = airport;
}

Airport* airplane_getSource(Airplane* airplane){
    return airplane -> source;
}

int airplane_getCapacity(Airplane* airplane){
    return airplane -> passenger_capacity;
}

Airplane* createAirplane(char* name, double speed, int num){
    Airplane* airplane = (Airplane*)malloc(sizeof(Airplane));
    airplane -> m_name = name;
    airplane -> m_speed = speed;
    airplane -> passenger_capacity = num;
    return airplane;
}


