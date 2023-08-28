#!/bin/bash

folder=./include

ls -d1 $folder/**/* | while read f; do
  ln -sf "$(cat $f)" "$f"
done
