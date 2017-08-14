CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(ProjectName Utopia)
#PROJECT(ProjectName)

SET(SourceFiles_Main 
	main.cpp
)
SOURCE_GROUP("" FILES ${SourceFiles_Main})

SET(SourceFiles
	${SourceFiles_Main}
)

ADD_EXECUTABLE(${ProjectName} ${SourceFiles})
#SET_PROPERTIES(PROPERTIES FOLDER "examples")
#LINK_LIBRARIES(event_extra event_core ws2_32 common)
#ADD_COMPILE_OPTIONS(-g -std=c++11)
#ADD_DEFINITIONS(/D _CRT_SECURE_NO_WARNINGS /wd4267 /wd4244)
#INCLUDE_DIRECTORIES(.)