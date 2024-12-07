/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:36:32 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/07 15:41:59 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_ges(int sig, siginfo_t *info, void *context);
static void	ft_write_str(t_vector **vec, siginfo_t *info);

int	main(int ac, char **av)
{
	if (ac != 1)
	{
		ft_fprintf(2, "Error: wrong format.\nTry: ./server\n");
		return (1);
	}
	ft_init_sig(SIGUSR1, &ft_ges);
	ft_init_sig(SIGUSR2, &ft_ges);
	ft_fprintf(1, "PID : %d\n", getpid());
	while (1)
		pause();
	(void)av;
	return (0);
}

/*If the signal is SIGUSR1 the bit is 1 and if the signql is SIGUSR2 the bit is
2 for reception, sends SIGUSR1 to confirm the character acceptance and SIGUSR2
to confirm the message receipt and reception*/
static void	ft_ges(int sig, siginfo_t *info, void *context)
{
	static char		c = 0;
	static int		bit = -1;
	static t_vector	*vec = NULL;

	if (!vec)
		vec = ft_new_vector(sizeof (char));
	if (!vec)
		exit(EXIT_FAILURE);
	if (bit < 0)
		bit = 7;
	if (sig == SIGUSR1)
		c = c | 1 << bit;
	else if (sig == SIGUSR2)
		c = c & ~(1 << bit);
	if (bit == 0 && c)
		if (ft_add_char_vector(&c, vec, 1, sizeof(char)) == NULL)
			return (ft_free_vector(&vec), exit(EXIT_FAILURE));
	if (bit == 0 && c == 0)
	{
		ft_write_str(&vec, info);
		kill(info->si_pid, SIGUSR2);
	}
	bit--;
	kill(info->si_pid, SIGUSR1);
	(void)context;
}

/*Displays the message once fully received*/
static void	ft_write_str(t_vector **vec, siginfo_t *info)
{
	write(1, (*vec)->buf, (*vec)->index);
	ft_free_vector(vec);
	write(1, "\n\033[3;92m", 8);
	ft_fprintf(1, "Message received from PID : %d", info->si_pid);
	write(1, "\033[0m\n", 5);
}
