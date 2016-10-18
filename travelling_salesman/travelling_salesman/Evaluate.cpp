/* *************************************************************
* Course: CSS 534 assignment 1
* Author: Mukambika Hegde
* Date: 10/16/2016
* *************************************************************/


#include <iostream>
#include <string.h>
#include <math.h>  // sqrt, pow
#include "Trip.h"
#include <stdlib.h>
#include <time.h>
#include <map>

#ifndef EVAL_H
#define EVAL_H

using namespace std;

void qsort(void *base, size_t nmemb, size_t size,
    int(*compar)(const void *, const void *));


int compare_trips(const void *, const void *);
float calculate_distance(char, char, int[CITIES][2]);
void evaluate(Trip trip[CHROMOSOMES], int coordinates[CITIES][2]);
void crossover(Trip parents[TOP_X], Trip offsprings[TOP_X], int coordinates[CITIES][2]);
void mutate(Trip offsprings[TOP_X]);

int compare_trips(const void *t1, const void *t2) {
    return (int)(*(Trip *)t1).fitness - (*(Trip *)t2).fitness;
}

float calculate_distance(char s, char d, int coordinates[CITIES][2]) {
    int indexs = (s >= 'A') ? s - 'A' : s - '0' + 26;
    int indexd = (d >= 'A') ? d - 'A' : d - '0' + 26;

    int x1 = coordinates[indexs][0] - coordinates[indexd][0];
    int y1 = coordinates[indexs][1] - coordinates[indexd][1];

    double x1_d = pow(x1, 2);
    double y1_d = pow(y1, 2);
    return sqrt(x1_d + y1_d);
}

void evaluate(Trip trip[CHROMOSOMES], int coordinates[CITIES][2]) {
    // evaluate shortest trip for each of 50000 trips

    for (int i = 0; i<CHROMOSOMES; i++) {
        float trip_distance = 0;
        for (int j = 0; j< CITIES - 1; j++) {
            char source = trip[i].itinerary[j];
            char destination = trip[i].itinerary[j + 1];
            trip_distance += calculate_distance(source, destination, coordinates);
        }
        trip[i].fitness = trip_distance;
    }
    // update the shortest trip among the 50000 trips using quick sort
    qsort(trip, CHROMOSOMES, sizeof(Trip), compare_trips);
}

