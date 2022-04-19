CD tools

if exist "../output/old_512k.bin" mkuzimage -n demo -i ../output/old_512k.bin -o ../output/uold_512k.bin
if exist "../output/old_1024k.bin" mkuzimage -n demo -i ../output/old_1024k.bin -o ../output/uold_1024k.bin
if exist "../output/new_512k.bin" make_udiff -o ../output/old_512k.bin -n ../output/new_512k.bin -p ../output/patch_512k.bin
if exist "../output/new_1024k.bin" make_udiff -o ../output/old_1024k.bin -n ../output/new_1024k.bin -p ../output/patch_1024k.bin


