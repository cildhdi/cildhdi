#!/usr/bin/env sh

git clone https://github.com/joakimkarlsson/igloo.git
git clone https://github.com/banditcpp/snowhouse.git "igloo/igloo/external/snowhouse"
# install snowhouse and igloo

sudo cp -a igloo/igloo /usr/include/