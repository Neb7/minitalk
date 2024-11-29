/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:56:03 by benpicar          #+#    #+#             */
/*   Updated: 2024/11/27 12:15:50 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
The sigaction structure is defined by something like:

struct sigaction {
    void   (*sa_handler) (int);
    void   (*sa_sigaction) (int, siginfo_t *, void *);
    sigset_t sa_mask;
    int sa_flags;
    void   (*sa_restorer) (void);
};

option:
SA_SIGINFO: Allows the use of sa_sigaction instead of sa_handler. This provides
access to additional information on the signal, via a siginfo_t structure (used
to access the client PID).
SA_RESTART: Automatically restores system calls interrupted by this signal.
SA_NODEFER: Prevents the processed signal from being blocked automatically 
during the execution of the handler.

int sigemptyset(sigset_t *set); empty set of all signals to not block any signal

sigaction(the signal, pointer to sigaction structure, pointer to store)
sigaction is used to modify the action to be performed when receiving a specific
signal
*/
void	ft_init_sig(int sig, void (*ft_ges)(int, siginfo_t *, void *))
{
	struct sigaction	signal;

	signal.sa_sigaction = ft_ges;
	signal.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	sigemptyset(&signal.sa_mask);
	if (sig == SIGUSR1)
		sigaction(SIGUSR1, &signal, 0);
	else if (sig == SIGUSR2)
		sigaction(SIGUSR2, &signal, 0);
}
