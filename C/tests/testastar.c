#include "unity/unity.h"
#include <stdlib.h>
#include <stdio.h>
#include "../astar.h"
#include "../map.h"

struct Coord start_coord;
struct Coord end_coord;
struct Coord test_coord0;
struct Coord test_coord1;
struct AStarHead list1;
struct AStarNode * a1;
struct AStarNode * b1;
struct AStarNode * c1;
struct AStarNode * d1;
struct AStarNode * start_node;

struct AStarHead open_list;
struct AStarHead closed_list;

struct Direction * path;

struct Direction test_dir;

int path_len;

void setUp() {
	start_coord.x = 0;
	start_coord.y = 0;
	end_coord.x = 10;
	end_coord.y = 10;
	
	a1 = (struct AStarNode *) malloc(sizeof(struct AStarNode));
	a1->tile = (struct Tile *) malloc(sizeof(struct Tile));
	a1->tile->coords = start_coord;
	a1->tile->passable = 1;
	a1->g = 0;
	a1->h = abs(a1->tile->coords.x - end_coord.x) + abs(a1->tile->coords.y - end_coord.y);
	a1->next = NULL;
	a1->parent_tile_node = NULL;
	
	b1 = (struct AStarNode *) malloc(sizeof(struct AStarNode));
	b1->tile = (struct Tile *) malloc(sizeof(struct Tile));
	b1->tile->coords.x = 1;
	b1->tile->coords.y = 1;
	b1->tile->passable = 1;
	b1->g = 0;
	b1->h = abs(b1->tile->coords.x - end_coord.x) + abs(b1->tile->coords.y - end_coord.y);
	b1->next = NULL;
	b1->parent_tile_node = NULL;
	
	c1 = (struct AStarNode *) malloc(sizeof(struct AStarNode));
	c1->tile = (struct Tile *) malloc(sizeof(struct Tile));
	c1->tile->coords.x = 2;
	c1->tile->coords.y = 2;
	c1->tile->passable = 1;
	c1->g = 0;
	c1->h = abs(c1->tile->coords.x - end_coord.x) + abs(c1->tile->coords.y - end_coord.y);
	c1->next = NULL;
	c1->parent_tile_node = NULL;
	
	d1 = (struct AStarNode *) malloc(sizeof(struct AStarNode));
	d1->tile = (struct Tile *) malloc(sizeof(struct Tile));
	d1->tile->coords.x = 3;
	d1->tile->coords.y = 3;
	d1->tile->passable = 1;
	d1->g = 0;
	d1->h = abs(d1->tile->coords.x - end_coord.x) + abs(d1->tile->coords.y - end_coord.y);
	d1->next = NULL;
	d1->parent_tile_node = NULL;
	
	list1.head = a1;
	list1.head->next = b1;
	list1.head->next->next = c1;
	list1.len = 3;
	
	open_list.head = NULL;
	open_list.len = 0;
	closed_list.head = NULL;
	closed_list.len = 0;
}

void tearDown(void) {
    // clean stuff up here
	free(a1->tile);
	free(b1->tile);
	free(c1->tile);
	free(d1->tile);
	free(a1);
	free(b1);
	free(c1);
	free(d1);
}

void test_utilities() {
	TEST_ASSERT_TRUE(astar_pop_node(&list1, b1) == b1);
	TEST_ASSERT_EQUAL(2, list1.len);
	TEST_ASSERT_TRUE(astar_pop_node(&list1, b1) == NULL);
	
	// On success, function returns 0, so we want a false evaluation
	TEST_ASSERT_FALSE(astar_push_node(&list1, d1));
	TEST_ASSERT_EQUAL(3, list1.len);
	TEST_ASSERT_TRUE(astar_pop_node(&list1, d1) == d1);
	
	astar_push_node(&list1, b1);
	astar_push_node(&list1, d1);
	
	TEST_ASSERT_TRUE(find_lowest_f(&list1) == d1);
	
	test_coord0.x = 1;
	test_coord0.y = 1;
	TEST_ASSERT_TRUE(find_node(&list1, test_coord0) == b1);
	
	test_coord0.x = 3;
	test_coord0.y = 3;
	TEST_ASSERT_TRUE(find_node(&list1, test_coord0) == NULL);
	
	// Test on empty list
	TEST_ASSERT_TRUE(find_node(&open_list, test_coord0) == NULL)
	
	// Test correct direction returning
	test_coord0.x = 5;
	test_coord0.y = 5;
	test_coord1.x = 6;
	test_coord1.y = 5;
	TEST_ASSERT_EQUAL('e', get_direction(test_coord1, test_coord0));
	
	test_coord1.x = 5;
	test_coord1.y = 6;
	TEST_ASSERT_EQUAL('s', get_direction(test_coord1, test_coord0));
	
	test_coord1.x = 4;
	test_coord1.y = 5;
	TEST_ASSERT_EQUAL('w', get_direction(test_coord1, test_coord0));
	
	test_coord1.x = 5;
	test_coord1.y = 4;
	TEST_ASSERT_EQUAL('n', get_direction(test_coord1, test_coord0));
}

void test_pathfinding() {
	int i;
	int path_len;
	TEST_ASSERT_FALSE(init_map("maptest.txt"));
	// FALSE FOR NOW, CHANGE TO TRUE AFTER PATH CONSTRUCTION
	end_coord.x = 10;
	end_coord.y = 10;
	start_node = (struct AStarNode *) malloc(sizeof(struct AStarNode));
	start_node->tile = &map[1][1];
	start_node->g = 0;
	start_node->h = abs(start_node->tile->coords.x - end_coord.x) + abs(start_node->tile->coords.y - end_coord.y);
	start_node->next = NULL;
	start_node->parent_tile_node = NULL;
	
	astar_push_node(&open_list, start_node);
	
	TEST_ASSERT_EQUAL(1, open_list.len);
	
	// This is start_node's coords, but 1 added to the y coordinate
	test_coord0.x = 1;
	test_coord0.y = 2;
	
	TEST_ASSERT_FALSE(visit_neighbour(&open_list, &closed_list, start_node, test_coord0, end_coord));
	// The neighbour should have had a node created and added to the open_list
	TEST_ASSERT_EQUAL(2, open_list.len);
	TEST_ASSERT_TRUE(find_node(&open_list, test_coord0));
	test_coord0.x = 1;
	test_coord0.y = 1;
	TEST_ASSERT_TRUE(find_node(&open_list, test_coord0));
	TEST_ASSERT_FALSE(free_list(&open_list));
	TEST_ASSERT_EQUAL(0, open_list.len);
	
	start_coord.x = 7;
	start_coord.y = 4;
	end_coord.x = 13;
	end_coord.y = 18;
	path_len = find_path(start_coord, end_coord);
	TEST_ASSERT_EQUAL(2, path_len);
	test_dir.dir = 's';
	test_dir.dist = 14;
	TEST_ASSERT_EQUAL(test_dir.dir, path[0].dir);
	TEST_ASSERT_EQUAL(test_dir.dist, path[0].dist);
	
	test_dir.dir = 'e';
	test_dir.dist = 7;
	TEST_ASSERT_EQUAL(test_dir.dir, path[1].dir);
	TEST_ASSERT_EQUAL(test_dir.dist, path[1].dist);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_utilities);
	RUN_TEST(test_pathfinding);
	
    return UNITY_END();
}