rm -rf .build_mac
mkdir  .build_mac
cd     .build_mac

cmake -DTARGET_SYSTEM=MAC -DEDITOR_BUILD=ON ..
make -j8 chest_editor
# make -j8 chest 