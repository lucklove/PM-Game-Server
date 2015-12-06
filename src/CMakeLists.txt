SET(POCKET_MONSTER_SRCS
    main.cc
)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/3rdparty/inc)
LINK_DIRECTORIES(/usr/local/lib64)
ADD_EXECUTABLE(pocket_monster ${POCKET_MONSTER_SRCS})
TARGET_LINK_LIBRARIES(pocket_monster boost_system pthread redox ev hiredis)
