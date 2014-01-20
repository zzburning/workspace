#!/bin/sh

function pause()
{
	read -n 1 -p "$*" INP
	if [[ $INP = 'y' ]] ; then
		echo -ne '\b\n'
	elif [[ $INP = 'n' ]] ; then
		echo "cancel"
		exit 0
	else
		echo "do nothing"
		exit 0
	fi
}

function YorN()
{
	while true; do
	    read -p "Do you wish to restore system to defaults[y/n]?" yn
	    case $yn in
	        [Yy]* ) echo "ok"; break;;
	        [Nn]* ) exit;;
	        * ) echo "Please answer y or n.";;
	    esac
	done
}

echo "first line"
set -x
echo "second line"
set +x
echo "third line"

read -n 1 -p "press any key to continue"

echo "second line"
echo "second line"

# YorN();
while true; do
    read -p "Do you wish to restore system to defaults[y/n]?" yn
    case $yn in
        [Yy]* ) 
			echo "ok";
			echo "ok" 
			break;;
        [Nn]* ) break;;
        * ) echo "Please answer y or n.";;
    esac
done


while true; do
    read -p "Do you wish to restore system to defaults, press[y/n]?" yn
    case $yn in
        [Yy]* ) 
			# === step 8 ===
			# restore system defaults
			echo "#############restore system defaults############"
			>restore_echo.txt
			>restore_error.txt
			sudo bash -c ">restore_res.txt"
			if
				echo "ok"
				# sudo ./ats.bin -f wdir/conf/ats_restore.conf  2>restore_error.txt #1>restore_echo.txt
			then
				echo "set restore over"
			else
				echo "set alarm fail"; exit -7;
			fi
			break;;
        [Nn]* ) break;;
        * ) echo "Please answer y or n.";;
    esac
done

pause "press y to contine, n to cancel ..."

echo "third line"
