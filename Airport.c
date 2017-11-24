//
//  Airport.c
//  Assignment5
//
//  Created by Bravado on 11/23/17.
//  Copyright © 2017 Bravado. All rights reserved.
//

#include "Airport.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define PLANE_ARRIVES 0
#define PLANE_LANDED 1
#define PLANE_TAKEOFF 2
#define PLANE_DEPARTS 3

typedef struct Airport{
    char* m_airportName;
    int m_inTheAir;
    int m_onTheGround;
    
    int runway_num;
    bool* runwayFree;
    
    double m_runwayTimeToLand;
    double m_requiredTimeOnGround;
    double m_takeOffTime;
    double total_cycling_time;
    
    int passengersIn;
    int passengersOut;
    
    double coordinate_x;
    double coordinate_y;
    
    Queue* AirportEventQueue;
    
}Airport;

typedef struct AirportEvent{
    double timeStamp;
    int AirportEventType;
    Airplane* airplane;
    Airport* airport;
}AirportEvent;

int getFreeRunWay(Airport* airport);


Airport* CreateAirport(char* name, double runwayTimeToLand, double requiredTimeOnGround, double takeOffTime, int num_runway, double coordinate_X, double coordinate_Y){
    Airport* airport = (Airport*)malloc(sizeof(Airport));
    
    airport -> m_airportName = name;
    airport -> m_inTheAir =  0;
    airport -> m_onTheGround = 0;
    airport -> m_runwayTimeToLand = runwayTimeToLand;
    airport -> m_requiredTimeOnGround = requiredTimeOnGround;
    airport -> m_takeOffTime = takeOffTime;
    airport -> coordinate_x = coordinate_X;
    airport -> coordinate_y = coordinate_Y;
    airport -> passengersIn = 0;
    airport -> passengersOut = 0;
    airport -> total_cycling_time = 0;
    airport -> AirportEventQueue = create_Queue();
    
    airport -> runway_num = num_runway;
    airport -> runwayFree = (bool*)malloc(num_runway * sizeof(bool));
    for (int i = 0; i < num_runway; i++) {
        airport -> runwayFree[i] = true;
    }
    
    return airport;
}

double calculate_distance(Airport* airport1, Airport* airport2){
    double airport1_x = airport1 -> coordinate_x;
    double airport1_y = airport1 -> coordinate_y;
    double airport2_x = airport2 -> coordinate_x;
    double airport2_y = airport2 -> coordinate_y;
    double distance = sqrt(pow(airport1_x - airport2_x, 2) + pow(airport1_y - airport2_y, 2));
    char* name1 = airport_getName(airport1);
    char* name2 = airport_getName(airport2);
    int comp1_1 = strncmp(name1, "Shanghai", 10);
    int comp1_2 = strncmp(name1, "HK", 10);
    int comp2_1 = strncmp(name2, "Shanghai", 10);
    int comp2_2 = strncmp(name2, "HK", 10);
    
    if (((comp1_1 == 0 || comp1_2 == 0) && (comp2_1 != 0 || comp2_2 != 0))
        || ((comp2_1 == 0 || comp2_2 == 0) && (comp1_1 != 0 || comp1_2 != 0))){
        distance = distance / 2;
    }
    return distance;
}

char* airport_getName(Airport* airport){
    return airport -> m_airportName;
}

double event_getTime(AirportEvent* event){
    return event -> timeStamp;
}

