#!/bin/bash

# ----- EP-CILK
cd ep/cilk/
make all

for class in {A,B,C}
do
	for threads in {2,4,8,16,32,64}
	do
		for i in {1..10}
		do
			echo "running ep-cilk" $class $threads "exec" $i  
			./ep-cilk $class $threads > ep-cilk-$class-$threads--$i
		done
	done
done

# ----- EP-CPP
cd ../cpp/
make all

for class in {A,B,C}
do
	for threads in {2,4,8,16,32,64}
	do
		for i in {1..10}
		do
			echo "running ep-cpp" $class $threads "exec" $i  
			./ep-cpp $class $threads > ep-cpp-$class-$threads--$i
		done
	done
done

# ----- EP-MPI
cd ../mpi/
make all

for class in {A,B,C}
do
	for threads in {2,4,8,16,32,64}
	do
		for i in {1..10}
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

for class in {A,B,C}
do
	for threads in {2,4,8,16,32,64}
	do
		for i in {1..10}
		do
			echo "running ep-openmp" $class $threads "exec" $i  
			./ep-openmp $class $threads > ep-openmp-$class-$threads--$i
		done
	done
done

# ----- EP-PTHREADS
cd ../pthreads/
make all

for class in {A,B,C}
do
	for threads in {2,4,8,16,32,64}
	do
		for i in {1..10}
		do
			echo "running ep-pthreads" $class $threads "exec" $i  
			./ep-pthreads $class $threads > ep-pthreads-$class-$threads--$i
		done
	done
done

# ----- EP-PTHREADS-CILK
cd ../pthreads-cilk/
make all

for class in {A,B,C}
do
	for threads in {2,4,8,16,32,64}
	do
		for i in {1..10}
		do
			echo "running ep-pthreads-cilk" $class $threads "exec" $i  
			./ep-pthreads-cilk $class $threads > ep-pthreads-cilk-$class-$threads--$i
		done
	done
done

# ----- EP-SERIAL
cd ../serial/
make all

for class in {A,B,C}
do
	for i in {1..10}
	do
		echo "running ep-serial" $class "exec" $i  
		./ep-serial $class > ep-serial-$class--$i
	done
done

# ----- IS-CILK
cd ../../is/cilk
make suite
cd bin

for class in {A,B,C}
do
	for threads in {2,4,8,16,32,64}
	do
		for i in {1..10}
		do
			echo "running cilk is."$class".x" $threads "exec" $i  
			./is.$class.x $threads > is-cilk-$class-$threads--$i
		done
	done
done

# ----- IS-CPP
cd ../../cpp/
make suite
cd bin

for class in {A,B,C}
do
	for threads in {2,4,8,16,32,64}
	do
		for i in {1..10}
		do
			echo "running cpp is."$class".x" $threads "exec" $i  
			./is.$class.x $threads > is-cpp-$class-$threads--$i
		done
	done
done

# ----- IS-MPI
cd ../../mpi/
make suite
cd bin

for class in {A,B,C}
do
	for threads in {2,4,8,16,32,64}
	do
		for i in {1..10}
		do
			echo "running mpi is."$class".x" $threads "exec" $i  
			#mpirun -c $threads ./is.$class.x  > is-mpi-$class-$threads--$i
			mpirun -n $threads ./is.$class.x  > is-mpi-$class-$threads--$i
		done
	done
done

# ----- IS-openmp
cd ../../openmp/
make suite
cd bin

for class in {A,B,C}
do
	for threads in {2,4,8,16,32,64}
	do
		for i in {1..10}
		do
			echo "running openmp is."$class".x" $threads "exec" $i  
			./is.$class.x $threads > is-openmp-$class-$threads--$i
		done
	done
done

# ----- IS-pthreads
cd ../../pthreads/
make suite
cd bin

for class in {A,B,C}
do
	for threads in {2,4,8,16,32,64}
	do
		for i in {1..10}
		do
			echo "running pthreads is."$class".x" $threads "exec" $i  
			./is.$class.x $threads > is-pthreads-$class-$threads--$i
		done
	done
done

# ----- IS-serial
cd ../../serial/
make suite
cd bin

for class in {A,B,C}
do
	for i in {1..10}
	do
		echo "running serial is."$class".x exec" $i  
		./is.$class.x > is-serial-$class--$i
	done
done

# ----- IS-mpi-openmp
cd ../../mpi-openmp/
make suite
cd bin

for class in {A,B,C}
do
	for i in {1..10}
	do
		echo "running mpi-openmp is."$class".x 2 hosts 16 threads exec" $i
		#mpirun -c 2 ./is.$class.x 16 > is-mpi-openmp-$class-2hosts-16threads--$i
		mpirun -n 2 ./is.$class.x 16 > is-mpi-openmp-$class-2hosts-16threads--$i

		echo "running mpi-openmp is."$class".x 4 hosts 8 threads exec" $i
		#mpirun -c 4 ./is.$class.x 8 > is-mpi-openmp-$class-4hosts-8threads--$i
		mpirun -n 4 ./is.$class.x 8 > is-mpi-openmp-$class-4hosts-8threads--$i

		echo "running mpi-openmp is."$class".x 8 hosts 4 threads exec" $i
		#mpirun -c 8 ./is.$class.x 4 > is-mpi-openmp-$class-8hosts-4threads--$i
		mpirun -n 8 ./is.$class.x 4 > is-mpi-openmp-$class-8hosts-4threads--$i

		echo "running mpi-openmp is."$class".x 16 hosts 2 threads exec" $i
		#mpirun -c 16 ./is.$class.x 2 > is-mpi-openmp-$class-16hosts-2threads--$i
		mpirun -n 16 ./is.$class.x 2 > is-mpi-openmp-$class-16hosts-2threads--$i
	done

done

echo "DONE"