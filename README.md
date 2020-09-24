# test dramsim behavior

- main source code: /test
- dependecies:
/fmt
/Catch2
/DRAMsim3


## init
```
git clone https://github.com/shenjiangqiu/dramsim_test.git --recursive
```
or
```
git clone https://github.com/shenjiangqiu/dramsim_test.git

git submodule update --init --recursive
```
## build
```
mkdir build;
cd build;
cmake .. && make -j
```
## run
```
cd build/test;
ln -sf ../../DRAMsim3/config ./;
./test
```