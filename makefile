Comment:Comment.c
	gcc -g -o $@ $^
PHONY:clear
clear:
	rm -r Comment output.c;
