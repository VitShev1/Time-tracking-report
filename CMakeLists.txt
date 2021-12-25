project(Time_tracking_report)

cmake_minimum_required(VERSION 3.22)

add_executable(main main.cpp Parser_CSV.cpp Loger.cpp Parser_CSV.h Loger.h)
