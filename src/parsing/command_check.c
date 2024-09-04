#include "minishell.h"

int is_invalid_syntax(t_shell *shell)
{
	int len = ft_strlen(shell->current_line);
	int i = 0;
	int single_quote_open = 0;
	int double_quote_open = 0;

	// Ignore les espaces au début de la commande
	while (shell->current_line[i] == ' ' && shell->current_line[i] != '\0')
		i++;

	// Vérifie si la commande commence par un pipe
	if (shell->current_line[i] == '|')
		return (2);

	// Parcourt la ligne pour détecter les guillemets non fermés
	while (shell->current_line[i] != '\0') {
		if (shell->current_line[i] == '\'' && double_quote_open == 0)
		{
			single_quote_open = !single_quote_open;
		} else if (shell->current_line[i] == '"' && single_quote_open == 0)
		{
			double_quote_open = !double_quote_open;
		}
		i++;
	}

	// Ignore les espaces à la fin de la commande
	while (len > 0 && shell->current_line[len - 1] == ' ')
		len--;

	if (len == 0)
		return (0);

	// Vérifie si la commande se termine par un pipe ou une redirection
	if (shell->current_line[len - 1] == '|')
		return (1);
	else if (shell->current_line[len - 1] == '<' || shell->current_line[len - 1] == '>')
		return (3);

	// Vérifie s'il y a des guillemets non fermés
	if (single_quote_open || double_quote_open)
		return (4);

	return (0);
}
