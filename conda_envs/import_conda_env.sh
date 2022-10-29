#!/usr/bin/env bash

param_num=$#

if [ $param_num -ne 1 ]; then
	echo "Usage: ./import_conda_env.sh <conda-env-name>"
else
	env_name="$1"
	conda env create -n $env_name --file env_${env_name}.yml
fi
