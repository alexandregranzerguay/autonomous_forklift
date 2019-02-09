#include "map.h"

int init_map(char const* const fileName) {
	int i, j;
	char line[MAP_X + 10]; // +10 to compensate if the line is a little longer
    FILE* file;
	
	if(!(file = fopen(fileName, "r"))) {
		printf("Could not read map.txt");
		return 1;
	}
	
	char * buffer[MAP_Y]; // Have an intermediate buffer instead of reading directly into map so that map is not partially overwritten if there's a problem with the text file
	for (i = 0; i < MAP_Y; i++) {
		buffer[i] = (char *)malloc((MAP_X + 1) * sizeof(char)); // +1 for /0
	}

	i = 0;
    while (fgets(line, sizeof(line), file)) {
		if(i >= MAP_Y) {
			printf("Incorrect number of lines in text file");
			fclose(file);
			return 1;
		}
		if(strlen(line) != MAP_X + 2) { // length of a properly sized line. +1 for /n, +1 for /0
			printf("Incorrect length in line: %d\n", i + 1);
			fclose(file);
			return 1;
		}
		if (line[0] == '\n') {
			printf("Line %d starts with a newline character", i + 1);
			fclose(file);
			return 1;
		}
		for(j = 0; j < MAP_X; j++) {
			if(line[j] != FLOOR_CHAR && line[j] != WALL_CHAR) {
				printf("Invalid character in line %d. Acceptable characers are: %c and %c", i+1, FLOOR_CHAR, WALL_CHAR);
				fclose(file);
				return 1;
			}
			buffer[i][j] = line[j];
		}
		buffer[i][j] = '\0';
		
		i++;
    }

	if (i < MAP_Y) {
		printf("Too few lines: %d\n", i + 1);
		fclose(file);
		return 1;
	}
	
	fclose(file);
	
	// to print out the buffer
	/*for(i = 0; i < MAP_Y; i++) {
		printf("%s\n", buffer[i]);
	} */
	
	for(i = 0; i < MAP_Y; i++) {
		for(j = 0; j < MAP_X; j++) {
			if(buffer[i][j] == WALL_CHAR) {
				map[i][j].symbol = WALL_CHAR;
				map[i][j].passable = 0;
			} else if(buffer[i][j] == FLOOR_CHAR) {
				map[i][j].symbol = FLOOR_CHAR;
				map[i][j].passable = 1;
			} else {
				// should not get here, characters are checked when reading from file
				printf("Invalid character in buffer");
				return 1;
			}
			map[i][j].coords.y = i;
			map[i][j].coords.x = j;
			map[i][j].lid = -1; // When reloading the map, reset lid and pid to -1 (the default invalid id)
			map[i][j].pid = -1;
		}
	}
	
	for (i = 0; i < MAP_Y; i++) {
		free(buffer[i]);
	}

    return 0;
}

int tokenize_locs_packs(char * str, unsigned int strsize, int * arr) {
	
}

int init_locs() {
	int i;
	for(i = 0; i < MAX_LOCATIONS; i++) {
		location_list[i].dir = 'x';
		location_list[i].loc.x = -1;
		location_list[i].loc.y = -1;
	}
	location_list[0].dir = 'w';
	location_list[0].loc.x = 1;
	location_list[0].loc.y = 2;
	
	location_list[1].dir = 'e';
	location_list[1].loc.x = 4;
	location_list[1].loc.y = 4;
}

int init_packs() {
	int i;
	for(i = 0; i < MAX_PACKAGES; i++) {
		package_list[i].dir = 'x';
		package_list[i].loc.x = -1;
		package_list[i].loc.y = -1;
	}
	package_list[0].dir = 'w';
	package_list[0].loc.x = 1;
	package_list[0].loc.y = 2;
}
