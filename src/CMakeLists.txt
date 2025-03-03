add_library(libsdb libsdb.cpp)         # 使用单个源文件libsdb.cpp 创建一个名为libsdb的目标
add_library(sdb::libsdb ALIAS libsdb)  # 创建一个别名，ALIAS是一个关键字，表示接下来定义的是一个别名

set_target_properties(      #用于设置target 的属性，将编译后的默认的库名 liblibsdb. a ==> libsdb. a
    libsdb
    PROPERTIES OUTPUT_NAME sdb
)

target_compile_features(libsdb PUBLIC cxx_std_17)  # 指定编译器应当在c++17 模式下编译libsdb

target_include_directories(  #指定libsdb include 的目录，对sdb/src/include文件夹使用PRIVATE可见性，因为依赖目标不应该将其传递添加到其include目录
    libsdb
    PRIVATE include
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)