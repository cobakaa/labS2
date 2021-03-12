#!/bin/sh
for k in "$@"
do
	if [ "-$k" = "--t" ]
	then
		set -x
		break
	elif [ "-$k" = "--?" ]
	then
		printf "\nNAME\n\t"$0" -- Displays the number of lines in text files from directory and all subdirectories with the extension .cpp and .h\n\nSYNOPSIS\n\t"$0" [-t] [FILE]\n\t"$0" [-?]\nDESCRIPTION\n\tProgramm checks all files in directory and in all subderictotries. In the end of output programm reports about total number of lines.\n\n\t-t\tenable trace mode\n\t-?\tShows help (this menu) and exits\n\n"
		exit 0
	fi
done
for j in "$@"
do
	if [[ "-$j" != --t ]]
	then
		if [[ "-$j" == --* ]]
		then
			echo "$0: Incorrect values."
			exit 1
		elif [ -d "$j" ]
		then
			pr=$j
		else
			echo "$0: No such file or directory."
			exit 2
		fi
	fi
idone
if [[ $pr == "" ]]
then
	pr="."
fi
res=0
s=0
for i in `find "$pr" \( -name '*.cpp' -o -name '*.h' \)`
do
	l=`cat "$i" | wc -l`
	s=`echo "$s+$l" | bc`
	printf "%-5s %s\n" "$l" "${i##*/}"
	res=`echo "$res+$s" | bc`
	s=0
done
echo "Result: $res"
exit 0

