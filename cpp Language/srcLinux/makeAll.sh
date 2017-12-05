make profile-build ARCH=x86-64
strip corchessextended
mv 'corchessextended' 'CorChessExtended 051217-x86-64'
make clean

make profile-build ARCH=x86-64-modern
strip corchessextended
mv 'corchessextended' 'CorChessExtended 051217-x86-64-modern'
make clean

make profile-build ARCH=x86-64-bmi2
strip corchessextended
mv 'corchessextended' 'CorChessExtended 051217-x86-64-bmi2'
make clean

make profile-build ARCH=x86-32
strip corchessextended
mv 'corchessextended' 'CorChessExtended 051217-x86-32'
make clean

make profile-build ARCH=x86-32-old
strip corchessextended
mv 'corchessextended' 'CorChessExtended 051217-x86-32-old'
make clean

make profile-build ARCH=ppc-64
strip corchessextended
mv 'corchessextended' 'CorChessExtended 051217-ppc-64'
make clean

make profile-build ARCH=ppc-32
strip corchessextended
mv 'corchessextended' 'CorChessExtended 051217-ppc-32'
make clean

make profile-build ARCH=armv7
strip corchessextended
mv 'corchessextended' 'CorChessExtended 051217-armv7'
make clean

make profile-build ARCH=general-64
strip corchessextended
mv 'corchessextended' 'CorChessExtended 051217-general-64'
make clean

make profile-build ARCH=general-32
strip corchessextended
mv 'corchessextended' 'CorChessExtended 051217-general-32'
make clean
