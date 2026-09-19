cmake_minimum_required(VERSION 3.20)

project(StykLexicon
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

add_executable(StykLexicon_main
	src/main.cpp
	# src/headertest.cpp

	# src/lex/lexer.cpp
)

target_include_directories(StykLexicon_main PRIVATE
	${PROJECT_SOURCE_DIR}/include
)