void Airport_handle(Airport* m_airport, AirportEvent* m_event){
    Airplane* m_airplane = m_event -> airplane;
    int eventType = m_event -> AirportEventType;
    int runway_nov = -1;
    switch (eventType) {
        case PLANE_ARRIVES:
            m_airport -> m_inTheAir++;
            printf("%.2f : airplane %s arrived at %s\n", m_event -> timeStamp, airplane_getName(m_airplane), airport_getName(m_airport));
            runway_nov = getFreeRunWay(m_airport);
            
            if (runway_nov >= 0) {
                m_airport -> runwayFree[runway_nov] = false;
                airplane_setRunwayOccupied(m_airplane, runway_nov);
                m_event -> timeStamp = getCurrentTime() + m_airport -> m_runwayTimeToLand;
                m_event -> AirportEventType = PLANE_LANDED;
                Schedule(m_event);
            }else{
                Queue* eventQueue = m_airport -> AirportEventQueue;
                Insert_value(eventQueue, m_event);
            }
            break;
        case PLANE_LANDED:
            m_airport -> m_inTheAir--;
            runway_nov = airplane_getRunwayOccupied(m_airplane);
            m_airport -> passengersIn += airplane_getPassengerNum(m_airplane);
            
            printf("%.2f : airplane %s landed at %s\n", m_event -> timeStamp, airplane_getName(m_airplane), airport_getName(m_airport));
            
            m_event -> timeStamp = getCurrentTime() + m_airport -> m_requiredTimeOnGround;
            m_event -> AirportEventType = PLANE_TAKEOFF;
            Schedule(m_event);
            
            if (!isEmpty(m_airport -> AirportEventQueue)) {
                AirportEvent* ae = Delete_Least(m_airport -> AirportEventQueue);
                int ae_EventType = ae -> AirportEventType;
                Airplane* ap = ae -> airplane;
                airplane_setRunwayOccupied(ap, runway_nov);
                if (ae_EventType == PLANE_ARRIVES) {
                    m_airport -> total_cycling_time += getCurrentTime() - ae -> timeStamp;
                    ae -> timeStamp = getCurrentTime() + m_airport -> m_runwayTimeToLand;
                    ae -> AirportEventType = PLANE_LANDED;
                    Schedule(ae);
                }else{
                    ae -> timeStamp = getCurrentTime() + m_airport -> m_takeOffTime;
                    ae -> AirportEventType = PLANE_DEPARTS;
                    Schedule(ae);
                }
            }else{
                m_airport -> runwayFree[runway_nov] = true;
            }
            break;
            
        case PLANE_TAKEOFF:
            m_airport -> m_onTheGround++;
            airplane_setPassenger(m_airplane);
            runway_nov = getFreeRunWay(m_airport);
            printf("%.2f : airplane %s takeoff at %s\n", m_event -> timeStamp, airplane_getName(m_airplane), airport_getName(m_airport));
            if (runway_nov >= 0) {
                m_airport -> runwayFree[runway_nov] = false;
                m_event -> timeStamp = getCurrentTime() + m_airport -> m_takeOffTime;
                m_event -> AirportEventType = PLANE_DEPARTS;
                airplane_setRunwayOccupied(m_airplane, runway_nov);
                Schedule(m_event);
            }else{
                Queue* eventQueue = m_airport -> AirportEventQueue;
                Insert_value(eventQueue, m_event);
            }
            break;
            
        case PLANE_DEPARTS:
            m_airport -> m_onTheGround--;
            m_airport -> passengersOut += airplane_getPassengerNum(m_airplane);
           
            runway_nov = airplane_getRunwayOccupied(m_airplane);
            
            Airport* destination = getDestination(m_airport);
            double speed = airplane_getSpeed(m_airplane);
            double distance = calculate_distance(m_airport, destination);
            double flightTime = distance / speed;
            printf("%.2f: airplane %s departs from %s to %s\n", m_event -> timeStamp, airplane_getName(m_airplane), airport_getName(m_airport), airport_getName(destination));
            airplane_setDestination(m_airplane, destination);
            airplane_setSource(m_airplane, m_airport);
            m_event -> timeStamp = getCurrentTime() + flightTime;
            m_event -> AirportEventType = PLANE_ARRIVES;
            m_event -> airport = destination;
            Schedule(m_event);
            
            if (!isEmpty(m_airport -> AirportEventQueue)) {
                AirportEvent* ae = Delete_Least(m_airport -> AirportEventQueue);
                Airplane* ap = ae -> airplane;
                airplane_setRunwayOccupied(ap, runway_nov);
                
                int ae_EventType = ae -> AirportEventType;
                if (ae_EventType == PLANE_ARRIVES) {
                    m_airport -> total_cycling_time += getCurrentTime() - ae -> timeStamp;
                    ae -> timeStamp = getCurrentTime() + m_airport -> m_runwayTimeToLand;
                    ae -> AirportEventType = PLANE_LANDED;
                    Schedule(ae);
                }else{
                    ae -> timeStamp = getCurrentTime() + m_airport -> m_takeOffTime;
                    ae -> AirportEventType = PLANE_DEPARTS;
                    Schedule(ae);
                }
            }else{
                m_airport -> runwayFree[runway_nov] = true;
            }
            break;
        default:
            break;
    }
}


int getFreeRunWay(Airport* airport){
    int num_runway = airport -> runway_num;
    bool* runWay = airport -> runwayFree;
    for (int i = 0; i < num_runway; i++) {
        if (runWay[i]) return i;
    }
    return -1;
}

AirportEvent* eventGenerator(Airplane* m_airplane, double ts){
    AirportEvent* event = (AirportEvent*)malloc(sizeof(AirportEvent));
    event -> airplane = m_airplane;
    event -> timeStamp = ts;
    event -> AirportEventType = PLANE_ARRIVES;
    event -> airport = airplane_getDestination(m_airplane);
    return event;
}

Airport* event_getAirport(AirportEvent* event){
    return event -> airport;
}

int event_getType(AirportEvent* event){
    return event -> AirportEventType;
}

Airplane* event_getAirplane(AirportEvent* event){
    return event -> airplane;
}
