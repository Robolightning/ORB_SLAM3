cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0074 NEW)
project(ORB_SLAM3)

option(SUPPRESS_WARNINGS "Suppress all compiler warnings" OFF)

# ------------------------------------------------------------------------------
# Compiler flags
# ------------------------------------------------------------------------------
if(MSVC)
    add_definitions(-DNOMINMAX)
    if(SUPPRESS_WARNINGS)
        add_compile_options(/W0 /wd4267 /wd4244)
    else()
        add_compile_options(/W3)
    endif()
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /O2")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
    if(SUPPRESS_WARNINGS)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w -O3")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -O3")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")
    endif()
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -march=native")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native")
endif()

# ------------------------------------------------------------------------------
# Build type
# ------------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# ------------------------------------------------------------------------------
# C++17 support
# ------------------------------------------------------------------------------
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
    add_definitions(-DCOMPILEDWITHC11)
    add_compile_options(/std:c++17)
    message(STATUS "Using MSVC with C++17 flag /std:c++17.")
else()
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    add_definitions(-DCOMPILEDWITHC11)
    message(STATUS "Using C++17 standard")
endif()

# ------------------------------------------------------------------------------
# Find OpenCV
# ------------------------------------------------------------------------------
find_package(OpenCV 4.4 REQUIRED)
message(STATUS "OpenCV found: ${OpenCV_VERSION}")

# ------------------------------------------------------------------------------
# Find Eigen3
# ------------------------------------------------------------------------------
find_package(Eigen3 REQUIRED)
message(STATUS "Eigen3 found")

# ------------------------------------------------------------------------------
# Find Pangolin
# ------------------------------------------------------------------------------
find_package(Pangolin REQUIRED)
message(STATUS "Pangolin found, LIBRARIES: ${Pangolin_LIBRARIES}")

# ------------------------------------------------------------------------------
# Find Sophus
# ------------------------------------------------------------------------------
find_package(Sophus CONFIG QUIET)

if(TARGET Sophus::Sophus)
    set(ORB_SLAM3_SOPHUS_TARGET Sophus::Sophus)
    message(STATUS "Sophus found via config target: Sophus::Sophus")
else()
    # Fallback for older/non-standard installs
    find_package(sophus QUIET)
    if(TARGET sophus)
        set(ORB_SLAM3_SOPHUS_TARGET sophus)
        message(STATUS "Sophus found via fallback target: sophus")
    elseif(DEFINED sophus_DIR OR DEFINED Sophus_DIR)
        message(FATAL_ERROR "Sophus package was found, but no supported imported target was exported")
    else()
        message(FATAL_ERROR "Sophus not found. Expected Sophus::Sophus (preferred) or sophus target")
    endif()
endif()

# ------------------------------------------------------------------------------
# Find g2o
# ------------------------------------------------------------------------------
find_package(g2o CONFIG REQUIRED)
if(NOT TARGET g2o::core)
    message(FATAL_ERROR "g2o::core target not found")
endif()
message(STATUS "g2o found: using targets")

# ------------------------------------------------------------------------------
# Find Boost
# ------------------------------------------------------------------------------
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()
find_package(Boost REQUIRED COMPONENTS serialization)
if(NOT TARGET Boost::serialization)
    message(FATAL_ERROR "Boost::serialization target not found")
endif()
message(STATUS "Boost found: ${Boost_VERSION}")

# ------------------------------------------------------------------------------
# Find DBoW2
# ------------------------------------------------------------------------------
find_package(DBoW2 CONFIG REQUIRED)
if(NOT DBoW2_FOUND)
    message(FATAL_ERROR "DBoW2 library not found")
endif()

if(WIN32)
    get_filename_component(DBOW2_ROOT "${DBoW2_DIR}/../.." ABSOLUTE)
    set(DBOW2_INCLUDE_DIRS "${DBOW2_ROOT}/include/DBoW2")
    set(DBoW2_LIBRARY_DEBUG "${DBOW2_ROOT}/debug/lib/DBoW2.lib")
    set(DBoW2_LIBRARY_RELEASE "${DBOW2_ROOT}/lib/DBoW2.lib")
    set(DBOW2_LIB
        $<$<CONFIG:Debug>:${DBoW2_LIBRARY_DEBUG}>
        $<$<CONFIG:Release>:${DBoW2_LIBRARY_RELEASE}>
    )
else()
    if(TARGET DBoW2::DBoW2)
        set(DBOW2_LIB DBoW2::DBoW2)
        set(DBOW2_INCLUDE_DIRS "")
    else()
        set(DBOW2_LIB ${DBoW2_LIBRARIES})
        get_filename_component(DBOW2_ROOT "${DBoW2_DIR}/../.." ABSOLUTE)
        set(DBOW2_INCLUDE_DIRS "${DBOW2_ROOT}/include/DBoW2")
    endif()
