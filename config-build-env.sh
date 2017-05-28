#!/bin/bash

echo "What is the path to the main OIP directory on YOUR system?"
read oipdir

echo -n "" > build-config
echo "OIPDIR="${oipdir%/} >> build-config
