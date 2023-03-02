
BASE := src/find_in_file.c \
	src/find_word.c \
	src/gen_dot_file.c \
	src/parser.c \

help:
	@cat Group_members
	@echo "\n"
	@cat README

gen_dot_file: $(BASE) src/gen_main.c
	@gcc -I./includes $^ -o $@

find_word: $(BASE) src/find_word_main.c
	@gcc -I./includes $^ -o $@

find_in_file: $(BASE) src/find_in_file_main.c
	@gcc -I./includes $^ -o $@