endif()

# ------------------------------------------------------------------------------
# Find OpenSSL
# ------------------------------------------------------------------------------
find_package(OpenSSL CONFIG REQUIRED)
if(NOT TARGET OpenSSL::SSL)
    message(FATAL_ERROR "OpenSSL::SSL target not found")
endif()
message(STATUS "OpenSSL found, using targets")

# ------------------------------------------------------------------------------
# Include directories
# ------------------------------------------------------------------------------
include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/CameraModels
    ${DBOW2_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

# ------------------------------------------------------------------------------
# Build ORB_SLAM3 library
# ------------------------------------------------------------------------------
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_library(${PROJECT_NAME} STATIC
    src/System.cpp
    src/Tracking.cpp
    src/LocalMapping.cpp
    src/LoopClosing.cpp
    src/ORBextractor.cpp
    src/ORBmatcher.cpp
    src/FrameDrawer.cpp
    src/Converter.cpp
    src/MapPoint.cpp
    src/KeyFrame.cpp
    src/Atlas.cpp
    src/Map.cpp
    src/MapDrawer.cpp
    src/Optimizer.cpp
    src/Frame.cpp
    src/KeyFrameDatabase.cpp
    src/Sim3Solver.cpp
    src/Viewer.cpp
    src/ImuTypes.cpp
    src/G2oTypes.cpp
    src/CameraModels/Pinhole.cpp
    src/CameraModels/KannalaBrandt8.cpp
    src/OptimizableTypes.cpp
    src/MLPnPsolver.cpp
    src/GeometricTools.cpp
    src/TwoViewReconstruction.cpp
    src/Config.cpp
    src/Settings.cpp
    include/System.h
    include/Tracking.h
    include/LocalMapping.h
    include/LoopClosing.h
    include/ORBextractor.h
    include/ORBmatcher.h
    include/FrameDrawer.h
    include/Converter.h
    include/MapPoint.h
    include/KeyFrame.h
    include/Atlas.h
    include/Map.h
    include/MapDrawer.h
    include/Optimizer.h
    include/Frame.h
    include/KeyFrameDatabase.h
    include/Sim3Solver.h
    include/Viewer.h
    include/ImuTypes.h
    include/G2oTypes.h
    include/CameraModels/GeometricCamera.h
    include/CameraModels/Pinhole.h
    include/CameraModels/KannalaBrandt8.h
    include/OptimizableTypes.h
    include/MLPnPsolver.h
    include/GeometricTools.h
    include/TwoViewReconstruction.h
    include/SerializationUtils.h
    include/Config.h
    include/Settings.h
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/CameraModels
)

# ------------------------------------------------------------------------------
# Link libraries
# ------------------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${OpenCV_LIBS}
        Eigen3::Eigen
        ${Pangolin_LIBRARIES}
        ${DBOW2_LIB}
        ${ORB_SLAM3_SOPHUS_TARGET}
        g2o::core
        g2o::types_sba
        g2o::types_sim3
        g2o::solver_eigen
        g2o::stuff
        OpenSSL::SSL
        OpenSSL::Crypto
        Boost::serialization
)

# ------------------------------------------------------------------------------
# Option to build examples
# ------------------------------------------------------------------------------
option(BUILD_EXAMPLES "Build ORB_SLAM3 examples" OFF)

