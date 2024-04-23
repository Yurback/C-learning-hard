#include "dbg.h"
#include "rexpfile.h"

struct findinfo *filechecking(char *filename, int argc, char *argv[], int pos, enum typecheck tc)
{
	// Allocate memory for lines
	int *lines = NULL;
	if (tc)
		lines = calloc(argc - 1, sizeof(int));
	lines = calloc(1, sizeof(int));
	check_mem(lines);

	int hit = 0;
	char *buf = calloc(200, sizeof(char));
	check_mem(buf);
	FILE *fp = NULL;
	fp = fopen(filename, "r");
	check_mem(fp);

	struct findinfo *FI = malloc(sizeof(struct findinfo) + argc * sizeof(int));
	check_mem(FI);

	UPTO(argc - 1)
	{
		rewind(fp);
		if (pos == i + 1) // check position -o
			continue;
		int numberline = 0;

		while (fgets(buf, 200, fp) != NULL)
		{
			switch (tc)
			{
			case AND:
				if (strstr(buf, argv[i + 1]))
				{
					hit++;
					numberline++;
					*(lines + i) = numberline;

					if (argc - 1 == hit)
					{
						FI->file = filename;
						FI->lines = lines;

						fclose(fp);
						free(buf);
						return FI;
					}
					goto outer;
				}
				else
				{
					numberline++;
				}
				break;
			case OR:
				if (strstr(buf, argv[i + 1]))
				{
					*(lines + i) = numberline + 1;

					FI->file = filename;
					FI->lines = lines;
					return FI;
				}
				else
				{
					numberline++;
				}
				break;
			default:
				sentinel("We never should be here");
			}
		}
	outer:
	}

	// log_info("No matching detected.");

error:
	free(lines);
	fclose(fp);
	free(buf);
	return NULL;
}
