#!/bin/bash

export REPO_DIR=$(git rev-parse --show-toplevel)
export COMPILE_THREADS_N=8

bash --rcfile <(echo '. ~/.bashrc; . ./.bashrc_extra')
