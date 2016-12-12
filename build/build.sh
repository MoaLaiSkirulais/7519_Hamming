# ---------------
# args
# ---------------
export gdb=0;
export valgrind=0;
export win64=0;
export win32=0;

for var in "$@"
do
    if [[ "$var" = "-gdb" ]];then gdb=1; fi	
    if [[ "$var" = "-v" ]];then valgrind=1; fi	
	if [[ "$var" = "-win32" ]];then win32=1; fi
    if [[ "$var" = "-win64" ]];then win64=1; fi	
done

# ---------------
# compile
# ---------------
export PLATFORM=linux; #default
if [ $win32 = 1 ]; then export PLATFORM=win32; fi;
if [ $win64 = 1 ]; then export PLATFORM=win64; fi;

if [ "$PLATFORM" == "win32" ]; then
	export GCC="i686-w64-mingw32-gcc"
	export LFLAGS="-pthread -lm -lwsock32 -lssp"
	export FLAGS=""
fi;

if [ "$PLATFORM" == "win64" ]; then
	export GCC="x86_64-w64-mingw32-gcc"
	export LFLAGS="-pthread -lm -lwsock32 -lssp"
	export FLAGS=""
fi;

if [ "$PLATFORM" == "linux" ]; then
	export GCC="gcc"
	export LFLAGS="-pthread -rdynamic -ldl -lm -lcrypto -lssl"
	export FLAGS="-Werror -g"
fi;

rm ../binary/*.a
rm ../binary/*.o
make -f Makefile

# ---------------
# link
# ---------------
export buildroot="../binary";
export EXEFILE="tdc_Hamming.$PLATFORM.exe";

rm -f $buildroot/$EXEFILE
make -f Makefile.test

# ---------------
# run
# ---------------

cd $buildroot

if [ -f $EXEFILE ]; then 		

	if [ $valgrind = 1 ]; then #valgrind
		printf "\n\n~> Running valgrind:main \n"
		executable=./$EXEFILE;
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrindLog.val $executable
		chmod -R 777 *
		tail ./valgrindLog.val;
		exit 0;
	fi

	if [ $gdb = 1 ]; then #gdb
		printf "\n\n~> Running gdb:main \n"
		gdb ./$EXEFILE;
		exit 0;
	fi
	
	./$EXEFILE;
fi;




