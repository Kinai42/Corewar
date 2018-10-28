/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbauduin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 09:55:16 by dbauduin          #+#    #+#             */
/*   Updated: 2018/09/30 13:13:24 by dbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		error_header(int error, t_asm *v)
{
    if (!error)
    {
        ft_print(2, "Usage: %s [-a] <sourcefile.s> \n\t-a : Instead ", v->exe);
        ft_print(2, "of creating a .cor file, outputs a stripped and ");
        ft_print(2, "annotated version of the code to the standard output\n");
    }
    if (error == 1)
        ft_print(2, "Can't read source file %s.\n", v->file_name);
    if (error == 2)
        ft_print(2, "Syntax at token NAME \"%s\"\n\tOnly one authorized \
                Usage : .name \"<name>\".\n", NAME_STRING);
    if (error == 3)
        ft_print(2, "Syntax at token COMMENT \"%s\"\n\tOnly one authorized \
                Usage : .comment \"<comment>\".\n", COMMENT_STRING);
    if (error == 4)
        ft_print(2, "No instructions found.\n");
    if (error == 5)
        ft_print(2, "Caracter invalid in name.\n");
    if (error == 6)
        ft_print(2, "Caracter invalid in comment.\n");
    if (error == 7 || error == 8)
        ft_print(2, "The maximum allowed %s length is : %d\n",
                error == 7 ? "NAME" : "COMMENT",
                error == 7 ? NAME_LENGTH : COMMENT_LENGTH);
}

static void		error_label(int error, t_asm *vasm)
{
    if (error == 10)
        ft_print(2, "Syntax error line %d LABEL: %s\n", vasm->l, vasm->error);
    if (error == 11 || error == 12)
        ft_print(2, "No such label while attempting to dereference line ");
    if (error == 11)
        ft_print(2, "%d DIRECT_LABEL \"%s\"\n", vasm->l, vasm->error);
    if (error == 12)
        ft_print(2, "%d INDIRECT_LABEL \"%s\"\n", vasm->l, vasm->error);
}

static void		error_instruction(int error, t_asm *vasm)
{
    if (error == 20)
        ft_print(2, "Syntax error line %d INSTRUCTION: %s\n", vasm->l,
                vasm->error);
    if (error == 21)
        ft_print(2, "Invalid parameter for instruction line %d \"%s\"\n",
                vasm->l,
                g_tab[vasm->irror].mnemonique);
    if (error == 22)
        ft_print(2, "Invalid number of parameter %d for instruction %s\n",
                g_tab[vasm->irror].nbr_args, g_tab[vasm->irror].mnemonique);
}

static void		error_lexical(int error, t_asm *vasm)
{
    if (error == 40)
        ft_print(2, "Lexical error line %d.\n", vasm->l);
    if (error == 41)
        ft_print(2, "Syntax error line %d ENDLINE.\n", vasm->l);
    if (error == 50)
        ft_print(2, "File %s creation failed.\n", vasm->cor);
    if (error == 51)
        ft_print(2, "File %s is incorrect.\n", vasm->file_name);
}

void			ft_error(int error, t_asm *vasm)
{
    vasm->l += 1;
    if (error != 0)
        ft_print(2, "%sError :%s ", RED, DEFAULT);
    if (error < 10)
        error_header(error, vasm);
    else if (error > 9 && error < 20)
        error_label(error, vasm);
    else if (error > 19 && error < 30)
        error_instruction(error, vasm);
    else
        error_lexical(error, vasm);
    if (vasm && error != 0)
        ft_free(vasm);
    exit(EXIT_FAILURE);
}
