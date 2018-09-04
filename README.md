# uWSProto
&ensp;&ensp;uWebSockets communicate with server in protobuffer data   
&ensp;&ensp;IDE： QtCreator

# install uWebSockets
```
cd $YOURWORKSPACE   
git clone https://github.com/uNetworking/uWebSockets.git  
cd uWebSockets   
make  
sudo make install  
```
&ensp;&ensp;more information please refer https://github.com/uNetworking/uWebSockets.git    

# install protobuf
```
$ git clone https://github.com/protocolbuffers/protobuf.git
$ cd protobuf
$ git submodule update --init --recursive
$ ./autogen.sh
```
```
$ ./configure
$ make
$ make check
$ sudo make install
$ sudo ldconfig # refresh shared library cache.
```
&ensp;&ensp;more information please refer https://github.com/protocolbuffers/protobuf.git    

