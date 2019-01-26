#include <stdlib.h>
#include <math.h>
#include "astar.h"
#include <stdio.h>


// Use if popping a node by its pointer
struct AStarNode * astar_pop_node(struct AStarHead * list, struct AStarNode * node) {
	struct AStarNode * next_node;
	struct AStarNode * curr_node = list->head;
	if(curr_node == NULL) {
		return NULL;
	}
	
	next_node = curr_node->next;
	
	// if the node to pop is the first in the list
	if(curr_node == node) {
		list->head = curr_node->next;
		curr_node->next = NULL;
		list->len--;
		return curr_node;
	}
	
	// Traverse the list
	while(!(next_node == node || next_node == NULL)) {
		curr_node = next_node;
		next_node = curr_node->next;
	}

	// If the while loop was exited because the node was found
	if(next_node) {
		curr_node->next = next_node->next;
		next_node->next = NULL;
		list->len--;
	}
	
	return next_node;
}

/* Use if popping a node by its coordinates (TODO, possibly not needed)
struct AStarNode * astar_pop_coords(struct AStarHead list, struct Coord coords) {
	
} */

int astar_push_node(struct AStarHead * list, struct AStarNode * node) {
	node->next = list->head;
	list->head = node;
	list->len++;
	return 0;
}

int free_list(struct AStarHead * list) {
	struct AStarNode * curr_node;
	struct AStarNode * next_node;
	if(list == NULL) {
		return 0;
	}
	curr_node = list->head;
	if(curr_node == NULL) {
		return 0;
	}
	
	next_node = curr_node->next;
	
	// There is the tile pointer within the node object, but other than for tests,
	// it will always point to a static tile object within the map 2D array, and thus is not freed
	// (maybe add testing/debug flag to free if the flag is set?)
	while(next_node != NULL) {
		free(curr_node);
		curr_node = next_node;
		next_node = curr_node->next;
	}
	
	free(curr_node);
	list->head = NULL;
	list->len = 0;
	return 0;
}

struct AStarNode * find_lowest_f(struct AStarHead * list) {
	int min;
	struct AStarNode * curr_node;
	struct AStarNode * min_node;
	
	if(list->head == NULL)
		return NULL;
	
	curr_node = list->head;
	min = curr_node->g + curr_node->h;
	min_node = curr_node;
		
	curr_node = curr_node->next;
	
	while(curr_node != NULL) {
		if(curr_node->g + curr_node->h < min) {
			min = curr_node->g + curr_node->h;
			min_node = curr_node;
		}
		curr_node = curr_node->next;
	}
	return astar_pop_node(list, min_node);
}

struct AStarNode * find_node(struct AStarHead * list, struct Coord coords) {
	struct AStarNode * next_node;
	struct AStarNode * curr_node = list->head;
	if(curr_node == NULL) {
		return NULL;
	}
	
	next_node = curr_node->next;
	
	// check if the node is the first in the list
	if((curr_node->tile->coords.x == coords.x) && (curr_node->tile->coords.y == coords.y)) {
		return curr_node;
	}

	while(!( next_node == NULL || ((next_node->tile->coords.x == coords.x) && (next_node->tile->coords.y == coords.y)))) {
		curr_node = next_node;
		next_node = curr_node->next;
	}
	
	return next_node;
}

int visit_neighbour(struct AStarHead * open_list, struct AStarHead * closed_list, struct AStarNode * orig_node, struct Coord neighbour_coords, struct Coord end) {
	struct AStarNode * neighbour_node = NULL;
	// The neighbour's g score will be one higher than the node it came from
	int new_g_score = orig_node->g + 1;
	
	if(neighbour_node = find_node(closed_list, neighbour_coords)) {
		return 0;
	} else if(neighbour_node = find_node(open_list, neighbour_coords)) {
		if(new_g_score < neighbour_node->g) {
			neighbour_node->g = new_g_score;
			neighbour_node->parent_tile_node = orig_node;
		}
	} else {
		neighbour_node = (struct AStarNode *) malloc(sizeof(struct AStarNode));
		neighbour_node->tile = &(map[neighbour_coords.y][neighbour_coords.x]);
		neighbour_node->g = new_g_score;
		neighbour_node->h = abs(neighbour_node->tile->coords.x - end.x) + abs(neighbour_node->tile->coords.y - end.y);
		neighbour_node->parent_tile_node = orig_node;
		astar_push_node(open_list, neighbour_node);
	}
	return 0;
}

