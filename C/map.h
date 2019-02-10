#ifndef MAP_H_
#define MAP_H_

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define MAP_X 6
#define MAP_Y 6
#define MAP_FILENAME "map.txt"
#define MAX_LOCATIONS 5
#define LOCATION_FILENAME "loc.txt"
#define MAX_PACKAGES 5
#define PACKAGE_FILENAME "pack.txt"
#define FLOOR_CHAR '.'
#define WALL_CHAR '#'

struct Coord {
	int x;
	int y;
};

struct Direction {
	char dir;
	int dist;
};

struct Location {
	char dir;
	struct Coord loc;
};

struct Tile {
	char symbol; // symbol to display for text representation of the tile
	int lid; // location id - if less than 0, not a valid location for packages
	int pid; // package id
	int passable; // Passable? IE. wall or floor?
	struct Coord coords;
};

struct Location location_list[MAX_LOCATIONS]; // IDs used as the array indices
struct Location package_list[MAX_PACKAGES]; // IDs used as the array indices
struct Tile map[MAP_Y][MAP_X];

int init_map(char const * const fileName);
int tok_location(char * str);
int init_locs();
int init_packs();

#endif
