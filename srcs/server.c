/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:36:32 by benpicar          #+#    #+#             */
/*   Updated: 2024/11/27 12:52:48 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_ges(int sig, siginfo_t *info, void *context);
static void	ft_write_str(t_vector **vec);

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

/*Si le signal est SIGUSR1 lebit est 1 et si le signql est SIGUSR2 le bit est
de 2 pour la reception, envoie SIGUSR1 pour confirmer la recption du caractere
et SIGUSR2 pour confirmer la reception et la reception du message*/
static void	ft_ges(int sig, siginfo_t *info, void *context)
{
	static char		c = 0;
	static int		bit = -1;
	static t_vector	*vec = NULL;

	if (!vec)
		vec = ft_new_vector();
	if (!vec)
		exit(EXIT_FAILURE);
	if (bit < 0)
		bit = 7;
	if (sig == SIGUSR1)
		c = c | 1 << bit;
	else if (sig == SIGUSR2)
		c = c & ~(1 << bit);
	if (bit == 0 && c)
		if (ft_add_char_vector(&c, vec, 1) == NULL)
			return (ft_free_vector(&vec), exit(EXIT_FAILURE));
	if (bit == 0 && c == 0)
	{
		ft_write_str(&vec);
		kill(info->si_pid, SIGUSR2);
	}
	bit--;
	kill(info->si_pid, SIGUSR1);
	(void)context;
}

/*Affiche le message une fois entierrement receptionner*/
static void	ft_write_str(t_vector **vec)
{
	write(1, (*vec)->buf, (*vec)->index);
	ft_free_vector(vec);
	write(1, "\n", 1);
}
