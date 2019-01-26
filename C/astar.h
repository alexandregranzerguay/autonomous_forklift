#ifndef ASTAR_H_
#define ASTAR_H_

#include "map.h"

struct AStarNode {
	// f(x) = g(x) + h(x)
	int g; // g(x) = the distance between the current node and the start node
	int h; // h(x) = abs (current_cell.x – goal.x) + abs (current_cell.y – goal.y)
	struct Tile * tile;
	struct AStarNode * parent_tile_node;
	struct AStarNode * next;
};

struct AStarHead {
	struct AStarNode * head;
	int len;
};

struct Direction * path;

struct AStarNode * astar_pop_node(struct AStarHead * list, struct AStarNode * node);
int astar_push_node(struct AStarHead * list, struct AStarNode * node);
int free_list(struct AStarHead * list);
char get_direction(struct Coord curr, struct Coord prev);
int get_path_length(struct AStarNode * node);
int construct_path(struct AStarNode * node);

struct AStarNode * find_lowest_f(struct AStarHead * list);

struct AStarNode * find_node(struct AStarHead * list, struct Coord coords);

int visit_neighbour(struct AStarHead * open_list, struct AStarHead * closed_list, struct AStarNode * orig_node, struct Coord neighbour_coords, struct Coord end);
int visit_neighbours(struct AStarHead * open_list, struct AStarHead * closed_list, struct AStarNode * orig_node, struct Coord end);

int find_path(struct Coord start, struct Coord end);

#endif