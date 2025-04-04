
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_AR ar)
set(CMAKE_RANLIB ranlib)

set(CMAKE_CXX_FLAGS  "-Wall -Wextra")

set(SRC_PATH ../../../src)

set(INCLUDE_DIRS
	${SRC_PATH}
	${GTEST_ROOT}/include
	../utils
)

set(TEST_INCLUDE_DIRS
	..
	.
)

set(SRCS
)

set(TEST_NAME template)

set(TEST_SOURCES
	${TEST_NAME}_main.cpp
	${TEST_NAME}_test.cpp
)

# testing private functions and variables #
add_definitions(-DUNIT_TESTING)

find_library(GTEST_LIB gtest PATHS ${GTEST_ROOT}/lib)
find_library(GTEST_MAIN_LIB gtest_main PATHS ${GTEST_ROOT}/lib)

add_executable(unit_test_${TEST_NAME} ${SRCS} ${TEST_SOURCES})

add_test(${TEST_NAME} unit_test_${TEST_NAME} COMMAND --gtest_color=1)
target_link_libraries(unit_test_${TEST_NAME} ${GTEST_LIB} ${GTEST_MAIN_LIB})

target_include_directories(unit_test_${TEST_NAME} PRIVATE ${INCLUDE_DIRS} ${TEST_INCLUDE_DIRS})







