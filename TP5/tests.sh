#!/usr/bin/env bash

for folder in tests/*/; do
    echo "=== ${folder%/} ==="

    for file in "$folder"*; do
        [ -f "$file" ] || continue

        ./bin/test_terrain "$file" >/dev/null 2>&1
        status=$?

        if [[ "$folder" == "tests/valid/" ]]; then
            expected=0
        else
            expected=1
        fi

        if { [ "$expected" -eq 0 ] && [ "$status" -eq 0 ]; } ||
           { [ "$expected" -eq 1 ] && [ "$status" -ne 0 ]; }; then
            echo "PASS: $(basename "$file")"
        else
            echo "FAIL: $(basename "$file")"
        fi
    done
done

