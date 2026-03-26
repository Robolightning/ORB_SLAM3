## List of Known Dependencies
### ORB-SLAM3 (cross‑platform version)

This document lists all pieces of code included in ORB-SLAM3 and the libraries it links to, which are not the property of the ORB-SLAM3 authors. The project is now **cross‑platform** (Windows / Linux) and all third‑party dependencies are managed via [vcpkg](https://vcpkg.io) using the manifest file `vcpkg.json`. The dependencies listed below are installed automatically during the build process.

---

### Code in **src** and **include** folders

- **ORBextractor.cpp**  
  Modified version of `orb.cpp` from the OpenCV library. The original code is BSD licensed.

- **PnPsolver.h, PnPsolver.cpp**  
  Modified version of `epnp.h` and `epnp.cpp` by Vincent Lepetit.  
  This code can be found in popular BSD licensed computer vision libraries such as [OpenCV](https://github.com/Itseez/opencv/blob/master/modules/calib3d/src/epnp.cpp) and [OpenGV](https://github.com/laurentkneip/opengv/blob/master/src/absolute_pose/modules/Epnp.cpp). The original code is FreeBSD.

- **MLPnPsolver.h, MLPnPsolver.cpp**  
  Modified version of the MLPnP implementation by Steffen Urban (from [here](https://github.com/urbste/opengv)).  
  The original code is BSD licensed.

- Function **ORBmatcher::DescriptorDistance** in `ORBmatcher.cpp`  
  Taken from [Bit Twiddling Hacks](http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel).  
  The code is in the public domain.

---

### Third‑party libraries (managed via vcpkg)

All required libraries are installed automatically by vcpkg when building the project. The following are the main dependencies:

| Library                 | Description                                 | License                                 |
|-------------------------|---------------------------------------------|-----------------------------------------|
| **OpenCV**              | Image processing, feature extraction        | BSD                                     |
| **Eigen3**              | Linear algebra                              | MPL2 (≥3.1.1), earlier LGPLv3           |
| **Pangolin**            | Visualization and user interface            | MIT                                     |
| **Sophus**              | Lie groups for IMU processing               | MIT                                     |
| **g2o**                 | Non‑linear graph optimization               | BSD                                     |
| **DBoW2**               | Place recognition (binary bag‑of‑words)     | BSD                                     |
| **Boost**               | Serialization and other utilities           | Boost Software License 1.0              |
| **OpenSSL**             | Cryptographic hashes (MD5, etc.)            | OpenSSL / Apache 2.0                    |

---

### Notes on licensing

- **OpenCV**: BSD license.  
- **Eigen3**: For versions greater than 3.1.1 it is MPL2; earlier versions are LGPLv3.  
- **Pangolin**: MIT license.  
- **Sophus**: MIT license.  
- **g2o**: BSD license.  
- **DBoW2**: BSD license.  
- **Boost**: Boost Software License 1.0.  
- **OpenSSL**: dual‑licensed under the OpenSSL License and the SSLeay License (both BSD‑like) or Apache 2.0, depending on the version.

The use of these libraries does not affect the GPLv3 license of ORB-SLAM3 itself, as they are compatible under the terms of the GPL (the BSD, MIT, MPL2, and Boost licenses are all GPL‑compatible).

---

### ROS support (optional, Linux only)

If the ROS examples are built (using the `build_ros.sh` script), the following ROS packages are used:

- `roscpp`
- `tf`
- `sensor_msgs`
- `image_transport`
- `cv_bridge`

All are BSD licensed. ROS itself is not required for the core ORB-SLAM3 library.