int visit_neighbours(struct AStarHead * open_list, struct AStarHead * closed_list, struct AStarNode * orig_node, struct Coord end) {
	struct Coord check_coords;
	struct Coord orig_node_coords = orig_node->tile->coords;
	
	/* For visiting neighbours, checks are made to ensure the neighbour is within the map coordinates
	(greater than or equal to zero and less than the dimensions of the map) and are passable (ie. not a wall)
	*/
	// visit neighbour at x - 1
	if(orig_node_coords.x - 1 >= 0 && map[orig_node_coords.y][orig_node_coords.x - 1].passable) {
		check_coords.x = orig_node_coords.x - 1;
		check_coords.y = orig_node_coords.y;
		visit_neighbour(open_list, closed_list, orig_node, check_coords, end);
	}
	// visit neighbour at y - 1
	if(orig_node->tile->coords.y - 1 >= 0 && map[orig_node->tile->coords.y - 1][orig_node->tile->coords.x].passable) {
		check_coords.x = orig_node_coords.x;
		check_coords.y = orig_node_coords.y - 1;
		visit_neighbour(open_list, closed_list, orig_node, check_coords, end);
	}
	// visit neighbour at x + 1
	if(orig_node->tile->coords.x + 1 < MAP_X && map[orig_node->tile->coords.y][orig_node->tile->coords.x + 1].passable) {
		check_coords.x = orig_node_coords.x + 1;
		check_coords.y = orig_node_coords.y;
		visit_neighbour(open_list, closed_list, orig_node, check_coords, end);
	}
	// visit neighbour at y + 1
	if(orig_node->tile->coords.y + 1 < MAP_Y && map[orig_node->tile->coords.y + 1][orig_node->tile->coords.x].passable) {
		check_coords.x = orig_node_coords.x;
		check_coords.y = orig_node_coords.y + 1;
		visit_neighbour(open_list, closed_list, orig_node, check_coords, end);
	}
	return 0;
}

char get_direction(struct Coord curr, struct Coord prev) {
	if(curr.x == prev.x + 1) {
		return 'e';
	} else if (curr.x == prev.x - 1) {
		return 'w';
	} else if (curr.y == prev.y + 1) {
		return 's';
	} else if (curr.y == prev.y - 1) {
		return 'n';
	} else {
		// this means the two coordinates are not neighbouring, so there is no valid direction between the two
		return 'x';
	}
}

int get_path_length(struct AStarNode * node) {
	// Start with an invalid direction
	char curr_dir;
	char next_dir;
	int len;
	
	if(node->parent_tile_node == NULL) {
		return 0;
	}
	
	curr_dir = get_direction(node->tile->coords, node->parent_tile_node->tile->coords);
	len = 1;
	
	while(node->parent_tile_node != NULL) {
		next_dir = get_direction(node->tile->coords, node->parent_tile_node->tile->coords);
		if(next_dir == 'x') {
			printf("Invalid direction\n");
			return -1;
		}
		// Since the direction struct has a direction and distance, each time the robot changes directions, one struct must be added
		if(next_dir != curr_dir) {
			curr_dir = next_dir;
			len++;
		}
		node = node->parent_tile_node;
	}
	return len;
}

/* Construct path first determines how much memory must be allocated by walking
through parent_tile_node pointers. Then it gets the first direction between the last node and its parent
and initializes the distance for that direction to 1. */
int construct_path(struct AStarNode * node) {
	int i, len;
	
	len = get_path_length(node);
	
	struct Direction curr_dir;
	
	char next_dir;
	if(len == -1) {
		return -1;
	}
	i = len - 1;
	path = (struct Direction *) malloc(len * sizeof(struct Direction));
	
	curr_dir.dir = get_direction(node->tile->coords, node->parent_tile_node->tile->coords);
	curr_dir.dist = 1;
	
	while(node->parent_tile_node != NULL && i >= 0) {
		next_dir = get_direction(node->tile->coords, node->parent_tile_node->tile->coords);
		if(next_dir == 'x') {
			printf("Invalid direction");
			return -1;
		}
		// Since the direction struct has a direction and distance, each time the robot changes directions, one struct must be added
		if(next_dir != curr_dir.dir) {
			// The current direction is done, so the direction and number of tiles will be added to the path array (in reverse order, as the node traversal begins from the end coordinate)
			path[i].dir = curr_dir.dir;
			path[i].dist = curr_dir.dist;
			curr_dir.dir = next_dir;
			curr_dir.dist = 0;
			i--;
		}
		curr_dir.dist++;
		node = node->parent_tile_node;
	}
	// Final direction must be added, as there will be no direction change
	path[0].dir = curr_dir.dir;
	path[0].dist = curr_dir.dist;

	return len;
}

int find_path(struct Coord start, struct Coord end) {
	struct AStarHead open_list;
	struct AStarHead closed_list;
	
	struct AStarNode * curr_node;
	struct AStarNode * found_node;
	struct AStarNode * last_node;
	
	struct Coord curr_node_coords;
	struct Coord check_coords;
	
	int path_len;
	
	// Create the initial node for the starting coordinates
	open_list.head = (struct AStarNode *) malloc(sizeof(struct AStarNode));
	open_list.len = 1;
	open_list.head->tile = &(map[start.y][start.x]);
	open_list.head->g = 0;
	open_list.head->h = abs(start.x - end.x) + abs(start.y - end.y);
	open_list.head->next = NULL;
	open_list.head->parent_tile_node = NULL;
	
	closed_list.head = NULL;
	closed_list.len = 0;
	
	while(open_list.head != NULL) {
		curr_node = find_lowest_f(&open_list);
		if((curr_node->tile->coords.x == end.x) && (curr_node->tile->coords.y == end.y)) {
			path_len = construct_path(curr_node);
			free_list(&open_list);
			free_list(&closed_list);
			return path_len;
		}
		
		visit_neighbours(&open_list, &closed_list, curr_node, end);
		
		// if(astar_push_node(&closed_list, curr_node))
		astar_push_node(&closed_list, curr_node);
	}
	
	// If the loop is exited, it means no valid path was found
	free_list(&open_list);
	free_list(&closed_list);
	return 0;
}