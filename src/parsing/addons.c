/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addons.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:15:07 by noldiane          #+#    #+#             */
/*   Updated: 2024/09/16 22:06:41 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_end(t_shell *shell, int start)
{
	int	i;

	i = start + 1;
	while (shell->current_arg[i])
	{
		if (shell->current_arg[i][0] == '|' || \
		is_redirecion(shell->current_arg[i]))
			break ;
		i++;
	}
	return (i);
}

void free_main_shell(t_shell *shell)
{
    int i;
    int j;

    if (shell == NULL || shell->current_arg == NULL)
        return;

    i = 0;
    while (shell->current_arg[i] != NULL)
    {
        // Gestion des redirections au début
        if (is_redirecion(shell->current_arg[i]) && i == 0 && shell->was_quoted[i] == 0)
        {
            // Libère les tokens de redirection
            free(shell->current_arg[0]); // "<" ou ">"
            free(shell->current_arg[1]); // Le fichier (ex: "Makefile")

            // Décale les arguments
            j = 2; // Commence à l'indice 2
            while (shell->current_arg[j] != NULL)
            {
                shell->current_arg[j - 2] = shell->current_arg[j];
                j++;
            }
            shell->current_arg[j - 2] = NULL; // Termine le tableau

            // Réinitialise les indices et états
            i = 0;
            free_all_shells(shell->next);
            shell->is_piped = 0;
            shell->pipe_in = -1;
            shell->pipe_out = -1;
            shell->next = NULL;
            continue;
        }
        // Modification ici :
        else if (((is_redirecion(shell->current_arg[i]) && i != 0 && shell->was_quoted[i] == 0) ||
                  (shell->current_arg[i][0] == '|' && shell->was_quoted[i] == 0 && shell->current_arg[i + 1] != NULL)))
        {
            // Si c'est une redirection ou un pipe non guillemeté au milieu des arguments, on arrête le traitement ici
            j = i;
            while (shell->current_arg[j] != NULL)
            {
                free(shell->current_arg[j]);
                shell->current_arg[j] = NULL;
                j++;
            }
            return;
        }
        i++;
    }
}
