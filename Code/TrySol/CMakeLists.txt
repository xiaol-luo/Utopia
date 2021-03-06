﻿CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

include (Utils.cmake)

SET(ProjectName TrySol)
PROJECT(${ProjectName})

SET(Cpp_File_Pattern "*.hpp" "*.cpp" "*.h" "*.c" "*.cc")
FileGlobRecurse(${CMAKE_CURRENT_SOURCE_DIR} "${Cpp_File_Pattern}" dir_files)
SET(SourceFiles ${SourceFiles} ${dir_files})
FileGroupByDir(${CMAKE_CURRENT_SOURCE_DIR} "${dir_files}" "")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../Server/Libs/3rdpartLibs/lua/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../Server/Libs/3rdpartLibs/sol)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../Server/Libs/3rdpartLibs/protobuf/include)

SET(LRDB_Parent_Dir ${CMAKE_CURRENT_SOURCE_DIR}/../../ExternalCode)
INCLUDE_DIRECTORIES(${LRDB_Parent_Dir}/LRDB/include)
INCLUDE_DIRECTORIES(${LRDB_Parent_Dir}/LRDB/third_party/asio/asio/include)
INCLUDE_DIRECTORIES(${LRDB_Parent_Dir}/LRDB/third_party/picojson)

IF (WIN32)
	LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../Tools/MakeLinks/Libs/win/Server/lua/libs)
	LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../Tools/MakeLinks/Libs/win/Server/protobuf/libs)
	ADD_DEFINITIONS(/D NOMINMAX)
	ADD_DEFINITIONS(/D _WIN32_WINNT=0x0601) #LRDB define  
ELSE ()
	
ENDIF (WIN32)

LINK_LIBRARIES(libprotocd libprotobufd liblua) 

ADD_EXECUTABLE(${ProjectName} ${SourceFiles})
ADD_DEFINITIONS(/D _CRT_SECURE_NO_WARNINGS /wd4267 /wd4244 /wd4996 /wd4800 /D _WINSOCK_DEPRECATED_NO_WARNINGS)
ADD_DEFINITIONS(/D SOL_NO_EXCEPTIONS /D SOL_CHECK_ARGUMENTS) #Sol define  

ADD_COMPILE_OPTIONS(-g -std=c++14)

#SET_PROPERTIES(PROPERTIES FOLDER "examples")



