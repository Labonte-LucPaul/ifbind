#!/bin/bash -e


rm -rf docker-build
mkdir -p docker-build/release

docker run --rm \
  --workdir=/app \
  --mount type=bind,source="$(pwd),target=/app" \
  --name finbindbuilder \
  ifbind:builder \
  cd docker-build/release && cmake ../.. && cmake --build . --target ifbind -- -j 6
