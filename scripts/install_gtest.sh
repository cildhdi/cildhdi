git clone https://github.com/google/googletest.git
cd googletest
cd googletest
mkdir mybuild
cd mybuild
cmake .. -DCMAKE_CXX_FLAGS=-std=c++11
make
sudo cp lib/lib* /usr/lib/
cd ..
sudo cp -a include/gtest /usr/include/
cd ..
rm -rf googletest