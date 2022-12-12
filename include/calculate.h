#pragma once
#ifndef CALCULATE_H
#define CALCULATE_H

     #include <bits/stdc++.h>
     #include "block.h"
     using namespace std;
     ///////////////////////// Vectors and Vector Lists //////////////////////////////////////


     extern void swap_positive(int x, int y, double Temperature);
     extern void swap_negative(int x, int y, double Temperature);
     extern void swap_both(int x, int y , double Temperature);
     extern void rotate_both(int x, int y);
     extern void rotate_x(int x);
     extern void rotate_y(int y);
     extern void calculate_HCG_VCG();
     extern void calculate_fanin_out();
     extern double calculate_Area();
     extern bool AcceptedMove(double Delta,double Temperature);
     extern bool Tabu_judgement(int random1, int random2, int move);

     extern vector<block> B;
     extern vector<block*> B_ptr;
     extern vector<list<block*> > vector_blocks;
     extern vector<block*> pos_seq;
     extern vector<block*> neg_seq;

     /////////////////////// Queues used for HCG and VCGs ////////////////////////////////////
     extern queue<block*> queue_HCG;
     extern queue<block*> queue_VCG;
     /////////////////////// Queues used for HCG and VCGs ////////////////////////////////////
     extern queue<pair<int,int>> tabu_list;
     extern queue<int> tabu_operator;
     /////////////////////////// Functions Declaration ///////////////////////////////////////


     ///////////////////////////////////////////////////////////////////////////////////////// 

     //////////////////////// Global Variable Declaration ////////////////////////////////////
     extern int Width_Initial;
     extern int Height_Initial;
     extern int Width_Final;
     extern int Height_Final;
     extern int tabu_max;
     extern int random1_final;
     extern int random2_final;
     extern int move_final;
     extern int current_Delta_Total;
     extern int count_tabu;
#endif