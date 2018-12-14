file(GLOB_RECURSE cfs "*/*.c")
foreach(src ${cfs})
    sfbt(${src} OFF)
endforeach()

file(GLOB_RECURSE cppfs "*/*.cpp")
foreach(src ${cppfs})
    sfbt(${src} OFF)
endforeach()