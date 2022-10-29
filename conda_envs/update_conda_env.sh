#!/usr/bin/env bash

param_num=$#

if [ $param_num -ne 1 ]; then
	echo "Usage: ./update_conda_env.sh <conda-env-name>"
else
	env_name="$1"
	conda env update -n $env_name --file env_${env_name}.yml --prune
fi
