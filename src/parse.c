/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 12:49:33 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/22 16:51:59 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void		set_tmp(t_part *tmp, t_part **part)
{
	if (!*part)
		*part = tmp;
	else if (tmp)
	{
		tmp->next = *part;
		*part = tmp;
	}
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
		set_tmp(tmp, &part);
		free(scop);
	}
	return (part);
}

int			get_all(t_part *tmp, t_scene *scene, int *is_init)
{
	if (tmp->type == SCENE)
	{
		if (is_init[0] > 0 || !(scene = get_scene(scene, tmp)))
			return (0);
		is_init[0] = 1;
	}
	if (tmp->type == LIGHT)
	{
		if (!(scene = get_lights(scene, tmp)))
			return (0);
		is_init[2] += 1;
	}
	if (tmp->type == OBJECT)
	{
		if (!(scene = get_objects(scene, tmp)))
			return (0);
		is_init[3] += 1;
	}
	if (tmp->type == CAMERA)
	{
		if (is_init[1] > 0 || !(get_cam(scene, tmp)))
			return (0);
		is_init[1] = 1;
	}
	return (1);
}

t_scene		*config(t_part *part)
{
	t_part	*tmp;
	t_scene	*scene;
	int		is_init[4];

	scene = init_scene();
	is_init[0] = 0;
	is_init[1] = 0;
	is_init[2] = 0;
	is_init[3] = 0;
	tmp = part;
	while (tmp)
	{
		get_all(tmp, scene, is_init);
		tmp = tmp->next;
	}
	if (is_initialized(is_init, scene))
		return (scene);
	return (NULL);
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
	free_part(&part);
	free(file_content);
	return (scene);
}
