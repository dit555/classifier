CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(${header})

ADD_EXECUTABLE(classify
	src/classify.cpp
	header/DataSet.h
	src/DataSet.cpp
	header/Instance.h
	src/Instance.cpp
)

