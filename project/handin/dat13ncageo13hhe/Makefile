all: makeall

makeall:
	cd src/shared/ && make
	cd src/server/ && make
	cd src/client/ && make
	
clean:
	cd src/shared/ && make clean
	cd src/server/ && make clean
	cd src/client/ && make clean
	
install: makeall
	cp src/server/newsserver bin/
	cp src/client/newsclient bin/