/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 02:32:08 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/12 01:41:21 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int			check_brace(char *s)
{
	int		brace;
	int		i;

	i = -1;
	brace = 0;
	while (s[++i])
	{
		if (s[i] == '{')
			brace++;
		else if (s[i] == '}')
			brace--;
	}
	return (brace);
}

char		*epur_file(int fd)
{
	char	*file_content;
	char	*tmp;
	char	*line;

	line = NULL;
	file_content = NULL;
	while (get_next_line(fd, &line))
	{
		if (!ft_strchr(line, '#')) //faire ca bien apres
		{
			line = ft_epur_str(line);
			if (file_content)
			{
				tmp = file_content;
				file_content = ft_strjoin(tmp, line);
				free(tmp);
			}
			else
				file_content = ft_strdup(line);
			if (!file_content)
				return (NULL);
		}
		free(line);
	}
	return (file_content);
}

char		*get_file_content(char *file_name)
{
	int		fd;
	char	*file_content;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (!(file_content = epur_file(fd)))
		return (NULL);
	if (close(fd) == -1)
		return (NULL);
	if (check_brace(file_content))
	{
		ft_putendl("'{' or '}' missing");
		free(file_content);
		return (NULL);
	}
	return (file_content);
}
