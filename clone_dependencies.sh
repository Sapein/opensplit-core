#!/bin/bash

printf "Cloning Brad Conte's Crypto-Algoritms...\n"
git clone https://github.com/B-Con/crypto-algorithms.git opensplit-core/deps/crypto-algorithms
if [ ${?} -eq 0 ]
then
    printf "SUCCESS!\n"
else
    printf "Failure! Git exited with non-zero exit state: ${?}\n"
fi
