CMAKE_MINIMUM_REQUIRED(VERSION 3.9 FATAL_ERROR)

SET(CMAKE_DEBUG_POSTFIX "_d" CACHE STRING "Add a postfix, usually _d on windows")
SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "Add a postfix, usually empty on windows")
SET(CMAKE_RELWITHDEBINFO_POSTFIX "" CACHE STRING "Add a postfix, usually empty on windows")
SET(CMAKE_MINSIZEREL_POSTFIX "" CACHE STRING "Add a postfix, usually empty on windows")

FUNCTION(ADD_POST_BUILD TARGET_NAME SUBFOLDER)
	IF(SUBFOLDER STREQUAL "")
		SET(TARGET_FOLDER ${LOO_BIN_DIR})
	ELSE()
		SET(TARGET_FOLDER ${LOO_BIN_DIR}/${SUBFOLDER})
	ENDIF()

	ADD_CUSTOM_COMMAND(TARGET ${TARGET_NAME}
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE_DIR:${TARGET_NAME}>/$<TARGET_FILE_NAME:${TARGET_NAME}> ${TARGET_FOLDER})
ENDFUNCTION()


FUNCTION(DOWNLOAD_FILE RELATIVE_PATH COMMIT_ID FILE_ID)
	SET(DEST ${LOO_ROOT_DIR}/${RELATIVE_PATH})
	SET(REDOWNLOAD FALSE)
	IF(EXISTS ${DEST})
	ELSE()
		SET(REDOWNLOAD TRUE)
	ENDIF()
	IF(REDOWNLOAD)
	#https://raw.githubusercontent.com/ifeuille/loodependencies/master/README.md
		SET(URL "https://raw.githubusercontent.com/ifeuille/loodependencies/${COMMIT_ID}/${RELATIVE_PATH}")
		MESSAGE(STATUS "Downloading ${URL}...")
		FILE(DOWNLOAD ${URL} ${DEST} SHOW_PROGRESS EXPECTED_HASH SHA1=${FILE_ID} STATUS ERR)
		LIST(GET ERR 0 ERR_CODE)
		IF(ERR_CODE)
			FILE(REMOVE ${DEST})
			LIST(GET ERR 1 ERR_MSG)
			MESSAGE(FATAL_ERROR "Failed to download file ${URL}: ${ERR_MSG}")
		ENDIF()
	ENDIF()
	SET(${ARGV3} ${REDOWNLOAD} PARENT_SCOPE)
ENDFUNCTION()
