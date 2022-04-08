/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:15:15 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/08 17:25:13 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// EXPORT AJOUTE DES VARIABLES D'ENVIRONNEMENT
// BASH KEY="value", mais zsh ne met pas de double quotes