/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:05:53 by benpicar          #+#    #+#             */
/*   Updated: 2024/11/27 16:12:52 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_ges_user(int sig, siginfo_t *info, void *context);
static void	ft_envoi_str(char *str, int pid);
static void	ft_envoi_char(char c, int pid);
static void	ft_error(int pid);

/*Variable global authorize pour check la reception du bit*/
volatile int	g_control_bit;

int	main(int ac, char **av)
{
	int	pid;

	g_control_bit = 0;
	if (ac != 3)
	{
		ft_fprintf(2, "Error: wrong format.\nTry: ./client [PID] [MESSAGE]");
		return (1);
	}
	ft_init_sig(SIGUSR1, &ft_ges_user);
	ft_init_sig(SIGUSR2, &ft_ges_user);
	pid = ft_atoi(av[1]);
	ft_envoi_str(av[2], pid);
	return (0);
}

/*Signal management for customers*/
static void	ft_ges_user(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGUSR1)
		g_control_bit = 1;
	else if (sig == SIGUSR2)
	{
		ft_fprintf(1, "Message received !\n");
		exit(EXIT_SUCCESS);
	}
	(void)info;
	(void)context;
}

/*Send the string to the server*/
static void	ft_envoi_str(char *str, int pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_envoi_char(str[i], pid);
		i++;
	}
	ft_envoi_char(str[i], pid);
}

/*Sends a character to the server*/
static void	ft_envoi_char(char c, int pid)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		g_control_bit = 0;
		if (c & (1 << bit))
		{
			if (kill(pid, SIGUSR1) < 0)
				ft_error(pid);
		}
		else
			if (kill(pid, SIGUSR2) < 0)
				ft_error(pid);
		bit--;
		while (g_control_bit != 1)
			usleep(10);
	}
}

/*Error for a wrong PID*/
static void	ft_error(int pid)
{
	ft_fprintf(2, "Wrong PID : %d\n", pid);
	exit(EXIT_FAILURE);
}
