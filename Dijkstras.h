#ifndef DIJKSTRAS_H
#define DIJKSTRAS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include "graph_generation.h"


bool checkFringes(int* status, int V);

int maxFringe(int* bw,int* status,int V);

int minfunction(int a, int b);
void Dijkstras (Graph* graph,int s, int t);

#endif