#!/system/bin/sh

# ----- EP-OPENMP
mkdir -p results/final/ep-openmp
chmod 777 -R results/final/ep-openmp
for class in A
do
    for threads in 4
    do
        for test in {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30}
        do
            for exec in {1,2,3,4,5}
            do
                echo "Running: ep-openmp"
                echo "Class  :" $class
                echo "Threads:" $threads
                echo "Test   :" $test
                echo "Exec   :" $exec
                echo ""
                ./ep-openmp $class $threads > results/final/ep-openmp/ep-openmp-$class-$threads\_$test\_$exec
                ./battery >> results/final/ep-openmp/ep-openmp-$class-$threads\_$test\_$exec
            done
        done
    done
done


echo "DONE"