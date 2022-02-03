/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:48:32 by jinoh             #+#    #+#             */
/*   Updated: 2022/02/03 15:59:01 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

int		ft_printf(const char *fmt, ...);
void	sig_handler(int signo);

void	ft_error(void);
void	print_pid(void);
char	*ft_itoa(int n);

#endif
