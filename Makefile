###############################################################################
#								STANDARS	 								  #
###############################################################################
NAME 		= 		philo
RM 			= 		rm -rf
INCLUDE		=		inc/philo.h
OBJS		= 		obj/
SRC_DIR		=		src/

###############################################################################
#								COMPILER	  								  #
###############################################################################

CC 			= 		gcc
CCFLAGS		= 		-g#-Wall -Wextra -Werror -fsanitize=address

###############################################################################
#									SRC    									  #
###############################################################################

SRC 		= 		$(SRC_DIR)main.c\
					$(SRC_DIR)actions.c\
					$(SRC_DIR)data_funtions.c\
					$(SRC_DIR)data_init.c\
					$(SRC_DIR)dinner.c\
					$(SRC_DIR)passeo.c\
					$(SRC_DIR)set_get.c\
					$(SRC_DIR)syncro_th.c\
					$(SRC_DIR)time_utils.c

###############################################################################
#									OBJ_DIR	   								  #
###############################################################################

OBJ_DIR = $(patsubst $(SRC_DIR)%.c, $(OBJS)%.o, $(SRC))

###############################################################################
#								RULES	      								  #
###############################################################################

all:
	@make $(NAME) --no-print-directory

$(NAME):: $(OBJ_DIR) $(LIBFT)
	@echo "Compiling file"
	@$(CC) $(CCFLAGS) $(OBJ_DIR) -o $(NAME)
$(NAME)::
	@echo "Philo compiled"

$(OBJS)%.o: $(SRC_DIR)%.c Makefile $(INCLUDE)
	@echo "Compiling $<"
	@mkdir -p $(OBJS)
	@$(CC) $(CCFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up..."
	@$(RM) $(OBJS)

fclean: clean
	@echo "Cleaning file..."
	@$(RM) $(NAME)

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re
