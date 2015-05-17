/*
 * display.h
 *
 *  Created on: May 10, 2015
 *      Author: staslatgttt
 */

#ifndef VIEWS_GAME_JUMPPOINTSEARCH_DISPLAY_H_
#define VIEWS_GAME_JUMPPOINTSEARCH_DISPLAY_H_

#include "jps_grid.h"
#include "neighbors.h"
#include "heap.h"

/* Draws the grid / map */
void displayGrid(struct grid *gd);

/* Displays rudimentary information about a given node */
void displayNodeInfo(struct node *n);

/* Draws the grid / map with the computed path */
void displaySolution(struct grid *gd, struct neighbor_xy_list *path);

/* Lists information about all walkable nodes adjecent to a node */
void listNeighbors(struct neighbor_list *list);

/* Lists all entry in the open list ( contains eligible nodes for inspection ) */
void listOpenList(struct open_list *list);



#endif /* VIEWS_GAME_JUMPPOINTSEARCH_DISPLAY_H_ */
