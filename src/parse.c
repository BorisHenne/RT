/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 12:49:33 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/15 04:11:19 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>


#include<stdio.h>

int			is_valid(char *s)
{
	while (*s)
	{
		if (*s != '}')
		{
			return (1);
		}
		s++;
	}
	return (0);
}

t_part		*parse_content(char *s, t_part *part)
{
	char	*scop;
	int		i;
	t_part	*tmp;

	i = 0;
	tmp = NULL;
	while (s && s[i])
	{
		scop = find_scop(s + i, 1);
		i += ft_strlen(scop);
		if (is_valid(scop))
		{
			if (!(tmp = parse_scop(scop)))
				return (NULL);
		}
		else
			tmp = NULL;
		free(scop);
		if (!part)
			part = tmp;
		else if (tmp)
		{
			tmp->next = part;
			part = tmp;
		}
	}
	return (part);
}

int			is_number(char *s)
{
	while (*s)
	{
		if (!((*s >= '0' && *s <= '9') || *s == '.' || *s == '+' || *s == '-'))
		{
			return (0);
		}
		s++;
	}
	return (1);
}
t_vec		*get_vec(char **values, char *name)
{
	t_vec 	*vec;
	int		n_values;

	if ((n_values = arr_len(values)) != 3)
	{
		if (n_values < 3)
			ft_putstr("missing value in '");
		else
			ft_putstr("too many values in '");
		ft_putstr(name);
		ft_putendl("'");
		return (NULL);
	}
	if (!is_number(values[0]) || !is_number(values[1]) || !is_number(values[2]))
	{
		ft_putstr("value != number in '");
		ft_putstr(name);
		ft_putendl("'");
		return (NULL);
	}
	if (!(vec = (t_vec *)malloc(sizeof(t_vec))))
		return (NULL);
	vec->x = ft_atof(values[0]);
	vec->y = ft_atof(values[1]);
	vec->z = ft_atof(values[2]);
	return (vec);
}

t_color		*get_color(char **values, int ref)
{
	t_color 	*color;
	double		color_max;
	int		n_values;

	color_max = (ref == OBJECT) ? 1.0 : 255.0;
	if ((n_values = arr_len(values)) != 3)
	{
		if (n_values < 3)
			ft_putendl("missing value in 'color'");
		else
			ft_putendl("too many values in 'color'");
		return (NULL);
	}
	if (!is_number(values[0]) || !is_number(values[1]) || !is_number(values[2]))
	{
		ft_putstr("value != number in 'color'");
		return (NULL);
	}
	if (!(color = (t_color *)malloc(sizeof(t_color))))
		return (NULL);
	color->r = ft_atof(values[0]);
	color->g = ft_atof(values[1]);
	color->b = ft_atof(values[2]);
	if ((color->r < 0 || color->r > color_max)
	|| (color->g < 0 || color->g > color_max)
	|| (color->b < 0 || color->b > color_max))
	{
		ft_putstr("value < 0 or > ");
		ft_putnbr(color_max);
		ft_putendl("'color'");
		return (NULL);
	}
	return (color);
}

float		get_num(char **values)
{
	return (ft_atof(values[0]));
}

int			get_bool(char **values)
{
	if (!ft_strcmp(values[0], "y"))
		return (1);
	else if (!ft_strcmp(values[0], "n"))
		return (0);
	return (-1);
}

int			get_enum(char **values)
{
	if (!strcmp(values[0], "marble"))
		return (MARBLE);
	else if (!strcmp(values[0], "checker"))
		return (CHECKER);
	else if (!strcmp(values[0], "none"))
		return (NONE);
	else if (!strcmp(values[0], "sepia"))
		return (SEPIA);
	else if (!strcmp(values[0], "bn"))
		return (NOIR_BLANC);
	return (-1);
}

t_quad		*get_quad(char **values)
{
	t_quad 	*quad;
	int		n_values;

	if ((n_values = arr_len(values)) != 3)
	{
		if (n_values < 3)
			ft_putendl("missing value in 'quad'");
		else
			ft_putendl("too many values in 'quad'");
		return (NULL);
	}
	if (!is_number(values[0]) || !is_number(values[1]) || !is_number(values[2]))
	{
		ft_putstr("value != number in 'quad'");
		return (NULL);
	}
	if (!(quad = (t_quad *)malloc(sizeof(t_quad))))
		return (NULL);
	quad->A = ft_atof(values[0]);
	quad->B = ft_atof(values[1]);
	quad->C = ft_atof(values[2]);
	return (quad);
}

t_scene		*config(t_part *part)
{
	t_part	*tmp;
	t_scene	*scene;
	t_cam	*tmp_cam;
	int		is_init[4];

	scene = init_scene();
	is_init[0] = 0;
	is_init[1] = 0;
	is_init[2] = 0;
	is_init[3] = 0;
	tmp = part;
	while (tmp)
	{
		if (tmp->type == SCENE)
		{
			if (is_init[0] > 0)
				return (NULL);
			if (!(scene = get_scene(scene, tmp)))
				return (NULL);
			is_init[0] = 1;
		}
		if (tmp->type == LIGHT)
		{
			if (!(scene = get_lights(scene, tmp)))
				return (NULL);
			is_init[2] += 1;
		}
		if (tmp->type == OBJECT)
		{
			if (!(scene = get_objects(scene, tmp)))
				return (NULL);
			is_init[3] += 1;
		}
		if (tmp->type == CAMERA)
		{
			if (is_init[1] > 0)
				return (NULL);
			if (!(tmp_cam = get_cam(scene, tmp)))
				return (NULL);
			is_init[1] = 1;
		}
		tmp = tmp->next;
	}
	if (is_init[1] == 0)
	{
		ft_putendl("No Camera");
		return (NULL);
	}
	if (is_init[2] == 0 && scene->ambient <= 0.0)
	{
		ft_putendl("No Lights");
		scene->ambient = 0.5;
	}
	if (is_init[3] == 0)
	{
		ft_putendl("No Objects");
	}
	return (scene);
}

t_scene		*parse(char *file_name)
{
	char	*file_content;
	int		level;
	t_part	*part;
	t_scene	*scene;

	level = 0;
	part = NULL;
	if (!(file_content = get_file_content(file_name)))
		return (NULL);
	if (!(part = parse_content(file_content, part)))
		return (NULL);
	if (!(scene = config(part)))
		return (NULL);
//	write_scene(*scene);
	free_part(&part);
	free(file_content);

	return (scene);
}