void crossover(Trip parents[TOP_X], Trip offsprings[TOP_X], int coordinates[CITIES][2]) {

    std::map<char, char> compli_cities = {
        { 'A', '9' },
        { 'B', '8' },
        { 'C', '7' },
        { 'D', '6' },
        { 'E', '5' },
        { 'F', '4' },
        { 'G', '3' },
        { 'H', '2' },
        { 'I', '1' },
        { 'J', '0' },
        { 'K', 'Z' },
        { 'L', 'Y' },
        { 'M', 'X' },
        { 'N', 'W' },
        { 'O', 'V' },
        { 'P', 'U' },
        { 'Q', 'T' },
        { 'R', 'S' },
        { 'S', 'R' },
        { 'T', 'Q' },
        { 'U', 'P' },
        { 'V', 'O' },
        { 'W', 'N' },
        { 'X', 'M' },
        { 'Y', 'L' },
        { 'Z', 'K' },
        { '0', 'J' },
        { '1', 'I' },
        { '2', 'H' },
        { '3', 'G' },
        { '4', 'F' },
        { '5', 'E' },
        { '6', 'D' },
        { '7', 'C' },
        { '8', 'B' },
        { '9', 'A' },
    };

    for (int i = 0; i < TOP_X - 1; i += 2) {
        offsprings[i].itinerary[0] = parents[i].itinerary[0];
        offsprings[i + 1].itinerary[0] = compli_cities[offsprings[i].itinerary[0]];
        for (int j = 1; j < CITIES; j++) {
            // select the source city of parent[i]
            char source_city = parents[i].itinerary[j - 1];
            // select the destination city of source city in parent[i]
            char destination1 = parents[i].itinerary[j];

            // Get the destination city of source_city in parent[i+1]
            int index = 0;
            for (int k = 0; k < CITIES; k++) {
                if (parents[i + 1].itinerary[k] == source_city) {
                    index = k;
                    break;
                }
            }

            // check if source_city is the last city in parent[i+1]
            if (index == CITIES - 1) {
                index = 0;
            }
            else {
                index = index + 1;
            }

            char destination2 = parents[i + 1].itinerary[index];

            int d1_flag = 0, d2_flag = 0;
            char cities_visited[CITIES];
            for (int k = 0; k < CITIES; k++) {
                cities_visited[k] = 0;
            }

            // check if destination1 or destination2 has already occurred in child[i]'s trip
            for (int l = 0; l < j; l++) {
                if (offsprings[i].itinerary[l] == destination1 && d1_flag == 0) {
                    d1_flag = 1;
                }
                if (offsprings[i].itinerary[l] == destination2 && d2_flag == 0) {
                    d2_flag = true;
                }

                // Keep a track of all the cities that have occurred in offsprings trip
                int index = (offsprings[i].itinerary[l] >= 'A') ? offsprings[i].itinerary[l] - 'A' : offsprings[i].itinerary[l] - '0' + 26;
                cities_visited[index] = 1;

            }

            // if destination1 has already occured in trip and destination2 has not occurred
            if (d1_flag && !d2_flag) {
                offsprings[i].itinerary[j] = destination2;
            }
            // check if destination2 has already occurred in trip and destination1 has not occurred
            if (d2_flag && !d1_flag) {
                offsprings[i].itinerary[j] = destination1;
            }
            // both destination1 and destination2 are yet to be visited
            if (!(d1_flag || d2_flag)) {
                if (destination1 == destination2) {
                    offsprings[i].itinerary[j] = destination1;
                }
                else {
                    // calculate the distance
                    double distance_1 = calculate_distance(source_city, destination1, coordinates);
                    double distance_2 = calculate_distance(source_city, destination2, coordinates);
                    // choose the closer city from source_city to extend the child[i]'s trip
                    if (distance_1 < distance_2) {
                        offsprings[i].itinerary[j] = destination1;
                    }
                    else {
                        offsprings[i].itinerary[j] = destination2;
                    }
                }
            }
            else if (d1_flag && d2_flag) { // randomly select a non-selected city

                                           /*int rand_num = 0;
                                           do {
                                           rand_num = rand() % CITIES;
                                           } while (cities_visited[rand_num]);
                                           if (rand_num < 26) {
                                           offsprings[i].itinerary[j] = 'A' + rand_num;
                                           }
                                           else {
                                           offsprings[i].itinerary[j] = rand_num - 26 + '0';
                                           if (offsprings[i].itinerary[j] == ']' || offsprings[i].itinerary[j] == '[') {
                                           cout << "error\n";
                                           }
                                           }*/
                int rand_index;
                for (rand_index = 0; rand_index < CITIES; rand_index++) {
                    if (cities_visited[rand_index] == 0) break;
                }
                if (rand_index < 26) {
                    offsprings[i].itinerary[j] = 'A' + rand_index;
                }
                else {
                    offsprings[i].itinerary[j] = rand_index - 26 + '0';
                    if (offsprings[i].itinerary[j] == ']' || offsprings[i].itinerary[j] == '[') {
                        cout << "error\n";
                    }
                }
            }

            // generate child[i+1]'s trip as a complement of child[i]
            offsprings[i + 1].itinerary[j] = compli_cities[offsprings[i].itinerary[j]];
        }
        offsprings[i].itinerary[CITIES] = offsprings[i + 1].itinerary[CITIES] = '\0';
    }
}

/*
* Randomly chooses two distinct cities in each trip with a given
* probability, and swaps them
* @param: TOP_X trips
*/
void mutate(Trip offsprings[TOP_X]) {
    // for each of the trip in TOP_X trips
    for (int i = 0; i < TOP_X; i++) {
        srand(time(NULL));
        // choose 2 random cities
        int r1 = 0, r2 = 0;
        do {
            r1 = rand() % CITIES;
            r2 = rand() % CITIES;
        } while (r1 == r2);

        // swap the two distinct cities
        char c = offsprings[i].itinerary[r1];
        offsprings[i].itinerary[r1] = offsprings[i].itinerary[r2];
        offsprings[i].itinerary[r2] = c;
    }
}

#endif
