# ORB-SLAM3 (Cross‑Platform)

### V1.0, December 22th, 2021  
**Authors:** Carlos Campos, Richard Elvira, Juan J. Gómez Rodríguez, [José M. M. Montiel](http://webdiis.unizar.es/~josemari/), [Juan D. Tardos](http://webdiis.unizar.es/~jdtardos/).

The [Changelog](https://github.com/UZ-SLAMLab/ORB_SLAM3/blob/master/Changelog.md) describes the features of each version.

ORB-SLAM3 is the first real-time SLAM library able to perform **Visual, Visual-Inertial and Multi-Map SLAM** with **monocular, stereo and RGB-D** cameras, using **pin-hole and fisheye** lens models. In all sensor configurations, ORB-SLAM3 is as robust as the best systems available in the literature, and significantly more accurate. 

We provide examples to run ORB-SLAM3 in the [EuRoC dataset](http://projects.asl.ethz.ch/datasets/doku.php?id=kmavvisualinertialdatasets) using stereo or monocular, with or without IMU, and in the [TUM-VI dataset](https://vision.in.tum.de/data/datasets/visual-inertial-dataset) using fisheye stereo or monocular, with or without IMU. Videos of some example executions can be found at [ORB-SLAM3 channel](https://www.youtube.com/channel/UCXVt-kXG6T95Z4tVaYlU80Q).

This software is based on [ORB-SLAM2](https://github.com/raulmur/ORB_SLAM2) developed by [Raul Mur-Artal](http://webdiis.unizar.es/~raulmur/), [Juan D. Tardos](http://webdiis.unizar.es/~jdtardos/), [J. M. M. Montiel](http://webdiis.unizar.es/~josemari/) and [Dorian Galvez-Lopez](http://doriangalvez.com/) ([DBoW2](https://github.com/dorian3d/DBoW2)).

<a href="https://youtu.be/HyLNq-98LRo" target="_blank"><img src="https://img.youtube.com/vi/HyLNq-98LRo/0.jpg" 
alt="ORB-SLAM3" width="240" height="180" border="10" /></a>

### Related Publications:
[ORB-SLAM3] Carlos Campos, Richard Elvira, Juan J. Gómez Rodríguez, José M. M. Montiel and Juan D. Tardós, **ORB-SLAM3: An Accurate Open-Source Library for Visual, Visual-Inertial and Multi-Map SLAM**, *IEEE Transactions on Robotics 37(6):1874-1890, Dec. 2021*. **[PDF](https://arxiv.org/abs/2007.11898)**.

[IMU-Initialization] Carlos Campos, J. M. M. Montiel and Juan D. Tardós, **Inertial-Only Optimization for Visual-Inertial Initialization**, *ICRA 2020*. **[PDF](https://arxiv.org/pdf/2003.05766.pdf)**

[ORBSLAM-Atlas] Richard Elvira, J. M. M. Montiel and Juan D. Tardós, **ORBSLAM-Atlas: a robust and accurate multi-map system**, *IROS 2019*. **[PDF](https://arxiv.org/pdf/1908.11585.pdf)**.

[ORBSLAM-VI] Raúl Mur-Artal, and Juan D. Tardós, **Visual-inertial monocular SLAM with map reuse**, IEEE Robotics and Automation Letters, vol. 2 no. 2, pp. 796-803, 2017. **[PDF](https://arxiv.org/pdf/1610.05949.pdf)**. 

[Stereo and RGB-D] Raúl Mur-Artal and Juan D. Tardós. **ORB-SLAM2: an Open-Source SLAM System for Monocular, Stereo and RGB-D Cameras**. *IEEE Transactions on Robotics,* vol. 33, no. 5, pp. 1255-1262, 2017. **[PDF](https://arxiv.org/pdf/1610.06475.pdf)**.

[Monocular] Raúl Mur-Artal, José M. M. Montiel and Juan D. Tardós. **ORB-SLAM: A Versatile and Accurate Monocular SLAM System**. *IEEE Transactions on Robotics,* vol. 31, no. 5, pp. 1147-1163, 2015. (**2015 IEEE Transactions on Robotics Best Paper Award**). **[PDF](https://arxiv.org/pdf/1502.00956.pdf)**.

[DBoW2 Place Recognition] Dorian Gálvez-López and Juan D. Tardós. **Bags of Binary Words for Fast Place Recognition in Image Sequences**. *IEEE Transactions on Robotics,* vol. 28, no. 5, pp. 1188-1197, 2012. **[PDF](http://doriangalvez.com/php/dl.php?dlp=GalvezTRO12.pdf)**

---

## 1. License
ORB-SLAM3 is released under [GPLv3 license](https://github.com/UZ-SLAMLab/ORB_SLAM3/blob/master/LICENSE). For a list of all code/library dependencies (and associated licenses), please see [Dependencies.md](https://github.com/UZ-SLAMLab/ORB_SLAM3/blob/master/Dependencies.md).

For a closed-source version of ORB-SLAM3 for commercial purposes, please contact the authors: orbslam (at) unizar (dot) es.

If you use ORB-SLAM3 in an academic work, please cite:

    @article{ORBSLAM3_TRO,
      title={{ORB-SLAM3}: An Accurate Open-Source Library for Visual, Visual-Inertial 
               and Multi-Map {SLAM}},
      author={Campos, Carlos AND Elvira, Richard AND G\´omez, Juan J. AND Montiel, 
              Jos\'e M. M. AND Tard\'os, Juan D.},
      journal={IEEE Transactions on Robotics}, 
      volume={37},
      number={6},
      pages={1874-1890},
      year={2021}
     }

---

## 2. Prerequisites
This version of ORB-SLAM3 is **cross‑platform** and has been tested on **Ubuntu 20.04/22.04** (Linux) and **Windows 10/11** (with Visual Studio 2022/2026). A powerful computer (e.g. i7) will ensure real-time performance.

### C++17 Compiler
The code requires a **C++17**‑compliant compiler (gcc ≥ 7, clang ≥ 5, or MSVC 2019/2022). The CMake scripts enforce C++17 automatically.

### vcpkg (recommended)
All third‑party dependencies are managed with [vcpkg](https://vcpkg.io).  
- Install vcpkg from https://github.com/microsoft/vcpkg.  
- Set the `VCPKG_ROOT` environment variable or keep vcpkg at a known location (e.g., `C:\vcpkg` on Windows, `~/vcpkg` on Linux).  
- The project includes a `vcpkg.json` file listing the required packages; vcpkg will automatically install them.

The required dependencies are:
- **OpenCV** (≥ 4.4) with modules `calib3d` and `highgui` (for visualisation and image processing).
- **Eigen3** (≥ 3.1)
- **Pangolin** (for visualisation)
- **Sophus** (Lie groups for IMU)
- **g2o** (non‑linear optimisation)
- **DBoW2** (place recognition)
- **Boost** (serialisation)
- **OpenSSL** (for hashing)

On Linux you may also need **Python** (for evaluation scripts) and optionally **ROS** (for ROS examples).  
On Windows, **Python** is also used for some evaluation scripts; install it separately.

---

## 3. Building ORB-SLAM3

Clone the repository:
```bash
git clone https://github.com/Robolightning/ORB_SLAM3.git ORB_SLAM3
cd ORB_SLAM3
```

### Using the provided build scripts

#### Linux (bash)
```bash
chmod +x build.sh
./build.sh
```
The script will:
- Install all dependencies via vcpkg (using the `vcpkg.json` manifest).
- Uncompress the vocabulary.
- Configure CMake with the vcpkg toolchain and build the library and examples.

#### Windows (PowerShell)
Open a **Developer Command Prompt for VS** (or PowerShell) and run:
```powershell
.\build.ps1
```
The script accepts optional parameters:
- `-VcpkgRoot <path>` – custom vcpkg location (defaults to `C:\vcpkg` or `$env:VCPKG_ROOT`).
- `-Configuration Release|Debug` – build configuration (default `Release`).
- `-SuppressWarnings` – switch to suppress compiler warnings.
- `-BuildExamples` – switch to build example executables (enabled by default).

### Manual CMake build

If you prefer to run CMake manually, follow these steps after installing dependencies via vcpkg:

```bash
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake \
         -DCMAKE_BUILD_TYPE=Release \
         -DSUPPRESS_WARNINGS=ON \
         -DBUILD_EXAMPLES=ON
make -j$(nproc)           # Linux
cmake --build . --config Release --parallel   # Windows
```

After a successful build, you will find:
- The static library `libORB_SLAM3.a` (Linux) or `ORB_SLAM3.lib` (Windows) in the `lib/` folder.
- Example executables in `Examples/` subdirectories (if `BUILD_EXAMPLES=ON`).

### Build options (CMake)
| Option              | Description                                              | Default |
|---------------------|----------------------------------------------------------|---------|
| `SUPPRESS_WARNINGS` | Disable all compiler warnings (Linux: `-w`, MSVC: `/W0`) | OFF     |
| `BUILD_EXAMPLES`    | Compile the example executables                          | OFF     |

---

## 4. Running ORB-SLAM3 with your camera

Directory `Examples` contains several demo programs and calibration files to run ORB-SLAM3 in all sensor configurations with Intel Realsense cameras T265 and D435i. To use your own camera:

1. Calibrate your camera following `Calibration_Tutorial.pdf` and write your calibration file `your_camera.yaml`.
2. Modify one of the provided demos to suit your specific camera model, and build it.
3. Connect the camera to your computer using USB3 or the appropriate interface.
4. Run ORB-SLAM3. For example, for a D435i camera:

```bash
./Examples/Stereo-Inertial/stereo_inertial_realsense_D435i Vocabulary/ORBvoc.txt ./Examples/Stereo-Inertial/RealSense_D435i.yaml
```

---

## 5. EuRoC Examples
[EuRoC dataset](http://projects.asl.ethz.ch/datasets/doku.php?id=kmavvisualinertialdatasets) was recorded with two pinhole cameras and an inertial sensor. We provide an example script to launch EuRoC sequences in all the sensor configurations.

1. Download a sequence (ASL format) from http://projects.asl.ethz.ch/datasets/doku.php?id=kmavvisualinertialdatasets.
2. Open the script `euroc_examples.sh` in the root of the project. Change `pathDatasetEuroc` variable to point to the directory where the dataset has been uncompressed. 
3. Execute the following script to process all the sequences with all sensor configurations:
```bash
./euroc_examples
```

### Evaluation
EuRoC provides ground truth for each sequence in the IMU body reference. As pure visual executions report trajectories centered in the left camera, we provide in the `evaluation` folder the transformation of the ground truth to the left camera reference. Visual-inertial trajectories use the ground truth from the dataset.

Execute the following script to process sequences and compute the RMS ATE:
```bash
./euroc_eval_examples
```

---

## 6. TUM-VI Examples
[TUM-VI dataset](https://vision.in.tum.de/data/datasets/visual-inertial-dataset) was recorded with two fisheye cameras and an inertial sensor.

1. Download a sequence from https://vision.in.tum.de/data/datasets/visual-inertial-dataset and uncompress it.
2. Open the script `tum_vi_examples.sh` in the root of the project. Change `pathDatasetTUM_VI` variable to point to the directory where the dataset has been uncompressed. 
3. Execute the following script to process all the sequences with all sensor configurations:
```bash
./tum_vi_examples
```

### Evaluation
In TUM-VI ground truth is only available in the room where all sequences start and end. As a result the error measures the drift at the end of the sequence. 

Execute the following script to process sequences and compute the RMS ATE:
```bash
./tum_vi_eval_examples
```

---

## 7. ROS Examples (Linux only)

**Note:** ROS is only supported on Linux. The ROS nodes are not built on Windows.

### Building the nodes for mono, mono-inertial, stereo, stereo-inertial and RGB-D
Tested with ROS Melodic and Ubuntu 18.04, or ROS Noetic and Ubuntu 20.04.

1. Add the path including `Examples/ROS/ORB_SLAM3` to the `ROS_PACKAGE_PATH` environment variable. Open `.bashrc`:
   ```bash
   gedit ~/.bashrc
   ```
   and add at the end the following line (replace `PATH` with the folder where you cloned ORB_SLAM3):
   ```bash
   export ROS_PACKAGE_PATH=${ROS_PACKAGE_PATH}:PATH/ORB_SLAM3/Examples/ROS
   ```

2. Execute `build_ros.sh` script:
   ```bash
   chmod +x build_ros.sh
   ./build_ros.sh
   ```

### Running Monocular Node
For a monocular input from topic `/camera/image_raw` run node ORB_SLAM3/Mono. You will need to provide the vocabulary file and a settings file. See the monocular examples above.

```bash
rosrun ORB_SLAM3 Mono PATH_TO_VOCABULARY PATH_TO_SETTINGS_FILE
```

### Running Monocular-Inertial Node
For a monocular input from topic `/camera/image_raw` and an inertial input from topic `/imu`, run node ORB_SLAM3/Mono_Inertial. Setting the optional third argument to true will apply CLAHE equalization to images (Mainly for TUM-VI dataset).

```bash
rosrun ORB_SLAM3 Mono PATH_TO_VOCABULARY PATH_TO_SETTINGS_FILE [EQUALIZATION]	
```

### Running Stereo Node
For a stereo input from topic `/camera/left/image_raw` and `/camera/right/image_raw` run node ORB_SLAM3/Stereo. You will need to provide the vocabulary file and a settings file. For Pinhole camera model, if you **provide rectification matrices** (see Examples/Stereo/EuRoC.yaml example), the node will recitify the images online, **otherwise images must be pre-rectified**. For FishEye camera model, rectification is not required since system works with original images:

```bash
rosrun ORB_SLAM3 Stereo PATH_TO_VOCABULARY PATH_TO_SETTINGS_FILE ONLINE_RECTIFICATION
```

### Running Stereo-Inertial Node
For a stereo input from topics `/camera/left/image_raw` and `/camera/right/image_raw`, and an inertial input from topic `/imu`, run node ORB_SLAM3/Stereo_Inertial. You will need to provide the vocabulary file and a settings file, including rectification matrices if required in a similar way to Stereo case:

```bash
rosrun ORB_SLAM3 Stereo_Inertial PATH_TO_VOCABULARY PATH_TO_SETTINGS_FILE ONLINE_RECTIFICATION [EQUALIZATION]	
```

### Running RGB_D Node
For an RGB-D input from topics `/camera/rgb/image_raw` and `/camera/depth_registered/image_raw`, run node ORB_SLAM3/RGBD. You will need to provide the vocabulary file and a settings file. See the RGB-D example above.

```bash
rosrun ORB_SLAM3 RGBD PATH_TO_VOCABULARY PATH_TO_SETTINGS_FILE
```

**Running ROS example:** Download a rosbag (e.g. V1_02_medium.bag) from the EuRoC dataset. Open 3 tabs on the terminal and run the following command at each tab for a Stereo-Inertial configuration:
```
roscore
```
```
rosrun ORB_SLAM3 Stereo_Inertial Vocabulary/ORBvoc.txt Examples/Stereo-Inertial/EuRoC.yaml true
```
```
rosbag play --pause V1_02_medium.bag /cam0/image_raw:=/camera/left/image_raw /cam1/image_raw:=/camera/right/image_raw /imu0:=/imu
```
Once ORB-SLAM3 has loaded the vocabulary, press space in the rosbag tab.

**Remark:** For rosbags from TUM-VI dataset, some play issue may appear due to chunk size. One possible solution is to rebag them with the default chunk size, for example:
```
rosrun rosbag fastrebag.py dataset-room1_512_16.bag dataset-room1_512_16_small_chunks.bag
```

---

## 8. Running time analysis
A flag in `include/Config.h` activates time measurements. Uncomment the line `#define REGISTER_TIMES` to obtain the time stats of one execution, which are shown at the terminal and stored in a text file (`ExecTimeMean.txt`).

---

## 9. Calibration
You can find a tutorial for visual-inertial calibration and a detailed description of the contents of valid configuration files at `Calibration_Tutorial.pdf`.
