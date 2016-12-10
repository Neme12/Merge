CC = clang
CFLAGS += -pedantic -Wall -std=gnu99

FILES = main.c arrayList.c str.c string.c fileSearcher.c codeFileSearcher.c fileLineReader.c fileLineWriter.c merger.c fileNameWithT.c args.c

program:
	${CC} ${CFLAGS} ${FILES} -o merge

clean:
	rm -f merge

.PHONY: program clean
