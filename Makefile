all:
	PATH=/usr/local/share/Qt-5.2.1/5.2.1/gcc_64/bin:$PATH
	qmake src/bludiste.pro -o src/Makefile
	$(MAKE) -C src

clean:
	$(MAKE) -C src clean
	rm -f -r doc/html
	rm -f -r doc/latex
	rm -f src/bludiste2014
	rm -f xvlaci00.zip

doxygen:
	doxygen doc/config

run:
	./src/bludiste2014

pack:
	zip -r xvlaci00.zip src examples doc/config README.txt Makefile

