all: 

# http://stackoverflow.com/questions/5963266/call-c-function-from-java

# compile
	@gcc -c -Wall -Werror -fpic \
		HelloWorld.c \
		-I /usr/lib/jvm/java-7-openjdk-amd64/include/

# link		
	@gcc -shared -o \
		libHelloWorld.so \
		HelloWorld.o
