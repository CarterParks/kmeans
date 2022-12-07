cd serial
./serial indata.csv > outdata
cd ..

cd shared-cpu
./shared-cpu indata.csv > outdata
cd ..

cd shared-gpu
./shared-gpu indata.csv > outdata
cd ..

diff -q serial/outdata shared-cpu/outdata
diff -q serial/outdata shared-gpu/outdata
