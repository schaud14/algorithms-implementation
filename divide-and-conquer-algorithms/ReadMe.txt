	CS575
	Section-01
	Project-2

	Saurabh Abhay Chaudhari

	----Instruction to Run the code:
	
	1.Extract: 	tar -xvf saurabh_chaudhari_proj2.tar
	2.Nevigate:	cd saurabh_chaudhari_proj2
	3.Compile:	"make compile" or "make"
	4.Run:		"make run_stra" or "make run_tro" or "./floyd <input_file>"
	5.Clean: 	make clean



---------Strassen's Algorithm:
	To test this code, after Compiling use "make run_stra" or "./strassen" to run the code.
	This will give the prompt to enter the size of matrix.
	Size should be of power 2, otherwise it will give the prompt again.
	After entering the valid size program will generate two random matrices and print their multiplication by Strassens's method and Traditional method.

---------Tromino's Tiling Algorithm:
	To test this code, after Compiling use "make run_tro" or "./tromino" to run the code.
	This will give the prompt to enter the value of k, where size is 2^k.
	This program will generate the hole at random in given grid and use recursive method to fill grid with tromino's tiles.

---------Floyd's Shortest Path Algorithm:
	To test this code after compiling use "./floyd <input_file>" where input file is file containing the matrix with comma seperated values.
	This program will Calculate the shortest path for all pairs of node and store them into same matrix.
	This program will also save the path matrix which will give the intermidiate nodes to find shortest path. 
