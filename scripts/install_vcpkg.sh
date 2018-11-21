#!/usr/bin/env sh

git clone https://github.com/Microsoft/vcpkg.git
./vcpkg/bootstrap-vcpkg.sh

# install snowhouse and igloo by vcpkg
./vcpkg/vcpkg install snowhouse igloo
