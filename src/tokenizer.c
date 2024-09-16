/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 10:37:11 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/16 10:21:43 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

#define META "\t\n|&;()<>"
#define OPERAND

enum						e_token_kind
{
	RESERVE,
	WORD,
	OP,
	ROF,
};

typedef enum e_token_kind	e_kind;

typedef struct s_token		t_token;

struct						s_token
{
	char					*word;
	e_kind					kind;
	t_token					*next;
}



//unitの作成

t_token *make_unit_token(void)
{
	return (t_token *)ft_calloc(1,sizeof(t_token));
}


int is_c_meta(char c)
{
	if(c&&ft_strchr(META,c))
		return sizeof(c);
	return 0;		
}

void meta_prosecc(char *prompt)
{
	prompt++;
}



//どれなのかがわかれば、あとはmeta文字がくるまでを切り取ればいい
//ここで重要になるのはoperandと予約後だよ
//これが非常に変わっている、なぜなら、これと定まっているから
//サーチもとをダブルポインタで持っておき、strchrで見つかったら
//そのサーチ元からsizeを推定すればいい。なる、

//先頭からサーチしていく。ここにおける場である。色々だがね。
//wordをどう定義するかだね。
t_token_info *prompt_set(char *prompt)
{
	t_token_info *token;

	if(is_operand(prompt))
		token=make_operand_token(prompt);
	else if(is_reserved(prompt)
		token=make_reserved_token(prompt);
	else
		token=make_reserver_token(prompt);

		return token;
}




	
	

	


//ここで重要なのがエラーだな。うわお、エラーがあると、これは。
//つまり、その現在が、つまりプログラムに現在が生まれる。
//４次元的なプログラムとなる。のか。
t_token *tokenizer(t_prompt_info *info,t_token_info *token,char *prompt)
{

	int i;
	int set_size;
	t_token_info *new_token;

	i=0;
	while(*prompt)
	{
		//tokeが作られなかったということは
		new_token=token_set(prompt);
		if(new_token==NULL)
		set_size=ft_strlen(new_token->word);
		if(set_size==0)
		{
			set_size=1;
			error_set("not_define_character",0,info);
		}
		prompt+=set_size;
	}

	EOF_token();

	return token;
}
		





//
//	
//t_token *tokenizer(t_prompt_info *info,t_token_info *token,char *prompt)
//{
//
//	int i;
//
//	i=0;
//	while(*prompt)
//	{
//		if(is_word(prompt))
//		{}
//		else if(is_reserve(prompt))
//		{}
//		else if(is_op(prompt))
//		{}
//		else
//		{
//			error_set("not_define_character",0,info);
//			prompt++;
//		}
//	}
//
//	EOF_token();
//
//	return token;
//}
//		
//
//
