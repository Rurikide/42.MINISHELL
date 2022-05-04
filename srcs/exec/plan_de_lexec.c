/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_de_lexec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:47:53 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/04 13:20:05 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
AVANT L'EXECUTION

parsing lexer managager

heredoc
pipeline pour les fd :
methode 1: open fd_i, open fd_o    et ensuite faire un check. Je dup2 si les fd_i et fd_o sont diff des STDIN/OUT
methode 2: int fd[2] pipe chaque node



EXECUTION






*/