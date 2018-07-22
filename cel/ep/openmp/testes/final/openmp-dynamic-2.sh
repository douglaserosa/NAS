#!/system/bin/sh

# ----- EP-OPENMP-DYNAMIC
mkdir -p results/final/ep-openmp-dynamic
chmod 777 -R results/final/ep-openmp-dynamic
for class in A
do
    for threads in 2
    do
        for chunk in 16384
        do
            for test in {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30}
            do
                for exec in {1,2,3,4,5}
                do
                    echo "Running: ep-openmp-dynamic"
                    echo "Class  :" $class
                    echo "Threads:" $threads
                    echo "Chunk  :" $chunk
                    echo "Test   :" $test
                    echo "Exec   :" $exec
                    echo ""
                    ./ep-openmp-dynamic $class $threads $chunk > results/final/ep-openmp-dynamic/ep-openmp-dynamic-$class-$threads-$chunk\_$test\_$exec
                    ./battery >> results/final/ep-openmp-dynamic/ep-openmp-dynamic-$class-$threads-$chunk\_$test\_$exec
                done
            done
        done
    done
done


echo "DONE"