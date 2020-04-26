a.out: main.cc menus.h
	g++ -fsanitize=address -fconcepts -fpermissive -Wconversion -lncurses -lform -lpanel -lmenu -g -O2  main.cc

clean:
	rm -rf a.out core *.o

