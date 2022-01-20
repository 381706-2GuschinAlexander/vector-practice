file(GLOB hdrs "*.h")
file(GLOB srcs "*.cpp")

add_library(${mlib} STATIC ${hdrs} ${srcs})