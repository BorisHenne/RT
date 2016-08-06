/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 04:28:31 by bhenne            #+#    #+#             */
/*   Updated: 2016/08/06 04:30:28 by bhenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	**init_file(void)
{
	char	**file;

	file = (char **)malloc(sizeof(char *) * 14);
	file[0] = ft_strdup("../ressources/worldmap.xpm");
	file[1] = NULL;
	return (file);
}

void	get_text(t_env *e)
{
	char	**file;
	int		x;
	int		*a;
	int		b;

	file = init_file();
	x = 0;
	a = &e->t_edn;
	while (file[x])
	{
		e->t_img[x] = mlx_xpm_file_to_image(e->mlx, file[x], &e->w, &e->h);
		free(file[x]);
		e->t_data[x] = mlx_get_data_addr(e->t_img[x], &b, &(e->t_sl[x]), a);
		e->t_bpp[x] = b;
		x++;
	}
	free(file);
}

void	init_tex(t_env *e)
{
	e->t_img = (void **)malloc(sizeof(void *) * 13);
	e->t_data = (char **)malloc(sizeof(char *) * 13);
	e->t_bpp = (int *)malloc(sizeof(int) * 13);
	e->t_sl = (int *)malloc(sizeof(int) * 13);
	get_text(e);
}

