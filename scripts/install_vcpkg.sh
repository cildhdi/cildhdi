#!/usr/bin/env sh

sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
sudo apt-get update -y
sudo apt-get install g++-7 -y

git clone https://github.com/Microsoft/vcpkg.git
./vcpkg/bootstrap-vcpkg.sh

# install snowhouse and igloo by vcpkg
./vcpkg/vcpkg install snowhouse igloo
