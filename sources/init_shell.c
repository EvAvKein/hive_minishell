
#include "minishell.h"

/**
 * 
 * TODO: Write these docs
 * 
 * @param node_next An address to a t_node pointer
 * 
 */
void	skip_to_last_node(t_node **node)
{
	while (node && *node && (*node)->next)
		*node = (*node)->next;
}

/**
 * 
 * TODO: Write these docs
 * 
 * @param node An address to a `t_node` pointer
 * 
 */
void	skip_to_first_node(t_node **node)
{
	while (node && *node && (*node)->prev)
		*node = (*node)->prev;
}
