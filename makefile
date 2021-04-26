# Ian Edwards - my Makefile
# EDWIAN004
CC=g++         # the compiler
LIBS=-lm       # the libraries we will ref

# object files to create .exe
tags: ConnectedComponent.o PGMimageProcessor.o findcomp.o
	$(CC) ConnectedComponent.o PGMimageProcessor.o findcomp.o -o findcomp.exe $(LIBS)

# Implicit pattern rule for compiling object files
%.o : %.cpp   # $< is the first dependancy and $@ is the target
	$(CC) -c $< -o $@
   
# other rules; invoked by make clean etc 

# deletes all the object code files
clean:
	@rm -f *.o
	@rm findcomp.exe
	@rm test.exe
   
# copies/moves the relevant binaries and/or libraries to the correct folders   
install:
	@mv findcomp.exe ~/bin
	
test: ConnectedComponent.o PGMimageProcessor.o Test.o
	$(CC) ConnectedComponent.o PGMimageProcessor.o Test.o -o test.exe $(LIBS)

