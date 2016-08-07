/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 12:49:33 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/07 01:48:44 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>


#include<stdio.h>

char		*get_file_content(char *file_name)
{
	char	*line;
	int		fd;
	char	*file_content;
	char	*tmp;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = NULL;
	file_content = NULL;
	while (get_next_line(fd, &line))
	{
		//faire ca bien apres
		if (!ft_strchr(line, '#'))
		{
			if (file_content)
			{
				tmp = file_content;
				file_content = ft_strjoin(tmp, line);
				free(tmp);
			}
			else
				file_content = ft_strdup(line);
		}
		free(line);
	}
	if (close(fd) == -1)
		return (NULL);
	return (file_content);
}

int			find_type(char *s)
{
	if (!s)
		return (NONE);
	if (ft_strstr(s, "scene"))
		return (SCENE); 
	if (ft_strstr(s, "light"))
		return (LIGHT); 
	if (ft_strstr(s, "object"))
		return (OBJECT);
	if (ft_strstr(s, "camera"))
		return (CAMERA);
	return (NONE);
}

char		*find_scop(char *s, int ref_level, int *max_level)
{
	static int	level;
	char		*ret;
	int			i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '{')
		{
			level++;
			*max_level += 1;
		}
		else if (s[i] == '}')
		{
			level--;
			if (level == ref_level)
				break ;
		}
	}
	ret = ft_strsub(s, 0, i + 1);
	return (ret);
}

t_part		*create_part(void)
{
	t_part *part;

	if (!(part = (t_part *)malloc(sizeof(t_part))))
		return (NULL);
	part->type = NONE;
	part->n_elems = 0;
	part->elems = NULL;
//	part->sub_parts = NULL;
	part->next = NULL;
	return (part);
}

t_elem		*create_elem(void)
{
	t_elem	*elem;

	if (!(elem = (t_elem *)malloc(sizeof(t_elem))))
		return (NULL);
	elem->name = NULL;
	elem->n_values = 0;
	elem->values = 0;
	elem->next = NULL;
	return (elem);
}

int			arr_len(char **array)
{
	int		i;

	i = 0;
	while (array && array[i])
	{
		i++;
	}
	return (i);
}

char		**cpy_carray(char **array)
{
	char	**new;
	int		i;

	i = arr_len(array);
	if (!(new = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = -1;
	while (array[++i])
	{
		if (!(new[i] = ft_strdup(array[i])))
			return (NULL);
	}
	new[i] = NULL;
	return (new);
}
t_elem		*parse_elem(char *s, t_elem *next)
{
	char	**name;
	char	**values;
	t_elem	*elem;

	if (!(elem = create_elem()))
		return (NULL);
//	ft_putendl("____1");
	if (!(name = ft_strsplit(s, ':')))
		return (NULL);
//	ft_putendl("____2");
	if (arr_len(name) != 2)
		return (NULL);
//	ft_putendl("____3");
	elem->name = ft_strtrim(name[0]);
	if (!(values = ft_strsplit(name[1], ',')))
		return (NULL);
//	ft_putendl("____4");
	if ((elem->n_values = arr_len(values)) <= 0)
		return (NULL);
//	ft_putendl("____5");
//	int i = -1;
//	while (values[++i])
//		ft_putendl(values[i]);
	if (!(elem->values = cpy_carray(values)))
		return (NULL);
	elem->next = next;
	free_tab(name);
	free_tab(values);
//	ft_putendl("____6");
	return (elem);

}

t_part		*parse_scop(char *scop, int max_level)
{
	t_part	*new_part;
	char	**array;
	char	*tmp;
	int		i;

	(void)max_level;
	if (!ft_strchr(scop, ':'))
		return (NULL);
	if (!(new_part = create_part()))
		return (NULL);
	if (!(array = ft_strsplit(scop, '{')))
		return (NULL);
	i = -1;
	while (array[++i])
	{
		tmp = ft_strtrim(array[i]);
		if (ft_strchr(tmp, '}'))
		{
			if (!(new_part->elems = parse_elem(tmp, new_part->elems)))
			{
				ft_putendl("YOU FAILED");
				return (NULL);
			}
		}
		else if (ft_strchr(tmp, ':'))
		{
//			ft_putendl(tmp);
			if (new_part->type == NONE)
				new_part->type = find_type(tmp);
//			if (part->type != 0)
//			{
//				//faux
//				if (!(part->sub_parts = create_part()))
//					return (NULL);
//			}
		}
	}
	return (new_part);
}

t_part		*parse_content(char *s, t_part * part)
{
	char	*scop;
	int		i;
	int		max_level;
	t_part	*tmp;

	i = 0;
	max_level = 0;
	tmp = NULL;
	while (s && s[i])
	{
		scop = find_scop(s + i, 1, &max_level);
//		ft_putendl("#######################################");
//		ft_putendl(scop);
//		ft_putendl("#######################################");
		i += ft_strlen(scop);
		tmp = parse_scop(scop, max_level);
//		s = cut(s);
		free(scop);
		if (!part)
		{
//			ft_putendl("! part");
			part = tmp;
		}
		else if (tmp)
		{
//			ft_putendl("part");
			tmp->next = part;
			part = tmp;
//		ft_putendl("1");
		}
	}
	return (part);
}

t_scene		*parse(char *file_name)
{
//	ft_putendl("parse");
	char	*file_content;
	int		level;
	t_part	*part;

	level = 0;
	part = NULL;
	if (!(file_content = get_file_content(file_name)))
		return (NULL);
	part = parse_content(file_content, part);
	if (part == NULL)
		ft_putendl("nul");
	else
	{
		t_part *tmp = part;
		while (tmp)
		{
			printf("TYPE : %d\n", tmp->type);
			t_elem *tmp2 = tmp->elems;
			while (tmp2)
			{
				ft_putendl("_______________________________________");
					int j = -1;
					ft_putendl(tmp2->name);
					while (tmp2->values[++j])
						ft_putendl(tmp2->values[j]);
				ft_putendl("_______________________________________");
				tmp2 = tmp2->next;
			}
			tmp = tmp->next;
		}
	}
	return (NULL);
}
