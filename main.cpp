#include "include/block.h"
#include "include/calculate.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <math.h>
#include <algorithm>
#include <cmath>
#include <map>
#include <utility>
#include <bits/stdc++.h>
#include <sys/time.h>
#include <filesystem>

using namespace std; 

struct timeval start_time, end_time;




/////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char **argv)
{
////////////////////// Time Calculation ////////////////////////////
    srand(100);
    double start_count, end_count;
    double elapsed_time;        
    gettimeofday(&start_time,NULL);
  


if(argc!=3)
 {
 cout<<"Provide valid Input Arguments"<<endl;
 cout<<"Example: ./parser <filename> -a" << endl;
 return 1;
 }

string dict=argc[argv-2];
string Annealing_Type=argc[argv-1];

int block_size=0, net_size=0, out=0;
// string Block_Name,n_name;
size_t st,st_blank;

using recursive_directory_iterator = filesystem::recursive_directory_iterator;
for (auto& i : recursive_directory_iterator(dict.c_str()))
{
	B.clear();
	B_ptr.clear();
	while (!tabu_list.empty()) {tabu_list.pop();}
	while (!tabu_operator.empty()) {tabu_operator.pop();}
	vector_blocks.clear();
	pos_seq.clear();
	neg_seq.clear();
	string filename = i.path().string();
	ifstream input_file(filename.c_str()); 
	string line_n;
	string chip_width_st;
	string numBlocks_st;
	string Width_Height;
	string width;
	string height;
	string block_name;
	std::string whitespaces (" \t\f\v\n\r");
	int chip_width;
	int numBlocks;
	int name;
	int length;
	double Width;
	double Height;
	if(!input_file.is_open())
	{
		cout << "File could not be opened.\n";
		return 1;
	}
while(getline(input_file, line_n))
{

	if (line_n.find("chipwidth")!= string::npos){
		st = line_n.find(":");
		chip_width_st = line_n.substr(st + 2 ,line_n.size());
		std::size_t found = chip_width_st.find_last_not_of(whitespaces);
		assert(found != std::string::npos);
		chip_width_st.erase(found+1);
		chip_width = atoi(chip_width_st.c_str());
	}

	else if (line_n.find("numBlocks")!= string::npos)	{
		st = line_n.find(":");
		numBlocks_st = line_n.substr(st + 2 ,line_n.size());
		std::size_t found = numBlocks_st.find_last_not_of(whitespaces);
		assert(found != std::string::npos);
		numBlocks_st.erase(found+1);
		numBlocks = atoi(numBlocks_st.c_str());		
	}
	else{
		block b;
		st = line_n.find(" : ");
		assert(st != std::string::npos);
		block_name = line_n.substr(0 , st);
		Width_Height = line_n.substr(st+3 , line_n.size());
		std::size_t found = Width_Height.find_last_not_of(whitespaces);
		assert(found != std::string::npos);
		Width_Height.erase(found+1);
		st_blank = Width_Height.find(" ");
		width = Width_Height.substr(0,st_blank);
		length = Width_Height.size();
		height = Width_Height.substr(st_blank+1,length);
		Width = atof(width.c_str());
		Height = atof(height.c_str());
		name = atoi(block_name.c_str());
		b.Block_initialize(name,Width,Height);
		B.push_back(b);
	}

}




//////////////////////////// Storing in Pointers !! /////////////////////////////////////

for(int i=0;i<B.size();i++)
	B_ptr.push_back(&B[i]);

////////////////////////// First Define a Random Positive and Negative Sequence ///////////////////////////////
////////////////////////// The Sequences are stored in pos_seq and neg_seq vectors ////////////////////////////

for(int i=0; i<B_ptr.size(); i++)
{
	B_ptr[i]->pos_position = i;
	B_ptr[i]->neg_position = i;
	pos_seq.push_back(B_ptr[i]);
	neg_seq.push_back(B_ptr[i]);	
}
calculate_fanin_out();
calculate_HCG_VCG();
// while(Width_Final>chip_width){
// 	int random1 = rand()%B_ptr.size();
// 	int random2 = rand()%B_ptr.size();
//  	swap_both(random1,random2, 0);
// 	calculate_fanin_out();
// 	calculate_HCG_VCG();
// }
///////////////////////////  Initial Run //////////////////////////////////

cout<< "Chip Width: " << Width_Final << " Chip Height: " << Height_Final << endl;
//cout << endl <<endl;

// double Initial_Wire_Length = calculate_wirelength();
//cout << "Initial Wire Length: " << Initial_Wire_Length << endl;

////////////////////////////////////////////////////////////////////////////
Width_Initial = Width_Final;
Height_Initial = Height_Final;
////////////////////////////////////////////////////////////////////////////

double Initial_Area = calculate_Area();
//cout << "Initial Area of Chip: " << Initial_Area << endl;

////////////////////////////////////////////////////////////////////////////



//////////////////////// Simulated Annealing ///////////////////////////////

// double current_wirelength = Initial_Wire_Length;
double next_wirelength = 0;
double Delta_wirelength = 0;
double Delta_Height = 0;
double current_Area = Initial_Area;
double next_Area = 0;
double Delta_Area = 0;
double current_Height = Height_Initial;
double Delta_Total = 0;
double current_Width = Width_Initial;
double initial_temperature = 1000000000;
double freezing_temperature = 1;
double Temperature = initial_temperature;

int random1,random2,move;
double Temperature_Step = 0.97;
bool  b;
bool obj = 0;

/////////////////////////////////////////////////////////////////////////////
string var7 = "result_new_func/";
string constant_var7 = numBlocks_st +"_Results.csv";
string var8;
if(Annealing_Type == "-withouttb")
	var8 = "a";
if(Annealing_Type == "-withtb")
	var8 = "t"; 
////////////////////////////////////////////////////////////////////////////
string res1_filename = var7+var8+constant_var7;

ofstream res7(res1_filename.c_str());
res7<<"Temperature"<<"\t"<<"Accepted Moves"<<"\t"<<"Rejected Moves\t"<<"HPWL\t"<<"Area"<<endl;

while(Temperature>freezing_temperature)
{
	int accepted = 0;
	int rejected = 0;
	for(int i=0;i<100;i++)
	{
		random1 = rand()%B_ptr.size();
		random2 = rand()%B_ptr.size();
		move = rand()%3;

		if(move==0)
			swap_positive(random1,random2, Temperature);
		else if(move == 1)
			swap_negative(random1,random2, Temperature);
		else if(move == 2)
			swap_both(random1,random2, Temperature);
		// else 
			// rotate(random1 , random2);


		// ///////////// For Area //////////////////////
		if(Annealing_Type == "-withouttb")
		{
		//cout << "Doing for Area" << endl;
		next_Area = calculate_Area();
		Delta_Area = next_Area - current_Area;
		Delta_Height = Height_Final - current_Height;
		double alpha = 0.2;
		Delta_Total = (alpha*(Width_Final - chip_width) + (1-alpha)*Delta_Area);
		// Delta_Total = Delta_Area;
		//current_wirelength = calculate_wirelength();
		// if (Width_Final - chip_width > 0){
		// 	bool b = true;
		// }
		// else{
		// 	bool b = AcceptedMove(Delta_Total,Temperature);
		// }
		bool b = AcceptedMove(Delta_Total,Temperature);
		if(b)
		{
			current_Area = next_Area;
			current_Height = Height_Final;
			current_Width = Width_Final;
			accepted++;
		}
		else
		{
			rejected++;
			if(move==0)
				swap_positive(random1,random2 , Temperature);
			else if(move == 1)
				swap_negative(random1,random2, Temperature);
			else if(move == 2)
				swap_both(random1,random2, Temperature);
			// else
			//   	rotate(random1, random2);
		}
		// current_wirelength = calculate_wirelength();
		}

		else if(Annealing_Type == "-withtb")
		{
		//cout << "Doing for Area" << endl;
		next_Area = calculate_Area();
		Delta_Area = next_Area - current_Area;
		Delta_Height = Height_Final - current_Height;
		double alpha = 0.2;
		// Delta_Total = (alpha*(Width_Final - chip_width) + (1-alpha)*Delta_Area);
		Delta_Total = chip_width*Height_Final;
		bool b = AcceptedMove(Delta_Total,Temperature);
		bool c =Tabu_judgement(random1, random2, move);
		bool d = true;
		if(Width_Final>chip_width){
			d = false;
		}
		if (Delta_Total < 0){
			c = true;
		}
		if(b&c&d)
		{
			current_Area = next_Area;
			current_Height = Height_Final;
			current_Width = Width_Final;
			random1_final = random1;
			random2_final = random2;
			current_Delta_Total = Delta_Total;
			move_final = move;
			accepted++;
		}
		else
		{
			rejected++;
			if(move==0)
				swap_positive(random1,random2, Temperature);
			else if(move == 1)
				swap_negative(random1,random2, Temperature);
			else if(move == 2)
				swap_both(random1,random2, Temperature);
			// else
			//   	rotate(random1, random2);
		}
		// current_wirelength = calculate_wirelength();
		}
	}
	if (Annealing_Type == "-withtb"){
		count_tabu =count_tabu +1;
		pair<int,int> tabu_combine(random1_final,random2_final);
		tabu_list.push(tabu_combine);
		tabu_operator.push(move_final);
		// if (count_tabu== tabu_max){
		// 	tabu_list.pop();
		// }
	}
//cout << Temperature << endl;


//place<<"Final Placement of Gates"<<endl;
res7<<Temperature<<"\t"<<accepted<<"\t"<<rejected << "\t"<< "\t"<< current_Area <<endl;
Temperature = Temperature*Temperature_Step;
}

//cout << "Initial Wire Length: " << Initial_Wire_Length << endl;
//cout << "Final Wirelength: " << current_wirelength << endl;


//cout << "Initial Area: " << Initial_Area << endl;
//cout << "Final Area: " << current_Area << endl;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////// ### Write Everything to a File //////////////////////////////////////////////
string var1 = "result_new_func/";
string constant_val = numBlocks_st + ".txt";
string var2; 
//cout << Annealing_Type << endl;
if(Annealing_Type == "-withouttb")
	var2 = "a";
if(Annealing_Type == "-withtb")
	var2 = "t";
string outfile_name=var1+var2+constant_val;

ofstream res2(outfile_name.c_str());
res2 << "Results: " << endl;
// res2 << "Initial Wirelength of the Placement is: " << Initial_Wire_Length << endl;
res2 << "Initial Width of the Placement is: " << Width_Initial << endl;
res2 << "Initial Height of the Placement is: " << Height_Initial << endl;
res2 << "Initial Area of the Placement is: " << Initial_Area << endl;
res2 << endl;
res2 << "------------------------------------------------------------------------------" << endl;
// res2 << "The Total HPWL of the Placement is: " << current_wirelength << endl;
res2 << "The width of the Placement is: " << current_Width << endl;
res2 << "The height of the Placement is: " << current_Height << endl;
res2 << "The Total Area of Placement is: " << current_Area << endl;
res2 << endl;
res2 << "------------------------------------------------------------------------------" << endl;
res2 << "Final Block Placements with x and y coordinates: " << endl;

for(int i=0;i<B_ptr.size(); i++)
{
	res2<< "Block Name: " << (*B_ptr[i]).name << "\t" <<  "Block x-coodinate: " << (*B_ptr[i]).x_coord << "\t" <<  "Block y-coordinate: " << (*B_ptr[i]).y_coord 
	<< "\t" <<  "Rotate:"<<B_ptr[i]->rotate<< endl;
}




    gettimeofday(&end_time,NULL);
    start_count = (double) start_time.tv_sec + 1.e-6 * (double) start_time.tv_usec;
    end_count = (double) end_time.tv_sec + 1.e-6 * (double) end_time.tv_usec;
    elapsed_time = (end_count - start_count);
    printf("The total elapsed time is:  %f seconds\n",elapsed_time);
    res2 << "\nEXECUTION TIME IS : " << "\t" << elapsed_time << endl;

}
return 0;

}




/////////////////////////////////////////////////////////////////////////////////////////

