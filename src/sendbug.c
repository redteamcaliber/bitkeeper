#include "system.h"
#include "sccs.h" 

extern char *bin, *editor;

sendbug_main(int ac,  char **av)
{
	char buf[MAXLINE];
	char bug[MAXPATH];
	FILE *f;

	platformInit();  
	sprintf(bug, "%s/bk_bug%d", TMP_PATH, getpid());
	f = fopen(bug, "wb");
	gethelp("bugtemplate", 0, f);
	fclose(f);
	sprintf(buf, "%s %s", editor, bug);
	system(buf);
	while (1) {
		printf("(s)end, (e)dit, (q)uit? ");
		unless (fgets(buf, sizeof(buf), stdin)) buf[0] = 'q';
		switch (buf[0]) {
		    case 's':
			mail("bitkeeper-bugs@bitmover.com", "BK Bug", bug);
			unlink(bug);
			printf("Your bug has been sent, thank you.\n");
			exit(0);
		    case 'e':
			sprintf(buf, "%s %s", editor, bug);
			system(buf);
			break;
		    case 'q':
			unlink(bug);
			printf("No bug sent.\n");
			exit(0);
		}
	}
}