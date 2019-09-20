Introduction  
============  
This project is to cluser files based on names using K-means and Jaro-Winkler algorithms. The program has been tested on **Ubuntu 16.04**  
  

Prerequisites  
==============  

1. CMake - See the reference   
2. C++11 dev tools  
```
    $ sudo apt install build-essential  
```  
3. Boost  
```  
    $ sudo apt-get install libboost-all-dev  
```  
  
  
Build and execute  
=================
  
```
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make 

    // Run K-Means clustering with JaroWinkler distance algorithm
    $ ./filecluster -f ../data/filelist.txt -o ../result/K3_iter200_result.txt -k 3 -i 200
```
  
Modification in K-means algorithm  
=================================  
It is hard to find a mean value among characters. Therefore, **the most frequenctly appeared character** in each sequence of file names is used as mean values instead.   

Hyperparameters
=================

```  
    // Resampling centeroids in line 5 in kmeans.hpp  
    const size_t RESAMPLING_ITER = 25;  

    // difference threshold to stop k-means process in line 8 in kmeans.hpp 
    const double DIFF_THRESHOLD = 0.01;
```  

Reference  
==========  
[How to install CMake on Ubuntu 16.04](https://peshmerge.io/how-to-install-cmake-3-11-0-on-ubuntu-16-04/)  
[K-means cluster in Python, C++, etc](http://www.goldsborough.me/c++/python/cuda/2017/09/10/20-32-46-exploring_k-means_in_python,_c++_and_cuda/)  
[Random selection from a STL container](https://stackoverflow.com/questions/6942273/how-to-get-a-random-element-from-a-c-container)  
[Jaro-Winkler algorithm](https://github.com/TriviaMarketing/Jaro-Winkler)  