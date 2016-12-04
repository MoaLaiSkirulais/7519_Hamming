# ---------------
# compile
# ---------------

export GCC="gcc"
export LFLAGS="-pthread -rdynamic -ldl -lm -lcrypto -lssl"
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
	./$EXEFILE $apiport;
fi;
