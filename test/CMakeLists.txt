SET(TEST_SOURCES
	test.cc
)

SET(REDIS_TEST_SOURCES
	test.cc
    redis_test.cc
)

INCLUDE_DIRECTORIES(../inc)
LINK_DIRECTORIES(/usr/local/lib64)

ADD_EXECUTABLE(pocket_monster_test ${TEST_SOURCES})
TARGET_LINK_LIBRARIES(pocket_monster_test boost_system)

ADD_EXECUTABLE(redis_test ${REDIS_TEST_SOURCES})
TARGET_LINK_LIBRARIES(redis_test redox ev hiredis)

ADD_CUSTOM_TARGET(run_test COMMAND ${CMAKE_BINARY_DIR}/test/pocket_monster_test DEPENDS pocket_monster_test WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
ADD_CUSTOM_TARGET(run_redis_test COMMAND ${CMAKE_BINARY_DIR}/test/redis_test DEPENDS redis_test WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
