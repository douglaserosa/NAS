#!/system/bin/sh

# ----- EP-OPENMP
for class in {S,W}
do
	for threads in {2,3,4}
	do
		for i in {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30}
		do
			echo "running ep-openmp" $class $threads "exec" $i  
			./ep-openmp $class $threads > results/openmp/ep-openmp-$class-$threads--$i
			./battery >> results/openmp/ep-openmp-$class-$threads--$i
		done
	done
done

echo "DONE"