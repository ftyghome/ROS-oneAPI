# ROS - oneAPI

![title](image/title.png)

**A ROS package that brings intel's oneAPI to the ROS framework.**

This repository provides an example of **vector summation** on ROS using the Intel oneAPI framework. With oneAPI, the summation operation can be run parallelly on CPUs, GPUs and even Intel FPGA devices.

## Getting started

1. Install Intel oneAPI HPC Toolkit following the instructions [here](https://www.intel.com/content/www/us/en/developer/tools/oneapi/hpc-toolkit-download.html).

2. Set up the oneAPI Toolkit properly (You may need to do this on each different shell instance.)

   ```bash
    source /opt/intel/oneapi/setvars.sh
   ```

3. Clone this repository and place it in the "src" folder under your ROS workspace.

   ```bash
   mkdir -p ~/catkin_ws/src && cd ~/catkin_ws/src
   git clone https://github.com/ftyghome/ros-oneapi
   cd ..
   catkin_make
   ```

## Testing

1. Make our workspace available on the current terminal.

   ```bash
   source ~/catkin_ws/devel/setup.bash
   ```

2. Run roscore on a separate shell

   ```bash
   roscore
   ```

3. Start the oneAPI node

   ```bash
   rosrun ros_oneapi vec_add_node
   ```

   After doing this, a message similar to the following one should be displayed on the terminal.

   > [ INFO] [1643793087.304878300]: Vector add example node started.
   > [ INFO] [1643793087.305051700]: oneAPI running on device: Intel(R) Core(TM) i7-9750H CPU @ 2.60GHz

   The device is selected automatically based on the oneAPI's default device selector. You can modify the selector manually.

4. Now we can test our service by using the rosservice tool. Open another terminal and execute the following command.

   ```bash
   rosservice call /ros_oneapi/vec_add '{a: {data: [1, 2, 3, 4, 5]},b: {data: [6, 7, 8, 9, 10]}}'
   ```

   Then you should get the following results.

   > sum:
   >   layout:
   >     dim: []
   >     data_offset: 0
   >   data: [7, 9, 11, 13, 15]

   The "data" field indicates the sum of two inputs. It is calculated using the Intel oneAPI platform.

## Principle of Implementation

The Intel oneAPI is strongly dependent on Intel's LLVM-based implementation of the icx compiler. However, ROS uses its official build system called catkin and it is intended to be built on the GNU C++ Compiler. So we decompose the whole package into oneAPI related part and ROS related part. the oneapi_prog folder contains everything needed to build the oneAPI related library. By linking the library, the ROS related part is  able to use functions provided by the library. Isolating these two parts eliminated the need using LLVM to compile ROS packages or using g++ to compile oneAPI code.
