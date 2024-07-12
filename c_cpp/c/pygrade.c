#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *list = fopen("outdated.log", "r");
  
  if (list == NULL) {
	fputs("outdated.log not found\n"
		"Creating file...\n", stderr);
	system("pip list --outdated > outdated.log");
	list = fopen("outdated.log", "r");
	fputs("Opening outdated.log...", stderr);

	if (list == NULL) {
	  fputs("Unable to open list of outdated files\n", stderr);
	  return 1;
	}
  }

  char package[100], linenum = 0;

  
  while (!feof(list)) {
	if (linenum++ < 2) { /*first 2 lines are for table head*/
	  fscanf(list, "%*[^\n]\n");
	  continue;
	}

	fscanf(list, "%99s%*[^\n]\n", package);
	fprintf(stderr, "package %d: %s\n", linenum - 2, package);
	
	char command[121]; /*"pip install --upgrade" == 21 chars*/

	sprintf(command, "pip install --upgrade %s", package);
	system(command);
  }
  
  fclose(list);

  remove("outdated.log");
  return 0;
}

