add_executable(
   MYQHYCCDDEMO
   main.cpp
)

target_link_libraries(
   MYQHYCCDDEMO
   USB-1::USB-1
   QHYCCD::QHYCCD
)
