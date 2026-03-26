#!/bin/bash
# build.sh – Build ORB_SLAM3 on Linux using vcpkg

set -e  # Exit on error

# Color output (optional)
GREEN='\033[0;32m'
NC='\033[0m' # No Color

echo -e "${GREEN}=== Setting up vcpkg dependencies ===${NC}"

# Check if vcpkg is installed
VCPKG_ROOT="${VCPKG_ROOT:-$HOME/vcpkg}"
if [ ! -f "$VCPKG_ROOT/vcpkg" ]; then
    echo "vcpkg not found at $VCPKG_ROOT. Please install vcpkg or set VCPKG_ROOT."
    exit 1
fi

# Install dependencies using vcpkg manifest mode (vcpkg.json must be present)
"$VCPKG_ROOT/vcpkg" install --triplet x64-linux

echo -e "${GREEN}=== Uncompressing vocabulary ===${NC}"
cd Vocabulary
tar -xf ORBvoc.txt.tar.gz
cd ..

echo -e "${GREEN}=== Configuring and building ORB_SLAM3 ===${NC}"
mkdir -p build && cd build
cmake .. \
    -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
    -DCMAKE_BUILD_TYPE=Release \
    -DSUPPRESS_WARNINGS=ON \
    -DBUILD_EXAMPLES=ON
make -j$(nproc)

echo -e "${GREEN}Build completed successfully.${NC}"