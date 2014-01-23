

# AUX_SOURCE_DIRECTORY(. _SRCS)
SET (_TSRC glist.c lpconfig.c)
# INCLUDE_DIRECTORIES(./)

ADD_EXECUTABLE(exclog_local.bin exclog_local_test.c)
ADD_DEPENDENCIES(exclog_local.bin ${LIB_LOCAL})

TARGET_LINK_LIBRARIES(exclog_local.bin ${LIB_LOCAL} pthread)

ADD_EXECUTABLE(exclog_local_server.bin exclog_local_server.c ${_TSRC})
ADD_DEPENDENCIES(exclog_local_server.bin ${LIB_LOCAL})

TARGET_LINK_LIBRARIES(exclog_local_server.bin ${LIB_LOCAL} pthread m)

# LIST (APPEND linkflags exclog m c pthread)
# TARGET_LINK_LIBRARIES(target.bin ${linkflags})
