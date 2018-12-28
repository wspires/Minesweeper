###############################################################################
# Variable declaration
###############################################################################

# name of program
NAME = minesweeper

# compilers/archivers to use
C  = gcc
CC = g++
AR = /usr/bin/ar

# compiler flags
FLAGS =
FLAGS += -std=c++14
FLAGS += -g
#FLAGS += -O2
FLAGS += -Wall

# my own libraries
BOOST_DIR =
#BOOST_DIR = boost_1_68_0/boost

# directories to search for header files
INCLUDES = 
#INCLUDES += -I$(BOOST_DIR)
#INCLUDES += -I<include_directory>

# directories to search for library files
LINK_DIRS =
#LINK_DIRS += -L$(BOOST_DIR)
#LINK_DIRS += -L<link_directory>

# libraries to link with
LIBS =
LIBS += -lm
#LIBS += -l<library>

# loader flags
LD_FLAGS =
#LD_FLAGS +=

# complete set of options to pass to linker
LINK = $(LINK_DIRS) $(LIBS) $(LD_FLAGS)

# name of file containing main()
MAIN = main

# header files in program
HEADERS =
HEADERS += Board.hpp
HEADERS += Cell.hpp
HEADERS += Coord.hpp
HEADERS += Game.hpp
HEADERS += GameSession.hpp
HEADERS += Settings.hpp
HEADERS += Stats.hpp

# source code in program
SOURCES = 
SOURCES += $(MAIN).cpp
SOURCES += Board.cpp
SOURCES += Cell.cpp
SOURCES += Coord.cpp
SOURCES += Game.cpp
SOURCES += GameSession.cpp
SOURCES += Settings.cpp
SOURCES += Stats.cpp

# object code to generate
OBJECTS =
OBJECTS += Board.o
OBJECTS += Cell.o
OBJECTS += Coord.o
OBJECTS += Game.o
OBJECTS += GameSession.o
OBJECTS += Settings.o
OBJECTS += Stats.o

RM = /bin/rm -f

###############################################################################
# Rules for compiling
###############################################################################

# compile each source file into object code
.c.o:
		$(C)  -c $(FLAGS) $< $(INCLUDES)

.cc.o:
		$(CC) -c $(FLAGS) $< $(INCLUDES)

.SUFFIXES: .cpp .o
.cpp.o:
		$(CC) -c $(FLAGS) $< $(INCLUDES)

# link all object modules into executable
$(NAME): $(MAIN).o $(OBJECTS)
		$(CC) $(FLAGS) -o $(NAME) $(MAIN).o $(OBJECTS) $(LINK) $(INCLUDES)

###############################################################################
# Rules for other stuff
###############################################################################

# create static library (excludes $(MAIN).o from library)
lib: $(OBJECTS)
	$(AR) rcs lib$(NAME).a $(OBJECTS)
#	ranlib lib$(NAME).a  # `ar s` is same as `ranlib`

# create dependency list by examining header files that are included
depend:
	makedepend -- $(FLAGS) -- $(SOURCES) $(INCLUDES) -s'# DO NOT DELETE THIS LINE -- `makedepend` depends on it.'

# remove object files, executables, and libraries
clean:
	$(RM) ${OBJECTS}
	$(RM) ${MAIN}.o
	$(RM) ${NAME}
	$(RM) lib${NAME}.a

# DO NOT DELETE THIS LINE -- `makedepend` depends on it.
