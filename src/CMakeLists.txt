add_library(libsdb Process.cpp)         # 使用单个源文件libsdb.cpp 创建一个名为libsdb的目标
add_library(sdb::libsdb ALIAS libsdb)  # 创建一个别名，ALIAS是一个关键字，表示接下来定义的是一个别名

set_target_properties(      #用于设置target 的属性，将编译后的默认的库名 liblibsdb. a ==> libsdb. a
    libsdb
    PROPERTIES OUTPUT_NAME sdb
)

target_compile_features(libsdb PUBLIC cxx_std_17)  # 指定编译器应当在c++17 模式下编译libsdb

target_include_directories(  #指定libsdb include 的目录，对sdb/src/include文件夹使用PRIVATE可见性，因为依赖目标不应该将其传递添加到其include目录
    libsdb
    # PRIVATE include
    # PUBLIC ${CMAKE_SOURCE_DIR}/include
    PUBLIC 
        $<INSTALL_INTERFACE:include>      # 如果用户正在访问libsdb的安装版本，则公共头文件位于相对于安装位置的include目录中
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> # 正在使用构建树中的版本（例如，如果他们链接sdb可执行文件），则应当使用源代码中的include目录
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/include 
)

include(GNUInstallDirs)
install(TARGETS libsdb
    EXPORT sdb-targets 
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install( 
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT sdb-targets 
    FILE sdb-config.cmake
    NAMESPACE sdb::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/sdb   
)