#!/system/bin/sh

# ----- EP-OPENMP-STATIC
for class in S
do
	for threads in 4
	do
        for chunk in {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216}
        do
            for i in {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30}
            do
                echo "Running: ep-openmp-static"
                echo "Class  :" $class
                echo "Threads:" $threads 
                echo "Chunk  :" $chunk
                echo "Exec   :" $i
                echo ""
                ./ep-openmp-static $class $threads $chunk > results/chunk-size-test/static/ep-openmp-static-$class-$threads-$chunk--$i
                ./battery >> results/chunk-size-test/static/ep-openmp-static-$class-$threads-$chunk--$i
            done
        done
	done
done

echo "DONE"