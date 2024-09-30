FROM docker.io/ubuntu:noble

RUN apt-get update && \
    apt-get install -y --no-install-recommends clang cmake ninja-build pkg-config freeglut3-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY ./helper/glut.pc /usr/lib/pkgconfig/glut.pc

RUN sed -i "s/^Version:.*/$(dpkg -s freeglut3 | grep -i version)/" /usr/lib/pkgconfig/glut.pc
