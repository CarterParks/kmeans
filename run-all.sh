cd serial
make
./serial ../indata.csv > outdata
cd ..

cd shared-cpu
make
./shared-cpu ../indata.csv > outdata
cd ..

cd shared-gpu
make
./shared-gpu ../indata.csv > outdata
cd ..

diff -q serial/outdata shared-cpu/outdata
diff -q serial/outdata shared-gpu/outdata

python3 visualize.py serial shared-cpu shared-gpu
