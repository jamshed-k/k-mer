
set(PROJECT_SRC
        main.cpp)


add_library(core STATIC ${PROJECT_SRC})

target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_compile_options(core PRIVATE ${WARNING_FLAGS})


add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE core)

target_compile_options(${PROJECT_NAME} PRIVATE ${WARNING_FLAGS})


set(DEFAULT_INSTALL_DIR ${CMAKE_SOURCE_DIR}/bin)
set(INSTALL_DIR .)
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(INSTALL_DIR ${DEFAULT_INSTALL_DIR})
endif()

install(TARGETS ${PROJECT_NAME}
        DESTINATION ${INSTALL_DIR}
        )
