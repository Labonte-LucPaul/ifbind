#!/bin/bash -e


sudo rm -rf docker-build
mkdir -p docker-build/release
#cp -r deps docker-build/release

#docker run --rm -ti \
#  --workdir=/app \
#  --mount type=bind,source="$(pwd),target=/app" \
#  --name ifbindbuilder \
#  ifbind:builder \
#  bash
  bash -c "cd docker-build/release && cmake ../.. && cmake --build . --target ifbind -- -j 6"
