rm -r .build_mac
mkdir .build_mac
cd .build_mac
cmake -DTARGET_SYSTEM=MAC ..
make
