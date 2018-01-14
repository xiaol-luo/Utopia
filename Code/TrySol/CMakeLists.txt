CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

include (Utils.cmake)

SET(ProjectName TrySol)
PROJECT(${ProjectName})

SET(Cpp_File_Pattern "*.hpp" "*.cpp" "*.h" "*.c")
FileGlobRecurse(${CMAKE_CURRENT_SOURCE_DIR} "${Cpp_File_Pattern}" dir_files)
SET(SourceFiles ${SourceFiles} ${dir_files})
FileGroupByDir(${CMAKE_CURRENT_SOURCE_DIR} "${dir_files}" "")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../Server/Libs/3rdpartLibs/lua)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../Server/Libs/3rdpartLibs/sol)

IF (WIN32)
	LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../Tools/MakeLinks/Libs/win/Server/lua)
	ADD_DEFINITIONS(/D NOMINMAX)
ELSE ()
	
ENDIF (WIN32)

LINK_LIBRARIES(liblua) 

ADD_EXECUTABLE(${ProjectName} ${SourceFiles})
ADD_DEFINITIONS(/D _CRT_SECURE_NO_WARNINGS /wd4267 /wd4244 /wd4996 /wd4800 /D _WINSOCK_DEPRECATED_NO_WARNINGS)
ADD_COMPILE_OPTIONS(-g -std=c++11)

#SET_PROPERTIES(PROPERTIES FOLDER "examples")


