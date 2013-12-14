#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <string.h>


#define MAXARGS 255

static short shell_exit = 0;

static int sapshell_main(int argc, char **argv)
{
    // "sapshell foo ..." is equivalent to "foo ..."
    if (argc > 1) {
        return main(argc - 1, argv + 1);
    } else {
        printf("sapshell!\n");
        return 0;
    }
}

static int exit_main(int argc, char **argv)
{
	printf("Bye bye!!\n");
	shell_exit = 1;
}

#define TOOL(name) int name##_main(int, char**);
#include "tools.h"
#undef TOOL

static struct 
{
    const char *name;
    int (*func)(int, char**);
} tools[] = {
    { "sapshell", sapshell_main },
    { "exit", exit_main },
#define TOOL(name) { #name, name##_main },
#include "tools.h"
#undef TOOL
    { 0, 0 },
};

void sapshell() {
	char* command = 0, *curr = 0, *t = 0;
	char* argv[MAXARGS] = {0};
	int i = 0, j = 0;
	do {
		command = readline("shapshell $");
		curr = t = 0;
		memset(argv, 0, MAXARGS);
		i = 0;
		if (!command)
			return;
		for (t = command; ;t = 0) {
			argv[i] = strtok_r(t, " ", &curr);
			if (argv[i] != NULL)
				if (!strlen(argv[i]))
					continue;
				else
					i++;
			else
				break;
		}
		for (j = 0; tools[j].name != 0; ++j)
		{
			if (!strcmp(argv[0], tools[j].name))
			{
				tools[j].func(i, argv);
				break;
			}
		}
		free(command);
	} while(command && (!shell_exit));
}

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		printf("Staring sapshell!!\n");
		sapshell();
	}
}

