#!/system/bin/sh

# ----- EP-OPENMP
for test in {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30}
do
    sleep 10
    data=$(date +"%Y%m%d%H%M%S")
    mkdir results/eficiencia/parallel/$data
    chmod 777 -R results/eficiencia/parallel/$data
    for class in {S,W}
    do
        for threads in {2,4}
        do
            for chunk in {16384,1048576}
            do
                for i in {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30}
                do
                    echo "Running: ep-openmp"
                    echo "Class  :" $class
                    echo "Threads:" $threads
                    echo "Chunk  :" $chunk
                    echo "Exec   :" $i
                    echo "Test   :" $test
                    echo ""
                    ./ep-openmp $class $threads $chunk > results/eficiencia/parallel/$data/ep-openmp-$class-$threads-$chunk--$i
                    ./battery >> results/eficiencia/parallel/$data/ep-openmp-$class-$threads-$chunk--$i
                done
            done
        done
    done
done

echo "DONE"