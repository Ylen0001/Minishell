/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:24:43 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/30 17:43:34 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


void b_i_echo(t_data *data, char *cmd)
{
    char *splited;
    int newline = 1;

    splited = clean_input(data, cmd);
    if (splited == NULL)
        return;

    if (data->flag_echo_trig == 1)
        newline = 0;

    printf("%s", splited);
    if (newline)
        printf("\n");

    free(splited); // Libère la mémoire allouée par strdup
    data->exit_status = 0;
}


char *clean_input(t_data *data, char *cmd)
{
    size_t i = 5; // Skips "echo "
    while (cmd[i] == ' ' || cmd[i] == '\t') // Skip les espaces après "echo"
        i++;

    if (cmd[i] == '-')
    {
        i++;
        while (cmd[i] == 'n')
            i++;
        if (cmd[i] == ' ' || cmd[i] == '\t')
        {
            i++;
            data->flag_echo_trig = 1; // Option -n détectée
        }
        else
            i = 5; // Pas d'option valide, on reset à après "echo"
    }

    while (cmd[i] == ' ' || cmd[i] == '\t') // Skip espaces après les options
        i++;

    // Alloue et copie la chaîne nettoyée
    return strdup(cmd + i); // strdup gère déjà l'allocation et la copie
}