if(BUILD_EXAMPLES)
    message(STATUS "Building examples")

    # RGB-D examples
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Examples/RGB-D)

    add_executable(rgbd_tum
            Examples/RGB-D/rgbd_tum.cpp)
    target_link_libraries(rgbd_tum ${PROJECT_NAME})

    if(realsense2_FOUND)
        add_executable(rgbd_realsense_D435i
                Examples/RGB-D/rgbd_realsense_D435i.cpp)
        target_link_libraries(rgbd_realsense_D435i ${PROJECT_NAME})
    endif()

    # RGB-D inertial examples
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Examples/RGB-D-Inertial)

    if(realsense2_FOUND)
        add_executable(rgbd_inertial_realsense_D435i
                Examples/RGB-D-Inertial/rgbd_inertial_realsense_D435i.cpp)
        target_link_libraries(rgbd_inertial_realsense_D435i ${PROJECT_NAME})
    endif()

    # Stereo examples
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Examples/Stereo)

    add_executable(stereo_kitti
            Examples/Stereo/stereo_kitti.cpp)
    target_link_libraries(stereo_kitti ${PROJECT_NAME})

    add_executable(stereo_euroc
            Examples/Stereo/stereo_euroc.cpp)
    target_link_libraries(stereo_euroc ${PROJECT_NAME})

    add_executable(stereo_tum_vi
            Examples/Stereo/stereo_tum_vi.cpp)
    target_link_libraries(stereo_tum_vi ${PROJECT_NAME})

    if(realsense2_FOUND)
        add_executable(stereo_realsense_t265
                Examples/Stereo/stereo_realsense_t265.cpp)
        target_link_libraries(stereo_realsense_t265 ${PROJECT_NAME})

        add_executable(stereo_realsense_D435i
                Examples/Stereo/stereo_realsense_D435i.cpp)
        target_link_libraries(stereo_realsense_D435i ${PROJECT_NAME})
    endif()

    # Monocular examples
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Examples/Monocular)

    add_executable(mono_tum
            Examples/Monocular/mono_tum.cpp)
    target_link_libraries(mono_tum ${PROJECT_NAME})

    add_executable(mono_kitti
            Examples/Monocular/mono_kitti.cpp)
    target_link_libraries(mono_kitti ${PROJECT_NAME})

    add_executable(mono_euroc
            Examples/Monocular/mono_euroc.cpp)
    target_link_libraries(mono_euroc ${PROJECT_NAME})

    add_executable(mono_tum_vi
            Examples/Monocular/mono_tum_vi.cpp)
    target_link_libraries(mono_tum_vi ${PROJECT_NAME})

    if(realsense2_FOUND)
        add_executable(mono_realsense_t265
                Examples/Monocular/mono_realsense_t265.cpp)
        target_link_libraries(mono_realsense_t265 ${PROJECT_NAME})

        add_executable(mono_realsense_D435i
                Examples/Monocular/mono_realsense_D435i.cpp)
        target_link_libraries(mono_realsense_D435i ${PROJECT_NAME})
    endif()

    # Monocular inertial examples
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Examples/Monocular-Inertial)

    add_executable(mono_inertial_euroc
            Examples/Monocular-Inertial/mono_inertial_euroc.cpp)
    target_link_libraries(mono_inertial_euroc ${PROJECT_NAME})

    add_executable(mono_inertial_tum_vi
            Examples/Monocular-Inertial/mono_inertial_tum_vi.cpp)
    target_link_libraries(mono_inertial_tum_vi ${PROJECT_NAME})

    if(realsense2_FOUND)
        add_executable(mono_inertial_realsense_t265
                Examples/Monocular-Inertial/mono_inertial_realsense_t265.cpp)
        target_link_libraries(mono_inertial_realsense_t265 ${PROJECT_NAME})

        add_executable(mono_inertial_realsense_D435i
                Examples/Monocular-Inertial/mono_inertial_realsense_D435i.cpp)
        target_link_libraries(mono_inertial_realsense_D435i ${PROJECT_NAME})
    endif()

    # Stereo Inertial examples
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Examples/Stereo-Inertial)

    add_executable(stereo_inertial_euroc
            Examples/Stereo-Inertial/stereo_inertial_euroc.cpp)
    target_link_libraries(stereo_inertial_euroc ${PROJECT_NAME})

    add_executable(stereo_inertial_tum_vi
            Examples/Stereo-Inertial/stereo_inertial_tum_vi.cpp)
    target_link_libraries(stereo_inertial_tum_vi ${PROJECT_NAME})

    if(realsense2_FOUND)
        add_executable(stereo_inertial_realsense_t265
                Examples/Stereo-Inertial/stereo_inertial_realsense_t265.cpp)
        target_link_libraries(stereo_inertial_realsense_t265 ${PROJECT_NAME})

        add_executable(stereo_inertial_realsense_D435i
                Examples/Stereo-Inertial/stereo_inertial_realsense_D435i.cpp)
        target_link_libraries(stereo_inertial_realsense_D435i ${PROJECT_NAME})
    endif()

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Examples/Calibration)
    if(realsense2_FOUND)
        add_executable(recorder_realsense_D435i
                Examples/Calibration/recorder_realsense_D435i.cpp)
        target_link_libraries(recorder_realsense_D435i ${PROJECT_NAME})

        add_executable(recorder_realsense_T265
                Examples/Calibration/recorder_realsense_T265.cpp)
        target_link_libraries(recorder_realsense_T265 ${PROJECT_NAME})
    endif()

    # Old examples

    # RGB-D examples
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Examples_old/RGB-D)

    add_executable(rgbd_tum_old
            Examples_old/RGB-D/rgbd_tum.cpp)
    target_link_libraries(rgbd_tum_old ${PROJECT_NAME})

    if(realsense2_FOUND)
        add_executable(rgbd_realsense_D435i_old
                Examples_old/RGB-D/rgbd_realsense_D435i.cpp)
        target_link_libraries(rgbd_realsense_D435i_old ${PROJECT_NAME})
    endif()

    # RGB-D inertial examples
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Examples_old/RGB-D-Inertial)

    if(realsense2_FOUND)
        add_executable(rgbd_inertial_realsense_D435i_old
                Examples_old/RGB-D-Inertial/rgbd_inertial_realsense_D435i.cpp)
        target_link_libraries(rgbd_inertial_realsense_D435i_old ${PROJECT_NAME})
    endif()

    # Stereo examples
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Examples_old/Stereo)

    add_executable(stereo_kitti_old
            Examples_old/Stereo/stereo_kitti.cpp)
    target_link_libraries(stereo_kitti_old ${PROJECT_NAME})

    add_executable(stereo_euroc_old
            Examples_old/Stereo/stereo_euroc.cpp)
    target_link_libraries(stereo_euroc_old ${PROJECT_NAME})

    add_executable(stereo_tum_vi_old
            Examples_old/Stereo/stereo_tum_vi.cpp)
    target_link_libraries(stereo_tum_vi_old ${PROJECT_NAME})

    if(realsense2_FOUND)
        add_executable(stereo_realsense_t265_old
                Examples_old/Stereo/stereo_realsense_t265.cpp)
        target_link_libraries(stereo_realsense_t265_old ${PROJECT_NAME})

        add_executable(stereo_realsense_D435i_old
                Examples_old/Stereo/stereo_realsense_D435i.cpp)
        target_link_libraries(stereo_realsense_D435i_old ${PROJECT_NAME})
    endif()

    # Monocular examples
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Examples_old/Monocular)

    add_executable(mono_tum_old
            Examples_old/Monocular/mono_tum.cpp)
    target_link_libraries(mono_tum_old ${PROJECT_NAME})

    add_executable(mono_kitti_old
            Examples_old/Monocular/mono_kitti.cpp)
    target_link_libraries(mono_kitti_old ${PROJECT_NAME})

    add_executable(mono_euroc_old
            Examples_old/Monocular/mono_euroc.cpp)
    target_link_libraries(mono_euroc_old ${PROJECT_NAME})

    add_executable(mono_tum_vi_old
            Examples_old/Monocular/mono_tum_vi.cpp)
    target_link_libraries(mono_tum_vi_old ${PROJECT_NAME})

    if(realsense2_FOUND)
        add_executable(mono_realsense_t265_old
                Examples_old/Monocular/mono_realsense_t265.cpp)
        target_link_libraries(mono_realsense_t265_old ${PROJECT_NAME})

        add_executable(mono_realsense_D435i_old
                Examples_old/Monocular/mono_realsense_D435i.cpp)
        target_link_libraries(mono_realsense_D435i_old ${PROJECT_NAME})
    endif()

    # Monocular inertial examples
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Examples_old/Monocular-Inertial)

    add_executable(mono_inertial_euroc_old
            Examples_old/Monocular-Inertial/mono_inertial_euroc.cpp)
    target_link_libraries(mono_inertial_euroc_old ${PROJECT_NAME})

    add_executable(mono_inertial_tum_vi_old
            Examples_old/Monocular-Inertial/mono_inertial_tum_vi.cpp)
    target_link_libraries(mono_inertial_tum_vi_old ${PROJECT_NAME})

    if(realsense2_FOUND)
        add_executable(mono_inertial_realsense_t265_old
                Examples_old/Monocular-Inertial/mono_inertial_realsense_t265.cpp)
        target_link_libraries(mono_inertial_realsense_t265_old ${PROJECT_NAME})

        add_executable(mono_inertial_realsense_D435i_old
                Examples_old/Monocular-Inertial/mono_inertial_realsense_D435i.cpp)
        target_link_libraries(mono_inertial_realsense_D435i_old ${PROJECT_NAME})
    endif()

    # Stereo Inertial examples
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Examples_old/Stereo-Inertial)

    add_executable(stereo_inertial_euroc_old
            Examples_old/Stereo-Inertial/stereo_inertial_euroc.cpp)
    target_link_libraries(stereo_inertial_euroc_old ${PROJECT_NAME})

    add_executable(stereo_inertial_tum_vi_old
            Examples_old/Stereo-Inertial/stereo_inertial_tum_vi.cpp)
    target_link_libraries(stereo_inertial_tum_vi_old ${PROJECT_NAME})

    if(realsense2_FOUND)
        add_executable(stereo_inertial_realsense_t265_old
                Examples_old/Stereo-Inertial/stereo_inertial_realsense_t265.cpp)
        target_link_libraries(stereo_inertial_realsense_t265_old ${PROJECT_NAME})

        add_executable(stereo_inertial_realsense_D435i_old
                Examples_old/Stereo-Inertial/stereo_inertial_realsense_D435i.cpp)
        target_link_libraries(stereo_inertial_realsense_D435i_old ${PROJECT_NAME})
    endif()
endif()