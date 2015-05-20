
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/../include
)

#AUX_SOURCE_DIRECTORY(. SRC_LIST)
SET(SRC_LIST birthday.c) 
ADD_EXECUTABLE(uhash ${SRC_LIST})

IF(WIN32)
    IF(MSVC)
    ELSE(MSVC)
    ENDIF(MSVC)
ELSE(WIN32)
    FIND_LIBRARY(libhash_core "hash-core")
    FIND_LIBRARY(libhash_src "hash-src")
ENDIF(WIN32)
IF(NOT libhash_core MATCHES libhash_core-NOTFOUND)
    TARGET_LINK_LIBRARIES(uhash ${libhash_core})
ENDIF()
IF(NOT libhash_src MATCHES libhash_src-NOTFOUND)
    TARGET_LINK_LIBRARIES(uhash ${libhash_src})
ENDIF()

INSTALL(
    TARGETS uhash 
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)

INSTALL(
    FILES ${PROJECT_SOURCE_DIR}/uhash/BIRTHDAY.DAT
    DESTINATION ${CMAKE_INSTALL_PREFIX}/utility/uhash/
)
