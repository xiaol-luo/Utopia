CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(ProjectName Utopia)
PROJECT(${ProjectName}) 

FUNCTION(SourceGroupByDir base_path file_paths prefix_source_group)
	FOREACH (file_path ${file_paths})
		STRING(REGEX REPLACE "${base_path}/(.*)" \\1 relate_path ${file_path})
		STRING(REGEX REPLACE "(.*)/.*" \\1 group_name ${relate_path})
		STRING(COMPARE EQUAL ${group_name} ${relate_path} is_no_group)
		IF (is_no_group)
			SET(group_name "\\")
		ENDIF(is_no_group)
		string(REPLACE "/"  "\\" group_name "${group_name}")
		SOURCE_GROUP("${prefix_source_group}\\${group_name}" FILES ${file_path})
	ENDFOREACH(file_path ${file_paths})
ENDFUNCTION(SourceGroupByDir)

SET(Cpp_File_Pattern "*.hpp" "*.cpp" "*.h" "*.c")

FUNCTION(FileGlobRecurse search_dir file_patterns out_files)
	FOREACH (file_pattern ${file_patterns})
		FILE(GLOB_RECURSE tmp_files "${search_dir}/${file_pattern}")
		SET(all_files ${all_files} ${tmp_files})
	ENDFOREACH(file_pattern ${file_patterns})
	SET(${out_files} ${all_files} PARENT_SCOPE)
ENDFUNCTION(FileGlobRecurse)


FileGlobRecurse(${CMAKE_CURRENT_SOURCE_DIR} "${Cpp_File_Pattern}" dir_files)
SET(SourceFiles ${SourceFiles} ${dir_files})
SourceGroupByDir(${CMAKE_CURRENT_SOURCE_DIR} "${dir_files}" "")


INCLUDE_DIRECTORIES(. ./Libs/3rdpartLibs ./Libs/OwnLibs ./Libs/3rdpartLibs/Libevent ./Libs/3rdpartLibs/protobuf/include)
INCLUDE_DIRECTORIES(./Logic ./Logic/ShareCode ./Logic/ShareCode/Config/AutoCsvCode ./Logic/LogicModules)
IF (WIN32)
	LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/Libs/3rdpartLibs/Libevent/win-libs ${CMAKE_CURRENT_SOURCE_DIR}/Libs/3rdpartLibs/protobuf/win-libs)
ELSE ()
ENDIF (WIN32)
LINK_LIBRARIES(event event_core event_extra)
LINK_LIBRARIES(libprotocd libprotobufd) 

ADD_EXECUTABLE(${ProjectName} ${SourceFiles})
ADD_DEFINITIONS(/D _CRT_SECURE_NO_WARNINGS /wd4267 /wd4244 /wd4996 /D _WINSOCK_DEPRECATED_NO_WARNINGS)
ADD_COMPILE_OPTIONS(-g -std=c++11)

#SET_PROPERTIES(PROPERTIES FOLDER "examples")


