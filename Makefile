build:
	gcc gol.c gol_in.c gol.h -o a.out
run:
	./checker-linux-amd64 -i
clean:
	rm -rf a.out