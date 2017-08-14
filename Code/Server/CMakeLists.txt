CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(ProjectName Utopia)
#PROJECT(ProjectName)

macro(source_group_by_dir source_file_paths)
        set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
        foreach(sgbd_file_path ${${source_file_paths}})
			string(REGEX REPLACE "${sgbd_cur_dir}/(.*)"  \\1 sgbd_relate_path ${sgbd_file_path})
			string(REGEX REPLACE "(.*)/.*"  \\1 sgbd_group_name ${sgbd_relate_path})
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
			STRING(COMPARE EQUAL ${sgbd_group_name} ${sgbd_relate_path} is_not_group)
			IF (is_not_group)
				SET(sgbd_group_name "\\")
			ENDIF(is_not_group)
            SOURCE_GROUP("${sgbd_group_name}" FILES ${sgbd_file_path})
        endforeach(sgbd_file_path)
endmacro(source_group_by_dir)

SET(search_dir ".")
FILE(GLOB_RECURSE dir_files "${search_dir}/*.cpp" "${search_dir}/*.c" "${search_dir}/*.h" "${search_dir}/*.hpp")
SET(SourceFiles ${SourceFiles} ${dir_files})
source_group_by_dir(SourceFiles) 

INCLUDE_DIRECTORIES(. ./Libs/3rdpartLibs ./Libs/OwnLibs)
ADD_EXECUTABLE(${ProjectName} ${SourceFiles})


#SET_PROPERTIES(PROPERTIES FOLDER "examples")
#LINK_LIBRARIES(event_extra event_core ws2_32 common)
#ADD_COMPILE_OPTIONS(-g -std=c++11)
#ADD_DEFINITIONS(/D _CRT_SECURE_NO_WARNINGS /wd4267 /wd4244)
#INCLUDE_DIRECTORIES(.)