#!/system/bin/sh

# ----- EP-OPENMP-DYNAMIC
data=$(date +"%Y%m%d%H%M%S")
for class in {S,W}
do
	for threads in {2,4}
	do
        for chunk in {1024,1048576}
        do
            for i in {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30}
            do
                echo "Running: ep-openmp-dynamic"
                echo "Class  :" $class
                echo "Threads:" $threads 
                echo "Chunk  :" $chunk
                echo "Exec   :" $i
                echo ""
                ./ep-openmp-dynamic $class $threads $chunk > results/eficiencia/dynamic/$data/ep-openmp-dynamic-$class-$threads-$chunk--$i
                ./battery >> results/eficiencia/dynamic/$data/ep-openmp-dynamic-$class-$threads-$chunk--$i
            done
        done
	done
done

echo "DONE"