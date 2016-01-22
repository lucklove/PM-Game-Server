SET(TEST_SOURCES
	test.cc
    combination.cc
    battle.cc
    storage.cc
    aioi_db.cc
    cereal.cc
    monster_memory_test.cc
    lock_free_stack.cc
    lock_free_queue.cc
    ../src/script/ClassRegister.cc
    ../src/script/FunctionRegister.cc
)

SET(REDIS_TEST_SOURCES
	test.cc
    redis_test.cc
    monster_cache_test.cc
    ../src/script/ClassRegister.cc
    ../src/script/FunctionRegister.cc
)

SET(MYSQL_TEST_SOURCES
	test.cc
    monster_persistent_test.cc
    skill_storage_test.cc
    ../src/script/ClassRegister.cc
    ../src/script/FunctionRegister.cc
)

SET(LINK_LIBS
    boost_system
    redox
    ev 
    hiredis
    soci_core 
    soci_mysql
    lua
    atomic
    pthread
)

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/3rdparty/inc
    /usr/include/mysql
)
LINK_DIRECTORIES(/usr/local/lib64)

ADD_EXECUTABLE(pocket_monster_test ${TEST_SOURCES})
TARGET_LINK_LIBRARIES(pocket_monster_test ${LINK_LIBS})

ADD_EXECUTABLE(redis_test ${REDIS_TEST_SOURCES})
TARGET_LINK_LIBRARIES(redis_test ${LINK_LIBS})

ADD_EXECUTABLE(mysql_test ${MYSQL_TEST_SOURCES})
TARGET_LINK_LIBRARIES(mysql_test ${LINK_LIBS})

ADD_CUSTOM_TARGET(run_test COMMAND ${CMAKE_BINARY_DIR}/test/pocket_monster_test DEPENDS pocket_monster_test WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
ADD_CUSTOM_TARGET(run_redis_test COMMAND ${CMAKE_BINARY_DIR}/test/redis_test DEPENDS redis_test WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
ADD_CUSTOM_TARGET(run_mysql_test COMMAND ${CMAKE_BINARY_DIR}/test/mysql_test DEPENDS mysql_test WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
