#!/bin/bash

# silence the wall of warnings that came with the old code
gcc -O3 new_washington.c -o build/new_washington 2> /dev/null
gcc -O3 old_washington_with_fixed_seed.c -o build/old_washington 2> /dev/null

echo "INSTANCE TYPE: 1"
./build/new_washington 1 100 100 1000 new_inst1.gr
./build/old_washington 1 100 100 1000 old_inst1.gr
diff -s new_inst1.gr old_inst1.gr
echo "INSTANCE TYPE: 2"
./build/new_washington 2 100 100 1000 new_inst2.gr
./build/old_washington 2 100 100 1000 old_inst2.gr
diff -s new_inst2.gr old_inst2.gr
echo "INSTANCE TYPE: 3"
./build/new_washington 3 100 100 1000 new_inst3.gr
./build/old_washington 3 100 100 1000 old_inst3.gr
diff -s new_inst3.gr old_inst3.gr
echo "INSTANCE TYPE: 4"
./build/new_washington 4 100 100 1000 new_inst4.gr
./build/old_washington 4 100 100 1000 old_inst4.gr
diff -s new_inst4.gr old_inst4.gr
echo "INSTANCE TYPE: 5"
./build/new_washington 5 100 100 1000 new_inst5.gr
./build/old_washington 5 100 100 1000 old_inst5.gr
diff -s new_inst5.gr old_inst5.gr
echo "INSTANCE TYPE: 6"
echo "Now there's a new parameter, taking the range, instead of using MAX_RANGE"
./build/new_washington 6 100 100 50 1000000 new_inst6.gr
./build/old_washington 6 100 100 50 old_inst6.gr
diff -s new_inst6.gr old_inst6.gr
echo "INSTANCE TYPE: 7"
echo "Now there's a new parameter, taking the range, instead of using MAX_RANGE."
./build/new_washington 7 10 10 50 1000000 new_inst7.gr
./build/old_washington 7 10 10 50 old_inst7.gr
diff -s new_inst7.gr old_inst7.gr
echo "INSTANCE TYPE: 8"
echo "Now there's a new parameter, taking the range, instead of using MAX_RANGE."
./build/new_washington 8 10 10 50 1000000 new_inst8.gr
./build/old_washington 8 10 10 50 old_inst8.gr
diff -s new_inst8.gr old_inst8.gr
echo "INSTANCE TYPE: 9"
echo "Now there are two less parameters, that weren't used."
./build/new_washington 9 100 new_inst9.gr
./build/old_washington 9 100 0 0 old_inst9.gr
diff -s new_inst9.gr old_inst9.gr
echo "INSTANCE TYPE: 10"
echo "Now there are two less parameters, that weren't used."
./build/new_washington 10 100 new_inst10.gr
./build/old_washington 10 100 0 0 old_inst10.gr
diff -s new_inst10.gr old_inst10.gr
echo "INSTANCE TYPE: 11"
echo "Now there's a new parameter, taking the range, instead of using VERY_BIG."
echo "Also, the code generated a instance file reporting the wrong number of vertexes, this is fixed now."
./build/new_washington 11 10 10 10 1000000 new_inst11.gr
./build/old_washington 11 10 10 10 old_inst11.gr
diff -s new_inst11.gr old_inst11.gr

