You will find in this README the commands to do in order to test the differents
elements that are presented for the first defense.



Loading picture :
Go to the folder "image" then perform the following commands:
make
./display images/source.jpeg (replacing source.jpeg by the chosen picture)


Grayscale image :
Go to the folder "image" then perform the following commands:
make
./grayscale images/source.jpeg (replacing source.jpeg by the chosen picture)


Binarized image :
Go to the folder "image" then perform the following commands:
make
./binarization images/source.jpeg (replacing source.jpeg by the chosen picture)


Image rotation :
Go to the folder "image" then perform the following commands:
make
./rotation images/source.jpeg angle (replacing source.jpeg by the chosen
picture and angle by the chosen angle)


Grid process :
Go to the folder "grid" then perform the following commands:
make
./grid_process ../image/images/source.jpeg X1 Y1 X2 Y2 (replacing source.jpeg by
the chosen image and 'X1,Y1 by the topleft coord of the grid and X2 Y2 by
the bottom right, let empty for 0,0 and width,height not working)


Xor :
Go to the folder "neuralnetwork" then perform the following commands:
make
./XOR x y (with x and y taking as values either 0 or 1)


Solver :
Go to the folder "solver" then perform the following commands:
make solver
./solver grid (replacing grid by the grid you want to resolve)
