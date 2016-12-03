g++ -Wall -O2 main.cpp -o  main -I/usr/local/include/ -lopencv_core -lopencv_highgui

#g++ -Wall -fexceptions -O2 -I/usr/local/include/opencv2 -I/usr/local/include/opencv -c main.cpp -o main.o
#g++ -L/usr/local/bin -o main main.o  -s -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab  
