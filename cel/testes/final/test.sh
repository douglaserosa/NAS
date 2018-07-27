#!/system/bin/sh

benchmark=$1
class=$2
threads=$3
chunk=$4

# liga tela brilho 100
echo 255 > /sys/class/leds/lcd-backlight/brightness

./battery > batteryLevel
batteryLevel=$(cat batteryLevel)

while [ $batteryLevel -gt 99 ]; do
    if [ "$chunk" = "" ]; then
        ./$benchmark S $threads
        echo ""
    else
        ./$benchmark S $threads $chunk
        echo ""
    fi
    ./battery > batteryLevel
    batteryLevel=$(cat batteryLevel)
done

# desliga tela
echo 0 > /sys/class/leds/lcd-backlight/brightness
sleep 10

mkdir -p results/final/$benchmark
chmod 777 -R results/final/$benchmark

for test in {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30}
do
    for exec in {1,2,3,4}
    do
        echo "Running: $benchmark"
        echo "Class  :" $class
        echo "Threads:" $threads
        if [ "$chunk" != "" ]; then
            echo "Chunk  :" $chunk
        fi
        echo "Test   :" $test
        echo "Exec   :" $exec
        echo ""

        # desliga tela
        echo 0 > /sys/class/leds/lcd-backlight/brightness

        if [ "$chunk" = "" ]; then
            ./$benchmark $class $threads > results/final/$benchmark/$benchmark-$class-$threads\_$test\_$exec
            ./battery >> results/final/$benchmark/$benchmark-$class-$threads\_$test\_$exec
        else
            ./$benchmark $class $threads $chunk > results/final/$benchmark/$benchmark-$class-$threads-$chunk\_$test\_$exec
            ./battery >> results/final/$benchmark/$benchmark-$class-$threads-$chunk\_$test\_$exec
        fi
    done
done

# liga tela brilho 0
echo 50 > /sys/class/leds/lcd-backlight/brightness

echo "DONE"