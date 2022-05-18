cmake -G "NMake Makefiles" . -B ../bin/release
cd ../bin/release
nmake
cd ../../src