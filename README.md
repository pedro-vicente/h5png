# h5png
Convert HDF5 image format to PNG format

Dependencies
------------

[HDF5](http://www.hdfgroup.org)
HDF5 is a set of software libraries and self-describing, 
machine-independent data format that support the creation, 
access, and sharing of array-oriented scientific data.
<br /> 
HDF5 images are simply HDF5 datasets with some metadata (attributes) that identify the dataset as an image. 
The HDF5 image specification allows for the dataset datum to be of any HDF5 integer or float type, but currently only the unsigned char type is defined.
Two types of images are defined in the specification and implemented, both for the RGB color model:
<ul>
<li>Indexed images</li>
<li>True color images</li>
</ul>
The true color images are 24 bit color depth with the storage being either pixel interlacing or plane interlacing.
In the current version, h5png only converts a 24 bit true color image with pixel interlacing to a PNG image.
<br /> 

[PNG](http://www.libpng.org)
Portable Network Graphics (PNG, pronounced "ping") is a raster graphics file format that supports full-color 24bit RGB images.
<br /> 

Building from source
------------

Install dependency packages: Debian-based systems (like Ubuntu)
<pre>
sudo apt-get install build-essential
sudo apt-get install libhdf5-serial-dev
sudo apt-get install libpng-dev
sudo apt-get install zlib1g-dev
</pre>

Install dependency packages: For RPM-based systems (like Fedora and CentOS)
<pre>
sudo yum install zlib-devel
sudo yum install hdf5 hdf5-devel
sudo yum install libpng
</pre>

Get source:
<pre>
git clone https://github.com/pedro-vicente/h5png.git
</pre>

Build with:
<pre>
make -f makefile
make -f makefile test
</pre>

Building with CMake in Unix
------------
On most Unix systems, the png, hdf5, zlib, szip libraries are found on the default location with
<pre>
cd build
cmake ..
</pre>

CMake build options
------------
If the png, hdf5, zlib, szip libraries are not found on the default location, they can be set. 
<pre>
cmake .. \
-DPNG_INCLUDE:PATH=/your/png/include/path \
-DHDF5_INCLUDE:PATH=/your/hdf5/include/path \
-DHDF5_HL_INCLUDE:PATH=/your/hdf5 high level/include/path \
-DPNG_LIBRARY=/your/png/library/file/name \
-DHDF5_LIBRARY=/your/hdf5/library/file/name \
-DHDF5_HL_LIBRARY=/your/hdf5 high level/library/file/name \
-DZLIB_LIBRARY=/your/zlib/library/file/name \
-DSZIP_LIBRARY=/your/szlib/library/file/name
</pre>

For a Windows Visual Studio build a statically build runtime library can be set with. 
<pre>
cmake .. -DSTATIC_CRT:BOOL=ON
</pre>


Documentation
------------
[h5png](http://www.space-research.org/blog/blog.html)

