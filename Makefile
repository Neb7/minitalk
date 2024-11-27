LIBFT		= libft/
OBJS_DIR	= objects/
SRCS_DIR 	= srcs/

#Sources
SRCS		= minitalk_utils.c

#Server
MAIN_SERV	= server.c
SRCS_S		+= $(addprefix ${SRCS_DIR}, ${MAIN_SERV})
SRCS_S		+= $(addprefix ${SRCS_DIR}, ${SRCS})

OBJS_S		= $(addprefix ${OBJS_DIR}, ${MAIN_SERV:.c=.o})
OBJS_S		+= $(addprefix ${OBJS_DIR}, ${SRCS:.c=.o})

#Client 
MAIN_CLI	= client.c
SRCS_C		+= $(addprefix ${SRCS_DIR}, ${SRCS})
SRCS_C		+= $(addprefix ${SRCS_DIR}, ${MAIN_CLI})

OBJS_C		= $(addprefix ${OBJS_DIR}, ${MAIN_CLI:.c=.o})
OBJS_C		+= $(addprefix ${OBJS_DIR}, ${SRCS:.c=.o})


INCLUDES	= includes
NAME_1		= server
NAME_2		= client
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -I ${INCLUDES}

#Colors
LIGHT_GRAY	= \033[2m
ORANGE		= \033[1;33m
DARK_GRAY	= \033[0;90m
RED			= \033[0;91m
GREEN		= \033[0;92m
YELLOW		= \033[0;93m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m
CYAN		= \033[0;96m
WHITE		= \033[0;97m
RESET		= \033[0m

#Forme
BOLD		= \033[1m
ITALIC		= \033[3m
UNDERLINE	= \033[4m
CROSS		= \033[9m
FLASH		= \033[5m
NEGATIF		= \033[7m

all:			${NAME_1} ${NAME_2}

${OBJS_DIR}%.o: ${SRCS_DIR}%.c | ${OBJS_DIR}
				@cc ${CFLAGS} -c $< -o $@

${NAME_1}:		${OBJS_S}
				@echo "${BLUE}'libft.a' is compiling... 🔥 ${ITALIC}(if needed)${RESET}"
				@make -sC ${LIBFT}
				@${CC} ${CFLAGS} ${OBJS_S} -L${LIBFT} -lft -o $@ 
				@echo "${YELLOW}'$@' is compiled ! ✅${RESET}"

${NAME_2}:		${OBJS_C}
				@echo "${BLUE}'libft.a' is compiling... 🔥 ${ITALIC}(if needed)${RESET}"
				@make -sC ${LIBFT}
				@${CC} ${CFLAGS} ${OBJS_C} -L${LIBFT} -lft -o $@ 
				@echo "${YELLOW}'$@' is compiled ! ✅${RESET}"

${OBJS_DIR}:
				@mkdir -p ${OBJS_DIR}

clean:
				@${RM} ${OBJS_S} ${OBJS_C}
				@${RM} -r ${OBJS_DIR}
				@make clean -sC ${LIBFT}
				@echo "${RED}'${NAME_1}' and '${NAME_2}' objects are deleted ! 👍${RESET}"

fclean:			clean
				@${RM} ${NAME_1} ${LIBFT}libft.a ${NAME_2}
				@echo "${RED}'${NAME_1}', '${NAME_2}' and 'libft.a' are deleted ! 👍${RESET}"

re:				fclean all

.PHONY:			all clean fclean re
