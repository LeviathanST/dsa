#!/bin/bash

usage () {
    echo "Command error: $1"
    echo "./test.sh [-flags]"
    echo "Flags:"
    echo "---"
    echo "-t <lib>                test <lib>"
    echo "-b <lib>                benchmark <lib>"
    echo "-d <lib>                debug <lib>"
}

run () {
    if [[ "$1" -ne "-t" || "$1" -ne "-b" || "$1" -ne "-d" || ! -n "$1" ]]; then
        usage "Flag is empty"
    fi

    case $1 in
        "-t")
            gcc ./tests/test_$2.c ./src/$2.c -Wall -Wextra -o out
            ./out
            rm ./out
            ;;
        "-b")
            gcc ./benchmark/bench_$2.c ./src/$2.c -Wall -Wextra -o bench 
            ./bench
            rm ./bench
            ;;
        "-d")
            gcc ./tests/test_$2.c ./src/$2.c -Wall -Wextra -g -o out
            ;;
    esac
}

run "$@"
