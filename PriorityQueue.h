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

Queue* create_Queue();

void Insert_value(Queue* queue, AirportEvent* event);

AirportEvent* Delete_Least(Queue* queue);

bool isEmpty(Queue* queue);

void printQueue(Queue* queue);

#endif



