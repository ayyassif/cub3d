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
			printf("%c", cub->map[i][j].value);
			j++;
		}
		printf("\n");
		i++;
	}

	printf("\nheight: %zu, width: %zu\n", cub->height, cub->width);
	printf("\nfront: %zu, back: %zu\n", cub->ofset_front, cub->ofset_back);
}
