/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:20:41 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/08 14:36:26 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef builtins
#define builtins

int ft_pwd(char **args, char **envp);
int ft_env(char **argv, char **envp);
int	ft_unset(char **args, char **envp);
// void ft_exit(char **args);
int ft_cd(char **args, char **envp);

#endif