//
//  PriorityQueue.h
//  Assignment5
//
//  Created by Bravado on 11/23/17.
//  Copyright © 2017 Bravado. All rights reserved.
//


#ifndef PriorityQueue_h
#define PriorityQueue_h

#include "Airport.h"
#include "publicInterface.h"

//this function is used to create a priority queue
Queue* create_Queue();

//insert the event into the priority queue;
/*
 * param:
 * queue, priorityqueue;
 * event, the airportEvent which includes the airplane, airport that will take care of this airplane timestamp and the runway label used to mark the runway occupied.
 */
void Insert_value(Queue* queue, AirportEvent* event);

//function used to remove the airportEvent which has the least timestamp.
/*
 * param:
 * queue, priority Queue used to poll the element.
 */

AirportEvent* Delete_Least(Queue* queue);

//function used to judge the queue is empty or not.
bool isEmpty(Queue* queue);

//function used to debug.
void printQueue(Queue* queue);

#endif



