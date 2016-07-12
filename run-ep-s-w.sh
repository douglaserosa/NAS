#!/bin/bash

# ----- EP-CILK
cd ep/cilk/
make all

for class in {S,W}
do
	for threads in {2,4,8,16,32}
	do
		for i in {1..5}
		do
			echo "running ep-cilk" $class $threads "exec" $i  
			./ep-cilk $class $threads > ep-cilk-$class-$threads--$i
		done
	done
done

# ----- EP-CPP
cd ../cpp/
make all

for class in {S,W}
do
	for threads in {2,4,8,16,32}
	do
		for i in {1..5}
		do
			echo "running ep-cpp" $class $threads "exec" $i  
			./ep-cpp $class $threads > ep-cpp-$class-$threads--$i
		done
	done
done

# ----- EP-MPI
cd ../mpi/
make all

for class in {S,W}
do
	for threads in {2,4,8,16,32}
	do
		for i in {1..5}
		do
			echo "running ep-mpi" $class $threads "exec" $i  
			#mpirun -c $threads ep-mpi $class > ep-mpi-$class-$threads--$i
			mpirun -n $threads ./ep-mpi $class > ep-mpi-$class-$threads--$i
		done
	done
done

# ----- EP-OPENMP
cd ../openmp/
make all

for class in {S,W}
do
	for threads in {2,4,8,16,32}
	do
		for i in {1..5}
		do
			echo "running ep-openmp" $class $threads "exec" $i  
			./ep-openmp $class $threads > ep-openmp-$class-$threads--$i
		done
	done
done

# ----- EP-PTHREADS
cd ../pthreads/
make all

for class in {S,W}
do
	for threads in {2,4,8,16,32}
	do
		for i in {1..5}
		do
			echo "running ep-pthreads" $class $threads "exec" $i  
			./ep-pthreads $class $threads > ep-pthreads-$class-$threads--$i
		done
	done
done

# ----- EP-PTHREADS-CILK
cd ../pthreads-cilk/
make all

for class in {S,W}
do
	for threads in {2,4,8,16,32}
	do
		for i in {1..5}
		do
			echo "running ep-pthreads-cilk" $class $threads "exec" $i  
			./ep-pthreads-cilk $class $threads > ep-pthreads-cilk-$class-$threads--$i
		done
	done
done

# ----- EP-SERIAL
cd ../serial/
make all

for class in {S,W}
do
	for i in {1..5}
	do
		echo "running ep-serial" $class "exec" $i  
		./ep-serial $class > ep-serial-$class--$i
	done
done

echo "DONE"