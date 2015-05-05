#!/bin/bash

shopt -q globstar
if [ $? -eq 0 ] ; then
    $1
else
    shopt -s globstar
    $1
    shopt -u globstar          
fi
