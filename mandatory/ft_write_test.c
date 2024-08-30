#include "cub3d.h"

void ft_write_cub(t_cub *cub)
{
	for (int i = 0; i < 4; i++)
		printf("|%d| %s\n", cub->texture[i].identifier, cub->texture[i].path);

	printf("\nF %d, %d, %d\n", cub->floor.red, cub->floor.green, cub->floor.blue);
	printf("C %d, %d, %d\n\n", cub->ceiling.red, cub->ceiling.green, cub->ceiling.blue);

	// t_line_map *tmp;
	// tmp = cub->line_map;
	// while (tmp)
	// {
	// 	printf("%s\n", tmp->line_map);
	// 	tmp = tmp->next;
	// }

	size_t	i = 0;
	size_t j;
	while (i < cub->height)
	{
		j = 0;
		while (j < cub->width)
		{
			if (cub->map[i][j].value == 6)
				printf("\e[1;30m██\e[0m");
			else if (cub->map[i][j].value == 0)
				printf("\e[1;32m██\e[0m");
			else if (cub->map[i][j].value == 1)
				printf("\e[1;33m██\e[0m");
			else
				printf("\e[1;31m██\e[0m");
			j++;
		}
		printf("\n");
		i++;
	}

	printf("\nheight: %zu, width: %zu\n", cub->height, cub->width);
	printf("\nfront: %zu, back: %zu\n", cub->ofset_front, cub->ofset_back);
}
