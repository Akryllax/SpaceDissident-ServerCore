#!/bin/bash

export REPO_DIR=$(pwd)
export COMPILE_THREADS_N=8

bash --rcfile <(echo '. ~/.bashrc; . ./.bashrc_extra')
