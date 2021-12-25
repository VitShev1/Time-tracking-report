Time_tracking_report

For work of the program need file "data.csv" with start information.

build:
mkdir build
cd build
cmake ..
cmake --build .

run:
main.exe <path_to_input.csv> <path_to_output.csv>

You get 2 files: "out.csv", where the output is saved and "log.txt", where you see the problems of the program.