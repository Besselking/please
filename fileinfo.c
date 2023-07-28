#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileinfo.h"

#define BUFFER_SIZE 1024
#define TEMP_FILENAME "temp.txt"

struct fileinfos fileinfos_create(void)
{
	struct fileinfos infos;
	infos.infos = NULL;
	infos.count = 0;
	return infos;
}

void fileinfos_add_line(struct fileinfos *infos, char *filename, size_t line)
{
	struct fileinfo *info = fileinfos_find_file(infos, filename);
	fileinfo_add_line(info, line);
}

struct fileinfo *fileinfos_find_file(struct fileinfos *infos, char *filename)
{
	struct fileinfo *infolist = infos->infos;
	for (size_t i = 0; i < infos->count; i++)
	{
		if (strcmp(infolist[i].filename, filename) == 0)
		{
			return &(infolist[i]);
		}
	}
	return fileinfos_add_fileinfo(infos, filename);
}

struct fileinfo *fileinfos_add_fileinfo(struct fileinfos *infos, char *filename)
{
	struct fileinfo *new_infos = realloc(infos->infos, sizeof(struct fileinfo) * (infos->count + 1));
	if (new_infos == NULL)
	{
		free(infos->infos);
	}
	infos->infos = new_infos;
	struct fileinfo *new_info = &infos->infos[infos->count];
	char *name = malloc(sizeof(*name) * strlen(filename));
	new_info->filename = strcpy(name, filename);
	new_info->lines = NULL;
	new_info->count = 0;
	infos->count += 1;
	return new_info;
}

void fileinfo_add_line(struct fileinfo *info, size_t line)
{
	size_t *lines = realloc(info->lines, sizeof(line) * (info->count + 1));
	if (lines == NULL)
	{
		free(info->lines);
	}
	info->lines = lines;
	info->lines[info->count] = line;
	info->count += 1;
}

void fileinfo_delete_lines(struct fileinfo info)
{
	FILE *original = fopen(info.filename, "r");
	FILE *temp = fopen(TEMP_FILENAME, "w");
	
	char buffer[BUFFER_SIZE];
	size_t current_line = 1;
	while (fgets(buffer, BUFFER_SIZE, original) != NULL)
	{
		bool found = false;
		for (size_t i = 0; i < info.count; i++)
		{
			if (info.lines[i] == current_line)
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			fputs(buffer, temp);
		}
		current_line += 1;
	}

	fclose(temp);
	fclose(original);
	rename(TEMP_FILENAME, info.filename);
	remove(TEMP_FILENAME);
}

