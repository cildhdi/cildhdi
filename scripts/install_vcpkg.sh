#!/usr/bin/env sh

git clone git@github.com:Microsoft/vcpkg.git
./vcpkg/bootstrap-vcpkg.sh

# install snowhouse and igloo by vcpkg
./vcpkg/vcpkg install snowhouse igloo
