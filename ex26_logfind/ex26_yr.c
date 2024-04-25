#include "dbg.h"
#include "rexpfile.h"
#include <glob.h>

// typedef struct {
//      size_t   gl_pathc;    /* Count of paths matched so far  */
//      char   **gl_pathv;    /* List of matched pathnames.  */
//      size_t   gl_offs;     /* Slots to reserve in gl_pathv.  */
// } glob_t;

// void globfree(glob_t *pglob);

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	int pos = 0;
	int cnt = 0; // number of files with matching
	struct findinfo *ref = NULL;

	enum typecheck tc = AND;

	check(argc > 1, "It takes one or more arguments for searching [-o] for 'or'.");
	// Set OR | AND type
	UPTO(argc - 1)
	if (strstr(argv[i + 1], "-o"))
		tc = OR,
		pos = i + 1;
	check(argc != pos, "It takes one or more arguments for searching [-o] for 'or'.");

	// Try out all files in common directory
	glob_t *pgl = calloc(1, sizeof(glob_t));
	char strman[20] = "*";

	while (glob(strman, GLOB_DOOFFS, NULL, pgl) == 0)
	{
		// Dynamic allocate memory for the array of struct FI
		struct findinfo **arrfinf = calloc(pgl->gl_pathc, sizeof(struct findinfo *));
		check_mem(arrfinf);
		// Open FILE and read rows in LOOP

		UPTO(pgl->gl_pathc)
		{
			ref = filechecking(pgl->gl_pathv[i], argc, argv, pos, tc);
			if (ref)
			{
				arrfinf[i] = ref;
				cnt++;
			}
		}
		// PRINT ALL MATCHES IN THE FILES

		UPTO(pgl->gl_pathc)
		{
			if (arrfinf[i])
			{
				printf("FILE: %s LINES: ", arrfinf[i]->file);
				struct findinfo *ref = arrfinf[i];
				UPTO(argc - 1)
				{
					if (ref->lines + i && *(ref->lines + i) != 0)
						printf("%d ", *(ref->lines + i));
				}
				printf("\n");
			}
		}

		// Clean all aloocation
		UPTO(pgl->gl_pathc)
		free(arrfinf[i]);
		free(arrfinf);
		
		// Next iteration for nested folders
		strcat(strman, "/*");
	}
	printf("In total %d:\n", cnt);
	// int err = glob("*", GLOB_DOOFFS, NULL, pgl);
	// check(err == 0, "Failed to list files.");

	globfree(pgl);
	return 0;

error:
	// if (arrfinf)
	// 	free(arrfinf);
	if (pgl)
		globfree(pgl);
	if (fp)
		fclose(fp);

	return 1;
}
