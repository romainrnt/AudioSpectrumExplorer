##*****************************************##
##                                         ##
##  AudioSpectrumExplorer Project          ##
##  File: <Makefile>                       ##
##  Author: romainrnt                      ##
##                                         ##
##*****************************************##

SRC		=	src/main.cpp \
			src/Exceptions.cpp	\
			src/Key_detection.cpp	\
			src/Bpm_detection.cpp

OBJ		=	$(SRC:src/%.cpp=obj/%.o)

NAME =	AudioSpectrumExplorer

CXXFLAGS = -Wall -Wextra -std=c++11 -Iinclude

LDFLAGS = -laubio

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf obj/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean clean re
