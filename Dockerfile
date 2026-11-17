FROM ubuntu:22.04
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates git build-essential cmake autoconf libtool pkg-config \
    unzip zip python3 \
 && update-ca-certificates

WORKDIR /tmp
RUN git clone --recurse-submodules -b v1.74.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc

WORKDIR /tmp/grpc/cmake/build
RUN cmake -DgRPC_INSTALL=ON \
          -DgRPC_BUILD_TESTS=OFF \
          -DgRPC_ABSL_PROVIDER=module \
          -DgRPC_PROTOBUF_PROVIDER=module \
          -DgRPC_SSL_PROVIDER=module \
          -DgRPC_ZLIB_PROVIDER=module \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_INSTALL_PREFIX=/usr/local \
          ../.. \
 && make -j 4 \
 && make install

RUN printf "/usr/local/lib\n" > /etc/ld.so.conf.d/usr-local.conf && ldconfig
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/grpc

WORKDIR /workspace
CMD ["/bin/bash"]