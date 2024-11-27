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
 La structure sigaction est définie par quelque chose comme :

struct sigaction {
    void     (*sa_handler) (int);
    void     (*sa_sigaction) (int, siginfo_t *, void *);
    sigset_t   sa_mask;
    int        sa_flags;
    void     (*sa_restorer) (void);
};

option :
SA_SIGINFO : Permet d'utiliser la fonction sa_sigaction au lieu de sa_handler.
Cela donne accès à des informations supplémentaires sur le signal, via une
structure siginfo_t (dont on se sert pour acceder au PID du client).
SA_RESTART : Rétablit automatiquement les appels système interrompus par
ce signal.
SA_NODEFER : Empêche que le signal traité soit bloqué automatiquement pendant
l'exécution du gestionnaire.

int sigemptyset(sigset_t *set); vide set de tout signaux pour ne bloquer
aucun signal

sigaction(le signal, pointeur vers structure sigaction, pointeur pour stocker)
sigaction sert a modifier l'action a effectuer lors de la reception d'un signal
specifique
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
