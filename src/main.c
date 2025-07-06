#include <stdio.h>
#include <unistd.h>
#include "screen.h"


int main() {
	while (1) {
		printf("\nTetris. Coming soon...\n");
		fflush(stdout);
		sleep(1);
		cls();
		printf("\n");
		sleep(1);
	}
	
	return 0;
}

