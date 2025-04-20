#!/bin/bash

mkdir -p ../traceinput

TRACE_URLS=(
    "https://jhucsf.github.io/fall2022/assign/assign03/gcc.trace"
    "https://jhucsf.github.io/fall2022/assign/assign03/read01.trace"
    "https://jhucsf.github.io/fall2022/assign/assign03/read02.trace"
    "https://jhucsf.github.io/fall2022/assign/assign03/read03.trace"
    "https://jhucsf.github.io/fall2022/assign/assign03/swim.trace"
    "https://jhucsf.github.io/fall2022/assign/assign03/write01.trace"
    "https://jhucsf.github.io/fall2022/assign/assign03/write02.trace"
)
for url in "${TRACE_URLS[@]}"; do
    filename=$(basename "$url")
    echo "Downloading $filename..."
    wget -q "$url" -O "../traceinput/$filename"
    if [ $? -eq 0 ]; then
        echo "Successfully downloaded $filename"
    else
        echo "Failed to download $filename"
    fi
done

echo "Completed downloading traces"