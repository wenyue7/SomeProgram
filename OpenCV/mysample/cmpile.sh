g++ -o mysample.out mysample.cpp mysample_func.cpp -I ./ $(pkg-config --cflags --libs opencv ) && ./mysample.out 
