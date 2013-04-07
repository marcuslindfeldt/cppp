#
# Makefile to make the file libclientserver.a, containing
# connection.o and server.o
#

CXX		 = g++
CXXFLAGS	 = -ggdb  -Wall -W -Werror -pedantic-errors
CXXFLAGS	+= -Wmissing-braces -Wparentheses
# The following option cannot be used since some of the socket
# macros give warnings on "old-style-cast"
#CXXFLAGS	+= -Wold-style-cast
SRCPATH = ../src
SRC	= $(wildcard $(SRCPATH)/**/*.cc)

.PHONY: all clean cleaner

all: libclientserver.a server 
	#client

# Create the library; ranlib is for Darwin and maybe other systems.
# Doesn't seem to do any damage on other systems.

libclientserver.a: ../src/com/connection.o ../src/server/server.o
	ar rv libclientserver.a \
	../src/com/connection.o ../src/server/server.o
	ranlib libclientserver.a

install: clean all
	mkdir bin
	mkdir lib
	mv server bin
	mv client bin
	mv libclientserver.a lib
	mv $(SRCPATH)/**/*.o lib

clean: 
	$(RM) libclientserver.a server

cleaner: clean untinstall
	$(RM) $(SRCPATH)/**/*.o

uninstall: 
	rm -r bin
	rm -r lib

server: ../src/server/serverhandler.o ../src/server/messageinterpreter.o ../src/com/messagehandler.o ../src/database/inmemorydatabase.o ../src/database/article.o ../src/database/newsgroup.o libclientserver.a
		 $(CXX) -o $@ $^

client: ../src/client/client.o ../src/client/messageinterpreter.o ../com/messagehandler.o ../com/connection.o libclientserver.a
		$(CXX) -o $@ $^

%.d: %.cc
	@set -e; rm -f $@; \
	 $(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	 sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	 rm -f $@.$$$$

include $(SRC:.cc=.d)
