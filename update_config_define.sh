#!/bin/bash

# Apply all changes from config.h to config.def.h


run() {

	software=$1;
	dir=$HOME/.config/suckless/$software

	if [ ! -d $dir ]; then
		echo "Suckless $software wasn't found at $dir"
		return
	fi

	config_h_file="$dir/config.h";
	config_def_h_file="$dir/config.def.h";

	if [ ! -f $config_h_file ]; then
		echo "$config_h_file not found"
		return;
	fi

	if [ ! -f $config_def_h_file ]; then
		echo "$config_def_h_file not found"
		return;
	fi

	# backup config.h.def
	backup_res=$(mv $config_def_h_file "$dir/config.def.bk.h")
	if [[ ! "$backup_res" == "" ]]; then 
	
		echo "Can't backup config.h.def. Error: $backup_res"
		return
	fi

	# clone config.h to config.def.h
	clone_res=$(cp $config_h_file $config_def_h_file)
	if [[ ! "$clone_res" == "" ]]; then
		
		echo "Can't clone config.h to config.def.h"
		mv $dir/config.def.bk.h $config_def_h_file
		return
	else 
		rm -f $dir/config.def.bk.h
	fi
}

run $@
