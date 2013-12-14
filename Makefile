sapshell: src/main.o src/version.o src/cat.o
	$(CC) -o sapshell src/main.o src/version.o src/cat.o -lreadline

clean:
	rm -f sapshell src/*.o
