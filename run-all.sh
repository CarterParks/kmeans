cd serial
time ./serial ../indata.csv > outdata
cd ..

cd shared-cpu
time ./shared-cpu ../indata.csv > outdata
cd ..

cd shared-gpu
time ./ghared-cpu ../indata.csv > outdata
cd ..

diff -q serial/outdata shared-cpu/outdata
diff -q serial/outdata shared-gpu/outdata

python3 visualize.py serial shared-cpu shared-gpu
