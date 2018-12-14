file(GLOB_RECURSE srcs "*/*.cpp")
foreach(src ${srcs})
    sfbt(${src} ON)
endforeach()
