//
//  Simulator.c
//  Assignment5
//
//  Created by Bravado on 11/23/17.
//  Copyright © 2017 Bravado. All rights reserved.
//

#include "Simulator.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

Airplane** createAirplanes(int num);
void airplaneSchedule(Airplane** airplanes, int num, Airport** airports);

static Queue* FutureEventList;

double Now = 0.0;

Airport* airports[7];

Airplane** initialize(int num, int runway_num){
    airports[0] = CreateAirport("LAX", 0.5, 3, 0.3, runway_num, 34.05, -118.24);
    airports[1] = CreateAirport("ATL", 0.4, 4, 0.2, runway_num, 33.75, -84.39);
    airports[2] = CreateAirport("NY", 0.4, 3, 0.5, runway_num, 40.73, -73.94);
    airports[3] = CreateAirport("SFO", 0.3, 4, 0.3, runway_num, 37.73, -112.44);
    airports[4] = CreateAirport("Dallas", 0.4, 3, 0.2, runway_num, 32.73, -96.86);
    airports[5] = CreateAirport("Shanghai", 0.4, 8, 0.3, runway_num, 31.27, 121.52);
    airports[6] = CreateAirport("HK", 0.4, 4, 0.5, runway_num, 22.37, 114.12);
    FutureEventList = create_Queue();
    Airplane** airplanes = createAirplanes(num);
    return airplanes;
    
}

Airplane** createAirplanes(int num){
    Airplane** airplanes = (Airplane**)malloc(num * 6 * sizeof(Airplane*));
    int idx = 0;
    while (idx < num * 6) {
        char* name1 = (char*)malloc(15 * sizeof(char));
        char* name2 = (char*)malloc(15 * sizeof(char));
        char* name3 = (char*)malloc(15 * sizeof(char));
        char* name4 = (char*)malloc(15 * sizeof(char));
        char* name5 = (char*)malloc(15 * sizeof(char));
        char* name6 = (char*)malloc(15 * sizeof(char));
        char* label = (char*)malloc(5 * sizeof(char));
        
        sprintf(label, "%d", idx / 6 + 1);
        strcpy(name1, "A320_");
        strcpy(name2, "A380_");
        strcpy(name3, "Boeing747_");
        strcpy(name4, "Boeing737_");
        strcpy(name5, "F22_");
        strcpy(name6, "CRJ_");
        strcat(name1, label);
        strcat(name2, label);
        strcat(name3, label);
        strcat(name4, label);
        strcat(name5, label);
        strcat(name6, label);
        
        Airplane* A320 = createAirplane(name1, 8.7, 250);
        Airplane* A380 = createAirplane(name2, 8.5, 400);
        Airplane* Boeing747 = createAirplane(name3, 9.1, 320);
        Airplane* Boeing737 = createAirplane(name4, 8.8, 200);
        Airplane* F22 = createAirplane(name5, 18, 20);
        Airplane* CRJ = createAirplane(name6, 8.2, 285);
        
        airplanes[idx++] = A320;
        airplanes[idx++] = A380;
        airplanes[idx++] = Boeing747;
        airplanes[idx++] = Boeing737;
        airplanes[idx++] = F22;
        airplanes[idx++] = CRJ;
    }
    return airplanes;
}

void airplaneSchedule(Airplane** airplanes, int num, Airport** airports){
    for (int i = 0; i < num * 6; i++) {
        int r = rand() % 7;
        Airport* source = airports[r];
        Airport* destination = getDestination(source);
        airplane_setSource(airplanes[i], source);
        airplane_setDestination(airplanes[i], destination);
    }
}

void Schedule(AirportEvent* event){
    Insert_value(FutureEventList, event);
}

double getCurrentTime(){
    return Now;
}

Airport* getDestination(Airport* source){
    Airport* candidate;
    int idx = rand() % 7;
    candidate = airports[idx];
    while (strncmp(airport_getName(candidate), airport_getName(source), 8) == 0) {
        idx = rand() % 7;
        candidate = airports[idx];
    }
    return candidate;
}

void RunSim(int num_airplanes, double endTime, int runwayNum){
    Airplane** airplanes = initialize(num_airplanes, runwayNum);
    airplaneSchedule(airplanes, num_airplanes, airports);
    for (int i = 0; i < 6 * num_airplanes; i++) {
        AirportEvent* event = eventGenerator(airplanes[i], Now);
        Insert_value(FutureEventList, event);
    }
    while (Now <= endTime) {
        AirportEvent* event = Delete_Least(FutureEventList);
        Now = event_getTime(event);
        Airport* handler = event_getAirport(event);
        Airport_handle(handler, event);
        printQueue(FutureEventList);
    }
    
    
    
}

int main(int argc, char* argv[]){
    
    RunSim(30, 1000, 10);
    
    return 0;
}




