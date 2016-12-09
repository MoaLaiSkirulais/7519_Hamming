# ---------------
# args
# ---------------
export gdb=0;
export valgrind=0;
for var in "$@"
do
    if [[ "$var" = "-gdb" ]];then gdb=1; fi	
    if [[ "$var" = "-v" ]];then valgrind=1; fi	
done

# ---------------
# compile
# ---------------
export GCC="gcc"
export LFLAGS="-pthread -rdynamic -ldl -lm -lcrypto -lssl"
export FLAGS="-Werror -g"
make -f Makefile

# ---------------
# link
# ---------------
export buildroot="../binary";
export EXEFILE="tdc_Hamming.exe";

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




