#!/system/bin/sh

# ----- EP-OPENMP
for test in {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30}
do
    sleep 10
    data=$(date +"%Y%m%d%H%M%S")
    mkdir -p results/eficiencia/parallel/4-threads/$data
    chmod 777 -R results/eficiencia/parallel/4-threads/$data
    for class in S
    do
        for threads in 4
        do
            for i in {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30}
            do
                echo "Running: ep-openmp"
                echo "Class  :" $class
                echo "Threads:" $threads
                echo "Test   :" $test
                echo "Exec   :" $i
                echo ""
                ./ep-openmp $class $threads > results/eficiencia/parallel/4-threads/$data/ep-openmp-$class-$threads--$i
                ./battery >> results/eficiencia/parallel/4-threads/$data/ep-openmp-$class-$threads--$i
            done
        done
    done
done

echo "DONE"