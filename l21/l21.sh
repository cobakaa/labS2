#!/bin/bash

file=""
dir=""

while [ -n "$1" ] 
do
case "$1" in 
-v) 
	set -x 
	;;
--info) 
		printf "\nNAME\n\t"$0" --  Compare the specified file with all other files that have the same suffix, and delete the matching files. \n\nSYNOPSIS\n\t"$0" [PARAMETERS] [FILE]\n\nDESCRIPTION\n\n\tProgramm checks all files in directory and in all subderictotries. If the suffix and the content of the input file match, it will be deleted.\n\n\t-v\tenable trace mode\n\t--info\tShows help (this menu) and exits\n\t-d\tSet directory for processing.\n\n"
		exit 0
		;;
-d)
	if [ -d $2 ]
	then
		dir="$2"
		shift
	else
		echo "Directory \"$2\" doesn't exists."
		exit 2
	fi
	;;
-f)
	if [ -f $2 ] && [ -z $file ]
	then
		file="$2"
		shift
	else
		echo "File \"$2\" doesn't exists."
		exit 2
	fi
	;;
--) 

	shift
	break 
	;;
-*) 
	echo "Incorrect values. Type --info for usage info."
	exit 1
	;;
*)
	if [ -f $1 ] && [ -z $file ]
	then 
		file="$1"
		# shift
	else
		echo "File \"$1\" doesn't exists."
		exit 1
	fi
	;;
esac
# echo "$1 $file $dir"
shift
done

suff=`echo "${file##*.}"`

if [ $file = $suff ]
then
	suff=""
fi

if [ -z $dir ]
then
	dir="/"
fi

# files=()

if [ -n $suff ]
then
	files=(`find $dir -name "*.$suff" -type f 2> /dev/null`)
else 
	files=(`find $dir -name "*$file" -type f 2> /dev/null`)
fi

# for f in ${files[@]}
# do
# 	echo $f
# done

for f in ${files[@]}
do
	# echo "$( diff $f $file )"
	if [ -z "$( diff $f $file )" ] && [ "$( readlink -e $f )" != "$( readlink -e $file )" ]
	then
		echo $f
	fi
done

# echo "$(whoami)"

exit 0
