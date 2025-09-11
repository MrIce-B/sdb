cmake command 
```
rm -rf build && mkdir build  && cd build/
cmake .. -DCMAKE_TOOLCHAIN_FILE=/home/wwd/code/vcpkg/scripts/buildsystems/vcpkg.cmake && make -j && cd ../

```