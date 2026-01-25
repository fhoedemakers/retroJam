:
# ====================================================================================
# retroJam build all script 
# Only Adafruit Fruit Jam supported.
# Binaries are copied to the releases folder
# ====================================================================================
cd `dirname $0` || exit 1
[ -d releases ] && rm -rf releases
mkdir releases || exit 1
# check picotool exists in path
if ! command -v picotool &> /dev/null
then
	echo "picotool could not be found"
	echo "Please install picotool from https://github.com/raspberrypi/picotool.git" 
	exit
fi
HWCONFIGS="8 13 14"
for HWCONFIG in $HWCONFIGS
do
	./bld.sh -c $HWCONFIG -2 || exit 1
done
if [ -z "$(ls -A releases)" ]; then
	echo "No UF2 files found in releases folder"
	exit 1
fi
for UF2 in releases/*.uf2
do
	ls -l $UF2
	picotool info $UF2
	echo " "
done
