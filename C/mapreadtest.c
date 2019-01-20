#include "map.h"

 
int main(int argc , char *argv[])
{
	int success = init_map("map.txt");
	printf("%d", success);
}