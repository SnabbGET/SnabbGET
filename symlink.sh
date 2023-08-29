#!/bin/bash

folder=./include

ls -d1 $folder/**/* | while read -r f; do
  ln -sf "$(cat $f)" "$f"
done
