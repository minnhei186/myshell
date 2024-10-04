/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:36:42 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/02 10:42:52 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

char	*ft_char_recalloc(char *old, size_t count)
{
	char	*new;
	size_t	i;

	if (count == SIZE_MAX)
		return (NULL);
	if (old == NULL)
	{
		new = ft_calloc(count + 1, sizeof(char));
		if (new == NULL)
			return (NULL);
		return (new);
	}
	i = ft_strlen(old);
	if (i > SIZE_MAX - count - 1) //右辺が-1だとラウンドアップされ検出できない
		return (NULL);
	new = ft_calloc(i + count + 1, sizeof(char));
	if (new == NULL)
		return (NULL);
	strlcpy(new, old, i + 1); // null終端文字を含めること
	free(old);
	return (new);
}

char	*append_char(char *old, char append_c)
{
	char	*new;
	int		i;

	new = ft_char_recalloc(old, 1);
	if (new == NULL)
		return (NULL);
	if (old == NULL)
		new[0] = append_c;
	else
	{
		//すでにoldはfreeずみ
		i = ft_strlen(new);
		new[i] = append_c;
	}
	return (new);
}

#define SINGLE_QUOTE '\''
#define DOUBLE_QUOTE '\"'

char	*remove_single_quote(char **word_ppt, char *new_word)
{
	(*word_ppt) = (*word_ppt) + 1;
	while (**word_ppt != SINGLE_QUOTE)
	{
		new_word = append_char(new_word, **word_ppt);
		if (new_word == NULL)
			return (NULL);
		(*word_ppt) = (*word_ppt) + 1;
	}
	(*word_ppt) = (*word_ppt) + 1;
	return (new_word);
}

char	*remove_double_quote(char **word_ppt, char *new_word)
{
	(*word_ppt) = (*word_ppt) + 1;
	while (**word_ppt != DOUBLE_QUOTE)
	{
		new_word = append_char(new_word, **word_ppt);
		if (new_word == NULL)
			return (NULL);
		(*word_ppt) = (*word_ppt) + 1;
	}
	(*word_ppt) = (*word_ppt) + 1;
	return (new_word);
}

void	remove_quote(t_token_info *token)
{
	char	*word;
	char	*new_word;

	word = token->word;
	new_word = NULL;
	while (*word)
	{
		if (*word == SINGLE_QUOTE)
			new_word = remove_single_quote(&word, new_word);
		else if (*word == DOUBLE_QUOTE)
			new_word = remove_double_quote(&word, new_word);
		else
		{
			new_word = append_char(new_word, *word);
			word++;
		}
	}
	free(token->word);
	token->word = new_word;
}

void	token_quote_removal(t_token_info *token)
{
	if (token == NULL)
		return ;
	while (token->next != NULL)
	{
		if ((token->kind == WORD) && (token->word != NULL))
			remove_quote(token);
		token = token->next;
	}
}

void	quote_remover(t_node_info *node)
{
	if (node == NULL)
		return ;
	token_quote_removal(node->node_token);
	token_quote_removal(node->filename);
	token_quote_removal(node->delimiter);
	quote_remover(node->redirects);
	quote_remover(node->cmd);
	quote_remover(node->re_node);
}

bool	is_alpha_or_under(char c)
{
	return (ft_isalpha(c) || c == '_');
}
bool	is_alpha_or_under_or_digit(char c)
{
	return (is_alpha_or_under(c) || ft_isdigit(c));
}

bool	is_variable(char *word)
{
	if (word[0] == '$' && is_alpha_or_under(word[1]))
		return (true);
	return (false);
}

char	*expand_variable_word(char **word, char *new_word)
{
	char	*variable_name;
	char	*variable_word;

	variable_name = NULL;
	variable_word = NULL;
	// skip_$
	*word = *word + 1;
	if (is_alpha_or_under(**word) != 1)
		printf("need_alpha_or_under_front_of_str\n");
	//途中で'などが出てきたら、wordは動かさない。
	while (is_alpha_or_under_or_digit(**word))
	{
		variable_name = append_char(variable_name, **word);
		*word = *word + 1;
	}
	variable_word = getenv(variable_name);
	if (variable_word != NULL)
	{
		while (*variable_word != '\0')
		{
			new_word = append_char(new_word, *variable_word);
			variable_word++;
		}
	}
	return (new_word);
}

char *expand_variable_single_quote(char **word,char *new_word)
{
	//append_and_skip_single_quote
	new_word=append_char(new_word,**word);
	*word=*word+1;
	while(**word!=SINGLE_QUOTE)
	{
		if(**word=='\0')
		{
			printf("not_close_single_quote\n");
			return NULL;
		}
		new_word=append_char(new_word,**word);
		*word=*word+1;
	}
	
	new_word=append_char(new_word,**word);
	*word=*word+1;
	return new_word;
}

char *expand_variable_double_quote(char **word,char *new_word)
{
	//append_and_skip_single_quote
	new_word=append_char(new_word,**word);
	*word=*word+1;
	while(**word!=DOUBLE_QUOTE)
	{
		if(**word=='\0')
		{
			printf("not_close_double_quote\n");
			return NULL;
		} 
		if(is_variable(*word))
			new_word=expand_variable_word(word,new_word);
		else
		{
			new_word=append_char(new_word,**word);
			*word=*word+1;
		}
	}
	
	new_word=append_char(new_word,**word);
	*word=*word+1;
	return new_word;
}



void	expand_variable(t_token_info *token)
{
	char	*word;
	char	*new_word;

	word = token->word;
	new_word = NULL;
	while (*word)
	{
		 if (*word == SINGLE_QUOTE)
			new_word = expand_variable_single_quote(&word, new_word);
		 else if (*word == DOUBLE_QUOTE)
			new_word = expand_variable_double_quote(&word, new_word);
		else if (is_variable(word))
			new_word = expand_variable_word(&word, new_word);
		else
		{
			new_word = append_char(new_word, *word);
			word++;
		}
	}
	free(token->word);
	token->word = new_word;
}

void	token_variable_expand(t_token_info *token)
{
	if (token == NULL)
		return ;
	while (token->next != NULL)
	{
		if ((token->kind == WORD) && (token->word != NULL))
			expand_variable(token);
		token = token->next;
	}
}

void	variable_expander(t_node_info *node)
{
	if (node == NULL)
		return ;
	token_variable_expand(node->node_token);
	token_variable_expand(node->filename);
	variable_expander(node->redirects);
	variable_expander(node->cmd);
	variable_expander(node->re_node);
}

void	expand(t_node_info *node)
{
	variable_expander(node);
	quote_remover(node);
}
