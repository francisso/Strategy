/*
 * neighbors.h
 *
 *  Created on: May 10, 2015
 *      Author: staslatgttt
 */

#ifndef VIEWS_GAME_JUMPPOINTSEARCH_NEIGHBORS_H_
#define VIEWS_GAME_JUMPPOINTSEARCH_NEIGHBORS_H_

#include "jps_grid.h"
#include <stdlib.h>

/*extern int malloc_count;*/

/* Circular Doubly Linked List that holds X & Y coordinates instead of full nodes */
struct neighbor_xy_list {
	struct neighbor_xy_list *left;
	struct neighbor_xy_list *right;
	int x;
	int y;
};

/* Create a new list */
struct neighbor_xy_list *neighbor_xy_new();

/* Clean list */
void neighbor_xy_clean(struct neighbor_xy_list *head);

/* Add to the list */
struct neighbor_xy_list *neighbor_xy_insert_right(struct neighbor_xy_list *list, int x, int y);

/* Find all neighbors adjecent to a node ( return X/Y coordinate list, rather than full nodes ) */
struct neighbor_xy_list *_findNeighbors(struct grid *gd, struct node *activeNode);

#endif /* VIEWS_GAME_JUMPPOINTSEARCH_NEIGHBORS_H_ */
