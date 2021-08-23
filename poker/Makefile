a.out: main.cc menus.h
	g++ -fsanitize=address -fconcepts -fpermissive -Wconversion -lncurses -lform -lpanel -lmenu -g -o -Wall -O2  main.cc

clean:
	rm -rf a.out core *.o

