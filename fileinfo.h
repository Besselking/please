#ifndef FILEINFO_H
#define FILEINFO_H

#include <stddef.h>

struct fileinfo
{
	char *filename;
	size_t count;
	size_t *lines;
};

struct fileinfos
{
	size_t count;
	struct fileinfo *infos;
};

struct fileinfos fileinfos_create(void);
void fileinfos_add_line(struct fileinfos *infos, char *filename, size_t line);
struct fileinfo *fileinfos_find_file(struct fileinfos *infos, char *filename);
struct fileinfo *fileinfos_add_fileinfo(struct fileinfos *infos, char *filename);

void fileinfo_add_line(struct fileinfo *info, size_t line);
void fileinfo_delete_lines(struct fileinfo info);

#endif // FILEINFO_H
