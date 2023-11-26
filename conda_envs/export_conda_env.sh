#!/usr/bin/env bash

param_num=$#

if [ $param_num -ne 1 ]; then
	echo "Usage: ./export_conda_env.sh <conda-env-name>"
else
	env_name="$1"
	conda env export -n $env_name --no-builds > env_${env_name}.yml
fi
