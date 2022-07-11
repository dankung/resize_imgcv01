# resize_imgcv01
Create a simple HTTP server application that listens on port 8080 to serves a
specific function: resizing a jpeg image, in the form of base 64 encoded binary input data
to the desired target dimension. The server only needs to serve exactly single API below:

HTTP://[host_address]:8080/resize_image [POST]

Input Payload:
Content-Type: application/json
{
"input_jpeg": "[base 64 encoding of jpeg binary]",
"target_width": [target_width],
"target_height": [target_height]
}

Output Payload:
If success:
HTTP 200
Content-Type: application/json
{
"code": 200,
"message": "success",
"output_jpeg": "[base 64 encoding of output jpeg binary]"
}


If failed:
HTTP 4XX/5XX
Content-Type: application/json
{
"code": 4xx/5xx,
"Message": "[output error description here]"
}

Building OpenCV from Source on Linux ( Ubuntu 20.0 LTS )
----------------------------------------------------------------------------------------------------------------------------------
$ sudo apt update
$ wget -O opencv-4.5.5.zip https://github.com/opencv/opencv/archive/4.5.5.zip
$ unzip opencv-4.5.5.zip
----------------------------------------------------------------------------------------------------------------------------------
$ cd opencv-4.5.5
$ mkdir build
$ cd build
----------------------------------------------------------------------------------------------------------------------------------
Below command is normally used for configuration of OpenCV library build (executed from build folder):
$ cmake ../

OpenCV defaults assume "Release" build type and installation path is "/usr/local". For additional information about CMake options refer to OpenCV C++ compilation guide:

$ make
$ sudo make install

----------------------------------------------------------------------------------------------------------------------------------
Create symlink
Since OpenCV4 include file in /usr/local/include/opencv4/opencv2 . 
We create symlink:

$ sudo ln -s /usr/local/include/opencv4/opencv2 /usr/local/include/opencv2 
