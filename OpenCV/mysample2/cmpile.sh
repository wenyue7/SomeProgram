g++ -o mysample2.out mysample2.cpp mysample2_func.cpp -I . $(pkg-config --cflags --libs opencv ) && ./mysample2.out 
