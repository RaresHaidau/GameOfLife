build:
	gcc gol.c gol_in.c -o a.out
run:
	./checker-linux-amd64 -i
clean:
	rm -rf a.out