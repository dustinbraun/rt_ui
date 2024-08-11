set(SDL2_DIR "C:/Libs/SDL2-2.30.6/cmake") 
find_package(SDL2 REQUIRED) 


add_executable(rt_example)

target_sources(rt_example
    PRIVATE example.cpp
)

target_compile_features(rt_example PRIVATE cxx_std_17)

target_link_libraries(rt_example PUBLIC rt SDL2::SDL2 SDL2::SDL2main)
