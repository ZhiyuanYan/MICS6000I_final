#pragma once
#ifndef BLOCK_H

#define BLOCK_H
#include <vector>


class block
{
public:
	int name;
	double Height;
	double Width;
	double x_coord;                  // Lower X-coordinate of the Block
	double y_coord;	              // Lower Y-coordinate of the Block
	int pos_position;             // Position of the Block in the Positive Sequence
	int neg_position;             // Position of the Block in the Negative Sequence
	std::vector<block*> fanIn_HCG;     // Fan-in for the Block in the Horizontal Graph
	std::vector<block*> fanOut_HCG;    // Fan-Out for the Block in the Horizontal Graph
	std::vector<block*> fanIn_VCG;     // Fan-in for the Block in the Vertical Graph
	std::vector<block*> fanOut_VCG;    // Fan-Out for the Block in the Vertical Graph
	int ip_cnt_hcg;
	int ip_cnt_vcg;
	int rotate;
public: void Block_initialize(int Block_Name, double w, double h);
};

#endif
