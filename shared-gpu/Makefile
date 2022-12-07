main: *.cu *.h 
	nvcc \
	-arch compute_52 \
	-code sm_52 \
	-lm -o shared-gpu *.cu
