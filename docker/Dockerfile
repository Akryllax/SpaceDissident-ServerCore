FROM ubuntu:20.04

VOLUME "/workspace"
WORKDIR "/workspace"

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install cmake clang wget git -y

# RUN update-alternatives --install /usr/bin/clang clang /usr/bin/clang-3 100 \
#     --slave /usr/bin/clang++ clang++ /usr/bin/clang++-3.10 \
#     --slave /usr/bin/clang-check clang-check /usr/bin/clang-check-3.10 \
#     --slave /usr/bin/clang-query clang-query /usr/bin/clang-query-3.10 \
#     --slave /usr/bin/clang-rename clang-rename /usr/bin/clang-rename-3.10 \
#     --slave /usr/bin/clang-tblgen clang-tblgen /usr/bin/clang-tblgen-3.10

COPY ./cmake_toolchains/clang.cmake /clang.cmake
COPY ./cmake_caller.sh /clang_caller.sh

RUN chmod +x /clang_caller.sh

# ENTRYPOINT "exec /clang_caller.sh -DCMAKE_TOOLCHAIN_FILE=/clang.cmake"
ENTRYPOINT /clang_caller.sh

