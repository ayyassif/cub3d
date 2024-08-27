#include "cub3d.h"

void ft_write_cub(t_cub *cub)
{
	for (int i = 0; i < 4; i++)
		printf("|%d| %s\n", cub->texture[i].identifier, cub->texture[i].path);
	printf("F %d, %d, %d\n", cub->floor.red, cub->floor.green, cub->floor.blue);
	printf("C %d, %d, %d\n", cub->ceiling.red, cub->ceiling.green, cub->ceiling.blue);

}