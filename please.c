#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileinfo.h"

#define BUFFER_SIZE 1024

int main(void)
{
	for(;;)
	{
		FILE *make_output;

		make_output = popen("make 2>&1 >/dev/null", "r");
		if (!make_output)
		{
			fprintf(stderr, "could not run make.\n");
			exit(EXIT_FAILURE);
		}

		printf("Building...\n");

		char buffer[BUFFER_SIZE] = {0};
		struct fileinfos infos = fileinfos_create();
		while (fgets(buffer, BUFFER_SIZE - 1, make_output) != NULL)
		{
			char *found_error = strcasestr(buffer, "error:");
			if (found_error != NULL)
			{
				char error_buffer[BUFFER_SIZE] = "";
				strncpy(error_buffer, buffer, found_error - buffer);
				char *error_loc = &error_buffer[0];
				char *filename = strsep(&error_loc, ":");
				char *line = strsep(&error_loc, ":");

				size_t line_nr = strtoul(line, NULL, 10);
				fileinfos_add_line(&infos, filename, line_nr);
			}
		}

		int make_status = pclose(make_output);
		if (make_status != 0 && infos.count > 0)
		{
			for (size_t i = 0; i < infos.count; i++)
			{
				struct fileinfo info = infos.infos[i];
				printf("deleting %zu errors in %s\n", info.count, info.filename);
				fileinfo_delete_lines(info);
			}
		} 
		else
		{
			break;
		}
	}
	return EXIT_SUCCESS;
}

