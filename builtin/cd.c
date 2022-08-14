/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunes <agunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:53:45 by agunes            #+#    #+#             */
/*   Updated: 2022/08/14 21:29:05 by agunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	gohome(void)
{
	char	*old;
	char	*new;

	old = getcwd(NULL, 0);
	if (chdir(ft_getenv("HOME")) == 0)
	{
		new = getcwd(NULL, 0);
		pwdupdate(new, old);
	}
	else
		notset(old, 1);
}

void	changedirectory(char *command)
{
	char	*old;
	char	*new;

	old = getcwd(NULL, 0);
	if (cdcheck(command, old))
	{
		new = getcwd(NULL, 0);
		pwdupdate(new, old);
	}
}

void	golastpwd(void)
{
	int		i;
	char	*old;
	char	*new;
	char	*temp;

	i = 0;
	old = getcwd(NULL, 0);
	while (g_shell->export[i])
	{
		if (!ft_strcmp(g_shell->export[i], "OLDPWD"))
			notset(old, 2);
		if (!ft_strncmp(g_shell->export[i], "OLDPWD=", 7))
		{
			new = deletechar(g_shell->export[i], '\"');
			temp = new;
			new = ft_strdup(new + findfirstindex(new, '=') + 1);
			chdir(new);
			free(temp);
		}
		i++;
	}
	free(new);
	free(old);
}

int	ft_cd(char *command)
{
	if (!command)
		gohome();
	else if (!ft_strcmp(command, "-"))
		golastpwd();
	else
		changedirectory(command);
	return (1);
}
