#!/bin/bash

file=""
dir=""
modey=false

while [ -n "$1" ]
do
case "$1" in
-v)
	set -x
	;;
--info)
		printf "\nNAME\n\t"$0" --  Compare the specified file with all other files that have the same suffix, and delete the matching files. \n\nSYNOPSIS\n\t"$0" [PARAMETERS] [FILE]\n\nDESCRIPTION\n\n\tProgramm checks all files in directory and in all subderictotries. If the suffix and the content of the input file match, it will be deleted.\n\n\t-v\tEnable trace mode\n\t--info\tShows help (this menu) and exits\n\t-d\tSet directory for processing.\n\t-f\tSet file for processing.\n\t-y\tAuto accept removing files.\n\n"
		exit 0
		;;
-d)
	if [[ -d $2 ]]
	then
		dir="$2"
		shift
	else
		echo "Directory \"$2\" doesn't exists."
		exit 2
	fш
	;;
-f)
	if [[ -f $2 ]] && [ -z $file ]
	then
		file="$2"
		shift
	else
		echo "File \"$2\" doesn't exists."
		exit 2
	fi
	;;

-y)
	modey=true
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
	if [[ -f $1 ]] && [ -z $file ]
	then
		file="$1"
		# shift
	else
		echo "File \"$1\" doesn't exists."
		exit 1
	fi
	;;
esac

shift
done

if [ -z "$file" ]
then
	echo "Incorrect values. Type --info for usage info."
	exit 1

fi

suff=`echo "${file##*.}"`

if [ "$file" = "$suff" ]
then
	suff=""
fi

if [[ -z $dir ]]
then
	dir="."
fi

files=()

if [[ $suff != "" ]]
then
	while IFS=  read -r -d $'\0'
	do
    	files+=("$REPLY")
	done < <(find $dir -name "*.$suff" -type f -print0 2> /dev/null)
else
	while IFS=  read -r -d $'\0'
	do
		# echo "$REPLY"
    	files+=("$REPLY")
	done < <(find $dir -not -name "*.*" -type f -print0 2> /dev/null)
fi

to_delete=()

for f in "${files[@]}"
do
	if [ -z "$( diff "$f" "$file" )" ] && [ "$( readlink -e "$f" )" != "$( readlink -e "$file" )" ]
	then
		to_delete+=("$f")
	fi
done

if [ ${#to_delete[@]} -eq 0 ]
then
	echo "There is no files to delete."
	exit 0
fi

echo "Files to delete:"

for i in ${!to_delete[@]}
do
	echo " ${to_delete[$i]}"

done

echo ""
if [ "$modey" = "true" ]
then
	answer="y"
else
	echo -n "$0: Remove files? (Y/n): "
	read answer
fi

if [ `echo $answer | awk '{print tolower($0)}'` = "y" ]
then

	rm -f ${to_delete[@]}
	echo "Files deleted."

elif [ `echo $answer | awk '{print tolower($0)}'` = "n" ]
then
	echo "Files not deleted."
else

	echo "Wrong answer."

fi

exit 0
