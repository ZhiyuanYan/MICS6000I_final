////////////////////////////////////// Functions Definitions ////////////////////////////////////////////////////

////////////////////////// ### Function to calculate Fan-in and Fan-out /////////////////////////////////////////
//////////////////////////       for each individual Block in the FP   //////////////////////////////////////////

#include "calculate.h"
 vector<block> B;
 vector<block*> B_ptr;
 vector<list<block*> > vector_blocks;
 vector<block*> pos_seq;
 vector<block*> neg_seq;

/////////////////////// Queues used for HCG and VCGs ////////////////////////////////////
 queue<block*> queue_HCG;
 queue<block*> queue_VCG;
/////////////////////// Queues used for HCG and VCGs ////////////////////////////////////
 queue<pair<int,int>> tabu_list;
 queue<int> tabu_operator;
/////////////////////////// Functions Declaration ///////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////// 

//////////////////////// Global Variable Declaration ////////////////////////////////////
 int Width_Initial;
 int Height_Initial;
 int Width_Final;
 int Height_Final;
 int tabu_max = 500000000;
 int random1_final;
 int random2_final;
 int move_final;
 int current_Delta_Total;
 int count_tabu = 0;
void calculate_fanin_out()
{
	vector<block*>::iterator iter;
	iter=B_ptr.begin();
	vector<block*>::iterator iter1;
	iter1=B_ptr.begin();

	for(iter=B_ptr.begin(); iter != B_ptr.end(); iter++)
	{
		(*iter)->fanIn_HCG.clear();
		(*iter)->fanOut_HCG.clear();
		(*iter)->fanIn_VCG.clear();
		(*iter)->fanOut_VCG.clear();
	}


	for(iter=B_ptr.begin();iter!=B_ptr.end();iter++)
	{
		for(iter1=B_ptr.begin();iter1!=B_ptr.end();iter1++)
		{
	   		if((*iter)->name != (*iter1)->name)
	    		{
				if((*iter)->pos_position > (*iter1)->pos_position && (*iter)->neg_position < (*iter1)->neg_position)
				{
					(*iter)->fanOut_VCG.push_back(&(*(*iter1)));
					(*iter1)->fanIn_VCG.push_back(&(*(*iter)));
					//cout << (*iter)->name << endl;
                        		//cout<<"inside"<<endl;
				}

				if((*iter)->pos_position < (*iter1)->pos_position && (*iter)->neg_position < (*iter1)->neg_position)
				{
					(*iter)->fanOut_HCG.push_back(&(*(*iter1)));
					(*iter1)->fanIn_HCG.push_back(&(*(*iter)));
					//cout << (*iter)->name << endl;
					//cout<<"Entering Once"<<endl;
				}
	    		}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////// ### Function to calculate HCG and the VCG //////////////////////////////////////
////////////////////////////////        for each iteration of Annealing   ///////////////////////////////////////

void calculate_HCG_VCG()
{
	Width_Final = 0;
	Height_Final = 0;
	
	///////////////////////////////////// Traverse the HCG and VCG Graphs //////////////////////////////////////////
	for(int k=0; k<B_ptr.size(); k++)
	{
		B_ptr[k]->ip_cnt_hcg = (*B_ptr[k]).fanIn_HCG.size();
		B_ptr[k]->ip_cnt_vcg = (*B_ptr[k]).fanIn_VCG.size();
		B_ptr[k]->x_coord = 0;
		B_ptr[k]->y_coord = 0;
		if((*B_ptr[k]).fanIn_HCG.size() == 0)
		{
			(*B_ptr[k]).x_coord = 0;
			//cout << "Block: " << (*B_ptr[k]).name << "\tX-coordinate: " << (*B_ptr[k]).x_coord << endl;
			queue_HCG.push(B_ptr[k]);
		}

		if((*B_ptr[k]).fanIn_VCG.size() == 0)
		{
			(*B_ptr[k]).y_coord = 0;
			//cout << "Block: " << (*B_ptr[k]).name << "\tY-coordinate: " << (*B_ptr[k]).y_coord << endl;
			queue_VCG.push(B_ptr[k]);
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////// Traverse the VCG and assign the y-positions ////////////////////////////////////
	//cout << queue_VCG.size() << endl; 
	while(!queue_VCG.empty())
	{
		//cout << "VCG Queue" << endl;
		block* b = queue_VCG.front();
		for(int i=0; i < (*b).fanOut_VCG.size(); i++)
		{
			//cout << "Entering For" << endl;
			block* Out = (*b).fanOut_VCG[i];
			Out->ip_cnt_vcg--;
			////////////////////////// Check for the Maximum Distance ///////////////////////////
			if(b->y_coord+b->Height > Out->y_coord)
				Out->y_coord = b->y_coord+b->Height;

			// Could be commented back in later
			//if(Height_Final < Out->y_coord + Out->Height)
				//Height_Final = Out->y_coord + Out->Height;
				//cout << "Entering If" <<endl;
			/////////////////////////////////////////////////////////////////////////////////////		
			if(Out->ip_cnt_vcg == 0)
			{
				//Out->y_coord = b->y_coord+b->Height;
				//cout << "Entering here" << endl;
				queue_VCG.push(Out);
				//cout << "Block Name: " << Out->name << "\tBlock y-coordinate: " << Out->y_coord << endl;
			}

		}
		queue_VCG.pop();
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////// Traverse the HCG and assign the x-positions ///////////////////////////////////

	while(!queue_HCG.empty())
	{
		//cout << "HCG Queue" << endl;
		block* b = queue_HCG.front();
		for(int i=0; i < (*b).fanOut_HCG.size(); i++)
		{
			block* Out = (*b).fanOut_HCG[i];
			Out->ip_cnt_hcg--;
			////////////////////////// Check for the Maximum Distance ///////////////////////////
			if(b->x_coord + b->Width > Out->x_coord)
				Out->x_coord = b->x_coord + b->Width;
				//cout << "Doin it! X-Coordinate" << endl;

			/////////////////////////////////////////////////////////////////////////////////////
			// Could be commented back in later			
			//if(Width_Final < Out->x_coord + Out->Width)
			//	Width_Final = Out->x_coord + Out->Width;
			/////////////////////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////		
			if(Out->ip_cnt_hcg == 0)
			{
				//Out->x_coord = b->x_coord+b->Width;
				queue_HCG.push(Out);
				//cout << "Block Name: " << Out->name << "\tBlock x-coordinate: " << Out->x_coord << endl;
			}

		}
		queue_HCG.pop();
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////// Final Width and Height Calculations for the Chip ///////////////////////////////
	
	for(int k=0;k<B_ptr.size();k++)
	{
		if(Width_Final < (*B_ptr[k]).x_coord + (*B_ptr[k]).Width)
			Width_Final = (*B_ptr[k]).x_coord + (*B_ptr[k]).Width;
		if(Height_Final < (*B_ptr[k]).y_coord + (*B_ptr[k]).Height)
			Height_Final = (*B_ptr[k]).y_coord + (*B_ptr[k]).Height;
	}	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////// ### Function to Swap 2 elements of the Positive Sequence /////////////////////////////

void swap_positive(int x, int y, double Temperature)
{
	//cout << "Blocks being swapped are: " << B_ptr[x]->name <<" " << B_ptr[y]->name << endl;
	swap(B_ptr[x]->pos_position,B_ptr[y]->pos_position);
	calculate_fanin_out();
	calculate_HCG_VCG();
	// if (Temperature < 20){
	// double unrotate_area = calculate_Area();
	// int move = rand()%3;

	// if(move==0)
	// 	rotate_both(x,y);
	// else if(move == 1)
	// 	rotate_x(x);
	// else if(move == 2)
	// 	rotate_y(y);	
	// calculate_fanin_out();
	// calculate_HCG_VCG();
	// double rotate_area = calculate_Area();
	// if (unrotate_area<rotate_area){
	// 	if(move==0)
	// 		rotate_both(x,y);
	// 	else if(move == 1)
	// 		rotate_x(x);
	// 	else if(move == 2)
	// 		rotate_y(y);		
	// }
	// calculate_fanin_out();
	// calculate_HCG_VCG();
	// }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////// ### Function to Swap 2 elements of the Negative Sequence /////////////////////////////

void swap_negative(int x, int y, double Temperature)
{
	//cout << "Blocks being swapped are: " << B_ptr[x]->name <<" " << B_ptr[y]->name << endl;
	swap(B_ptr[x]->neg_position,B_ptr[y]->neg_position);
	calculate_fanin_out();
	calculate_HCG_VCG();
// 	if (Temperature<20){
// 	double unrotate_area = calculate_Area();
// 	int move = rand()%3;

// 	if(move==0)
// 		rotate_both(x,y);
// 	else if(move == 1)
// 		rotate_x(x);
// 	else if(move == 2)
// 		rotate_y(y);	
// 	calculate_fanin_out();
// 	calculate_HCG_VCG();
// 	double rotate_area = calculate_Area();
// 	if (unrotate_area<rotate_area){
// 		if(move==0)
// 			rotate_both(x,y);
// 		else if(move == 1)
// 			rotate_x(x);
// 		else if(move == 2)
// 			rotate_y(y);		
// 	}
// 	calculate_fanin_out();
// 	calculate_HCG_VCG();
// 	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////// ### Function to Swap 2 elements of Both Sequences ////////////////////////////////////

void swap_both(int x, int y, double Temperature)
{
	//cout << "Blocks being swapped are: " << B_ptr[x]->name <<" " << B_ptr[y]->name << endl;
	swap(B_ptr[x]->pos_position,B_ptr[y]->pos_position);
	swap(B_ptr[x]->neg_position,B_ptr[y]->neg_position);
	calculate_fanin_out();
	calculate_HCG_VCG();
	// if (Temperature < 20){
	// double unrotate_area = calculate_Area();
	// int move = rand()%3;

	// if(move==0)
	// 	rotate_both(x,y);
	// else if(move == 1)
	// 	rotate_x(x);
	// else if(move == 2)
	// 	rotate_y(y);	
	// calculate_fanin_out();
	// calculate_HCG_VCG();
	// double rotate_area = calculate_Area();
	// if (unrotate_area<rotate_area){
	// 	if(move==0)
	// 		rotate_both(x,y);
	// 	else if(move == 1)
	// 		rotate_x(x);
	// 	else if(move == 2)
	// 		rotate_y(y);		
	// 	}
	// 	calculate_fanin_out();
	// 	calculate_HCG_VCG();
	// }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void rotate_both(int x, int y){

	int Width = B_ptr[x]->Width;
	int Height = B_ptr[x]->Height;
	B_ptr[x]->Width = Height;
	B_ptr[x]->Height = Width;
	if (B_ptr[x]->rotate == 0){
		B_ptr[x]->rotate = 1;
	}
	else{
		B_ptr[x]->rotate = 0;
	}
	int Width_y = B_ptr[y]->Width;
	int Height_y = B_ptr[y]->Height;
	B_ptr[y]->Width = Height_y;
	B_ptr[y]->Height = Width_y;	
	if (B_ptr[y]->rotate == 0){
		B_ptr[y]->rotate = 1;
	}
	else{
		B_ptr[y]->rotate = 0;
	}


}


void rotate_x(int x){

	int Width = B_ptr[x]->Width;
	int Height = B_ptr[x]->Height;
	B_ptr[x]->Width = Height;
	B_ptr[x]->Height = Width;
	if (B_ptr[x]->rotate == 0){
		B_ptr[x]->rotate = 1;
	}
	else{
		B_ptr[x]->rotate = 0;
	}
}


void rotate_y(int y){

	int Width = B_ptr[y]->Width;
	int Height = B_ptr[y]->Height;
	B_ptr[y]->Width = Height;
	B_ptr[y]->Height = Width;
	if (B_ptr[y]->rotate == 0){
		B_ptr[y]->rotate = 1;
	}
	else{
		B_ptr[y]->rotate = 0;
	}
}
///////////////////////////// ### Function to Calculate the Intermediate Areas //////////////////////////////////
double calculate_Area()
{
	double area=0;
	return Width_Final*Height_Final;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////// ### Accept Move /////////////////////////////////////
bool AcceptedMove(double Delta,double Temperature)
{
	if(Delta < 0) return 1;
	double boltzman_const = exp(((-1)*(Delta))/((Temperature*0.95)));
	double random_compare =((double)rand()/(double)RAND_MAX);
	if(random_compare<boltzman_const)
		return 1;
	else return 0;
}

bool Tabu_judgement(int random1, int random2, int move){
	pair<int, int> combine;
	int operator1 = 0;
	for(int i = 0; i < tabu_list.size();i++){
		combine = tabu_list.front();
		operator1 = tabu_operator.front();
		if (combine.first == random1 && combine.second == random2 && operator1 == move){
			return false;
		}
		
	}
	return true;
}