NAME = minishell
LIBFT_NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline -lncurses
LIB_DIR = libft
SRC_DIR = src
OBJ_DIR = obj
INCLUDES_DIR = includes

SRCS = $(addprefix $(SRC_DIR)/, \
    minishell.c \
	main_utils.c \
    read_from_stdin.c \
	redirections_2.c \
    waitpids_unlink.c \
    builtin_env_ex_utils.c \
    parsing_utils_0.c \
    parsing_utils_4.c \
    parsing_utils_3.c \
    parsing_utils_2.c \
    parsing_utils_1.c \
    minishell_core.c \
    mc_utils1.c \
    redirections.c \
    core_exec.c \
    files_checker.c \
    builtin_env_ex.c \
    builtin_unset.c \
    builtin_export.c \
    builtin_export_0.c \
    builtin_export_1.c \
    cd.c \
    built_in.c \
    pwd.c \
    echo.c \
    path_exec.c \
    here_doc_handler.c \
    garbage_vector.c \
	signal_handler.c \
	signal_init.c \
    init_vect.c \
    init_exec.c \
    parsing.c \
    cd_2.c \
    workinprog_vect.c \
    garbage_collector.c \
    split_savior.c \
	split_savior_helper.c \
    vect_dup_print.c \
	bi_redir_savior.c \
    bi_redir_savior_2.c \
    free_pids.c \
	exit_savior.c \
)

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

HEADER = $(INCLUDES_DIR)/minishell.h

all : $(NAME)

DEF_COLOR		:= \033[0;39m
GRAY			:= \033[0;90m
RED				:= \033[0;91m
GREEN			:= \033[0;92m
YELLOW			:= \033[0;93m
BLUE			:= \033[0;94m
MAGENTA			:= \033[0;95m
CYAN			:= \033[0;96m
WHITE			:= \033[0;97m
DARK_GRAY       := \033[1;30m 
LIGHT_RED       := \033[0;31m
LIGHT_GREEN     := \033[0;32m
LIGHT_YELLOW    := \033[0;33m
LIGHT_BLUE      := \033[0;34m
LIGHT_MAGENTA   := \033[0;35m
LIGHT_CYAN      := \033[0;36m
LIGHT_WHITE     := \033[0;37m
STEEL_BLUE      := \033[0;38;2;94;99;153m
PASTEL_BLUE     := \033[0;38;2;130;135;206m
RESET			:= \033[0m


PASTEL_BLUE     := \033[0;38;2;130;135;206m
PRUSSIAN_BLUE   := \033[0;38;2;28;49;68m
JASPER           := \033[0;38;2;213;87;59m
OLIVINE           := \033[0;38;2;154;184;122m


TOTAL_FILES := $(shell echo $(SRCS) | wc -w)
COMPILE_COUNT := 0



# Define a function that prints a progress bar based on the current count
define update_compile_count
    $(eval COMPILE_COUNT := $(shell echo $$(( $(COMPILE_COUNT) + 1 ))))
    $(call print_progress_bar,$(COMPILE_COUNT),$(TOTAL_FILES))
endef


$(NAME) : $(LIB_DIR)/$(LIBFT_NAME) $(OBJS)
	@$(CC) $(OBJS) $(LIB_DIR)/$(LIBFT_NAME) $(CFLAGS) $(LDFLAGS) -o $(NAME)
	@echo "$(GRAY)Compilation en cours...$(RESET)"
	@echo "$(STEEL_BLUE)Minishell créé avec succès.$(RESET)"

compute_total:
    $(eval TOTAL_FILES := $(shell var=$$(./progress.sh); if [ $${var} -ne 0 ]; then echo $${var} ; else echo 43; fi))

$(LIB_DIR)/$(LIBFT_NAME):
	@if [ ! -e $(LIB_DIR)/$(LIBFT_NAME) ]; then \
		$(MAKE) -s -C $(LIB_DIR); \
		cp $(LIB_DIR)/$(LIBFT_NAME) .; \
		mv $(LIBFT_NAME) $(NAME); \
	fi

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(call update_compile_count)
	@$(CC) $(CFLAGS) -MMD -I$(INCLUDES_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Shell function to print a progress bar
define print_progress_bar
    @CURRENT=$(1); \
    TOTAL=$(2); \
    if [ "$$TOTAL" -eq 0 ]; then \
        echo "No files to compile."; \
    else \
        PERCENT=$$((CURRENT * 100 / TOTAL)); \
        BAR_WIDTH=50; \
        EMPTY_BLOCK=" "; \
        FILLED_BLOCK="#"; \
        FILLED=$$((BAR_WIDTH * PERCENT / 100)); \
        EMPTY=$$((BAR_WIDTH - FILLED)); \
        FILLED_BAR=$$(printf "%$${FILLED}s" | sed "s/ /$${FILLED_BLOCK}/g") \
        EMPTY_BAR=$$(printf "%$${EMPTY}s" | sed "s/ /$${EMPTY_BLOCK}/g"); \
        printf "\033[?25l"; \
        printf "\033[1B"; \
        printf "\rProgress: [$(PASTEL_BLUE)$$FILLED_BAR$(RESET)$$EMPTY_BAR] %d%% (%d/%d)\n" $$PERCENT $$CURRENT $$TOTAL; \
        if [ "$$CURRENT" -eq "$$TOTAL" ]; then printf "\033[?25h"; else printf "\033[2A"; fi; \
    fi
endef

clean:
	@$(MAKE) -s -C $(LIB_DIR) clean
	@rm -f $(OBJS) > /dev/null 2>&1

fclean: clean
	@$(MAKE) -s -C $(LIB_DIR) fclean
	@rm -f $(NAME) > /dev/null 2>&1
	@echo "$(STEEL_BLUE)Minishell supprimé.$(RESET)"

re: fclean all

.PHONY: clean fclean re all bonus

all : compute_total ascii_art

ascii_art:
	@echo "$(PASTEL_BLUE)"
	@cat logo.txt
	@echo "$(RESET)"
