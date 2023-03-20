
BASE := src/find_in_file.c \
	src/find_word.c \
	src/gen_dot_file.c \
	src/parser.c \
	src/copy_automate.c \
	src/print_nodes.c

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

union: $(BASE) src/union.c
	@gcc -I./includes $^ -o $@

etoile: $(BASE) src/etoile.c
	@gcc -I./includes $^ -o $@

clean:
	rm -rf gen_dot_file find_word find_in_file union etoile