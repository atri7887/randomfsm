#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <math.h>
#include <ctime>

using namespace std;

struct node {
  long int id;
  long int level;
  long int number_of_inputs,number_of_outputs;
  vector<long int> inputs,outputs;
  string type;

};

string type_list[] = {"&","|","^","~^"}; //"~&","~|",
string type_out[] = {"&","|","^","~^","+","-","*","/","%"}; //this is used for choosing random funtions between stateout of different fsms



//   int * nodes_per_level_generator(long int number_of_nodes,long int number_of_levels){
//
//   int node_list[number_of_levels] ={0}; // stores the number of nodes stored in a level.
//   long int j=0;
//
//   for(long int i=0;i<number_of_nodes;i++){
//     j = rand()%number_of_levels ; // this genrates the level number randomly
//     node_list[j] += 1; // this stores the number of times a level got a hit
//
//   }
//
//   //make a code segment to check if any of the levels are empty
//   //also re evaluate the whole thing and check for mistakes and logical errors
//
//   for(long int i = 0; i<number_of_levels;i++){
//
//       if(node_list[i]==0){
//
//         j = i+1;
//         while(node_list[j]<2){
//           j++;
//         }
//
//         node_list[i] += 1;
//         node_list[j] -=1;
//
//       }
//
//   }
//
//   // cout<<"Nodes per level:\n";    // this if for prlong inting out the number of nodes per level
//   //
//   // for(long int i=0; i<number_of_levels;i++){
//   //   cout <<node_list[i] << endl;
//   // }
//
//
//   return node_list;
//
// }

 void graph_map(string entityname,long int inputs,long int outputs){

  long int levels,nodes;
  long int node_counter  = 0 ;
  long int possible_nodes = 0;
  long int i,j,k,l,value;
  long int number_of_fsm = 3;
  //long int number_of_states[number_of_fsm] = {2,2,2}; // always have numnber of state equal to log2 2^n else problem.

  // cout<<"enter the number of  and number of FSMs:"<<endl; // here total number of nodes is equal to inputs outputs and the long intermediate node elements.
  // cin >> number_of_fsm ;

  srand(time(0));

  number_of_fsm = rand()%5 + 2; //maximum of 7 fsm and minimum of 2 fsms

  levels = rand()%86 + 5 ; //maximum of 90 levels and minimum of 5 Levels

  k = inputs + outputs + levels + 1 ; //this will ensure that the number of nodes will greater than inputs + outputs + levels. thus each level will contain a minimum of 1 node
  nodes = rand()%200 + (k *2 ) ; // maximum of 220 nodes and minimum of k nodes



  long int number_of_states[number_of_fsm];

  // for(i=0;i<number_of_fsm;i++){
  //   cout  << "enter the number of states of FSM" << i <<":\n";
  //   cin >> number_of_states[i] ;
  // }

  for(i=0;i<number_of_fsm;i++){
    k = rand()%3 + 3 ;            // max 5 bits and min of 3 bits for number of states.
    number_of_states[i] = pow(2,k);
    cout <<"FSM"<<i<<" states: "<<number_of_states[i]<<", ";
  }

  cout<<endl;

  cout << "Inputs: " << inputs <<" " << "Outputs: " << outputs << " "  << "Levels: " << levels << " "  << "Nodes: " << nodes <<" FSMs :"<< number_of_fsm<< endl << endl;




  node graph[nodes];

  // random nodes per levels

//  int* nodes_in_level = nodes_per_level_generator((nodes - inputs - outputs),(levels-2)); // this passes the values of long intermideate nodes and the the long intermideate levels, where long intermideate means number of nodes/levels elcluding the input/output levels

//-+-+-+-+-+-+-+---+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+
// nodes per level nodes_per_level_generator

int number_of_nodes = nodes - inputs - outputs ;
int number_of_levels = levels-2 ;

int node_list[number_of_levels] ={0}; // stores the number of nodes stored in a level.
j=0;

for(long int i=0;i<number_of_nodes;i++){
  j = rand()%number_of_levels ; // this genrates the level number randomly
  node_list[j] += 1; // this stores the number of times a level got a hit

}

//make a code segment to check if any of the levels are empty
//also re evaluate the whole thing and check for mistakes and logical errors

for(long int i = 0; i<number_of_levels;i++){

    if(node_list[i]==0){

      j = i+1;
      while(node_list[j]<2){
        j++;
      }

      node_list[i] += 1;
      node_list[j] -=1;

    }

}




//-+-+-+-+-+-+-+-+-+-+--++-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+--+-+-+-+-+--+-+-+-+-+-+





   int* nodes_in_level = node_list ;


  long int nodes_per_level[levels];

  for(i=0;i<levels;i++){
    if(i==0){
      nodes_per_level[i]= inputs;
    } else if(i== levels-1){
      nodes_per_level[i] = outputs;
    } else {
      nodes_per_level[i] = *(nodes_in_level+i-1);
    }
  }


  //level iteration --- this stores the values of the attributes of the structure variable -- viz graph

  for(i = 0; i<levels ; i++){

    for(j=0;j<nodes_per_level[i];j++){   // node iterator per level

      if(i==0){

        graph[node_counter].type = "input";

      } else if(i==levels-1){

        graph[node_counter].type = "output";

      }else{
        k = rand()%(sizeof(type_list)/sizeof(type_list[0]));
        graph[node_counter].type = type_list[k];

      }

      graph[node_counter].id = node_counter;
      graph[node_counter].level = i ;


      if(i != 0){

        possible_nodes = 0;
        for(l=0;l<i;l++){
          possible_nodes += nodes_per_level[l];
        }

        graph[node_counter].number_of_inputs = rand()%possible_nodes + 1;          // gave  range from 1 to n -- this decides the number of inputs------ not present in the main code segment

        for(long int m =0;m<graph[node_counter].number_of_inputs;m++){


          long int condition =1;                                                          //searches for nodes present in the input vector to prevent duplication of nodes ------ not present in the main code segment
          value = rand()%possible_nodes  ;
          while(condition){


          //  find (graph[node_counter].inputs.begin(), graph[node_counter].inputs.end(), value);
            if (find (graph[node_counter].inputs.begin(), graph[node_counter].inputs.end(), value) != graph[node_counter].inputs.end()){
              value = rand()%possible_nodes  ;
            }else{
            //cout << "Element not found in myvector\n";
              condition = 0;
            }
          }



          graph[node_counter].inputs.push_back(value);
          graph[value].outputs.push_back(node_counter);


        }

      }


      node_counter++;
    }

  }

  // this is for calculating the number of outputs for each node

  for(i=0;i<nodes;i++){

    graph[i].number_of_outputs = graph[i].outputs.size();

  }

  // cout<<"Nodes per level:\n";    // this if for prlong inting out the number of nodes per level
  // j =0 ;
  // for(long int i=0; i<levels;i++){
  //   cout <<graph[i].number_of_inputs << endl;
  //   if(graph[i].type != "input"){
  //     j += graph[i].number_of_inputs;
  //     }
  //   }
  //   cout <<"total j: "<<j<<endl;


  //-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

// Verilog code generating area

// Operator Description
//
//    &        and
//   ~&        nand
//    |        or
//   ~|        nor
//    ^        xor
// ^~ or ~^    xnor



  vector<string> endpop;


  // string entityname = "samplebench";
  string testbenchname = entityname+".v";
  long int randnot=0; // this will randomly choose a not or and gate in case the number of inputs are 1 0 for and and 1 for not
  string randomnot[] = {"","~"};
  long int possiblecombo;


  ofstream myfile (testbenchname.c_str());
  if (myfile.is_open())
  { // entity declaration part
    myfile << "//Atri Chatterjee\n//University of Florida\n\n";


    // module start...... filename and entityname are the same for this code

    myfile << "module " << entityname << "(\n";

    myfile << "input [" << inputs-1 << ":0] in0,\n" << "output reg [" << outputs-1 <<":0] out0,\n" ;
    myfile << "input clk,\ninput rst);\n\n";

    //node declaration

    myfile << "reg ";

    for(i=0;i<nodes-1;i++){
      myfile << "node" << i << ",";
    }
    myfile << "node" << nodes -1 <<";\n\n" ;

    //stateout for diffrent fsm state declaration

    for(i=0;i<number_of_fsm;i++){

      myfile<<"reg ["<<outputs-1<<":0] stateout"<<i<<",";

      for(j=0;j<number_of_states[i];j++){  //removed -1 from here

        myfile<<"stateout"<<i<<"calculate"<<j<<",";

      }

      myfile<<"stateout"<<i<<"calculate"<<j<<";\n";

    }

    myfile <<endl;

    // combinational circuit/graph declaration site

    myfile << "always @ (*)\n\nbegin\n\n";

    for(i=0;i<nodes;i++){
      if(graph[i].type == "input"){
        myfile <<"  node"<<i<<" <= in0[" << i << "];\n";
      }else{
        if(graph[i].number_of_inputs == 1){
            randnot = rand()%2;
            myfile << "  node"<<i<<" <= "<< randomnot[randnot] <<"node"<<graph[i].inputs.back()<<";\n";

        }else{
            possiblecombo = graph[i].number_of_inputs - 1;
            myfile << "  node"<<i<<" <= ";
            while(possiblecombo){
              myfile << "node"<<graph[i].inputs.back()<<" ";
              k = rand()%(sizeof(type_list)/sizeof(type_list[0]));
              myfile << type_list[k] <<" ";
              graph[i].inputs.pop_back();
              possiblecombo--;
            }

            myfile << "node"<<graph[i].inputs.back()<<";\n";
        }
      }
    }

    for(i=0;i<number_of_fsm;i++){ // declaring the stateout_x_calculate_y statements
      for(j=0;j<number_of_states[i];j++){
        for(k=0;k<outputs;k++){
          myfile<<"  stateout"<<i<<"calculate"<<j<<"["<<k<<"]"<<" <= node"<<rand()%nodes<<";\n";
        }
      }
    }

    myfile <<endl<<endl;

    possiblecombo = number_of_fsm - 1;//carry on from here .... codes the output of the fsm which is combination of random functions to the outputs of all the fsms
    k = rand()%(sizeof(type_out)/sizeof(type_out[0]));
    myfile<<"  out0 <= ";
    while(possiblecombo){
      myfile<<"stateout"<<possiblecombo<<" ";
      myfile<<type_out[k]<<" ";
      possiblecombo--;
    }

    myfile<<"stateout"<<possiblecombo<<";\n";

    endpop.push_back("\n\nend\n"); // made change over here

    myfile <<endpop.back() << endl;
    endpop.pop_back();

    //fsm generating part

    for(i=0;i<number_of_fsm;i++){

      myfile << "reg ["<<log2(number_of_states[i])-1<<":0] state"<< i <<";\n" ;

    }

    myfile << "\nalways @ (posedge clk)\n\nbegin\n\n";

    myfile <<"  if(rst)\n  begin\n\n"; //if part where we are putting the states of the fsm at random upon reset

    for(i=0;i<number_of_fsm;i++){

      k = rand()%number_of_states[i];
      myfile << "    state"<< i <<" <= " <<log2(number_of_states[i])<<"'d"<<k<<";\n";

    }

    myfile <<"\n  end\n\n  else\n  begin\n\n"; //else part where the the next state is incremented by 1

    for(i=0;i<number_of_fsm;i++){

      myfile << "    state"<< i <<" <= state"<< i << " + 1'd1 ;\n" ;

    }

    for(i=0;i<number_of_fsm;i++){ // the next state part where output of each fsm is defined

      myfile<<"\n\n";
      myfile<<"   case(state"<<i<<")\n";

      for(j=0;j<number_of_states[i];j++){

        myfile<<"    "<<log2(number_of_states[i])<<"'d"<<j<<":\n    begin\n";
        myfile<<"      "<<"stateout"<<i<<" = stateout"<<i<<"calculate"<<j<<";\n";
        myfile<<"    end\n";

      }

      myfile<<"   endcase\n";

    }

    myfile <<"\n\n  end";

    endpop.push_back("\n\nend");

    myfile <<endpop.back() << endl;
    endpop.pop_back();

    endpop.push_back("\n\nendmodule");

    myfile <<endpop.back() << endl;
    endpop.pop_back();




    myfile.close();
  }
  else cout << "Unable to open file" ;


//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

  //test area
  for(i=0;i<nodes;i++){

      cout<<"Id: "<<graph[i].id<<" Level:  "<<graph[i].level<<" Number_of_inputs: "<<graph[i].number_of_inputs<<" Number_of_outputs: "<<graph[i].number_of_outputs<<" Type: "<<graph[i].type<<endl;
      cout << "Inputs: ";
      for(j=0;j<graph[i].inputs.size();j++){
        cout<<graph[i].inputs[j]<<" ";
      }
      cout <<endl<<"Outputs: ";

      for(j=0;j<graph[i].outputs.size();j++){
        cout<<graph[i].outputs[j]<<" ";
      }
      cout <<endl;

  }



}

int main(){

  long int i,j,retVal,inlow,inhigh,outlow,outhigh,inputs,outputs;
  int starting_number = 0 ;
  char name[200] ;
  cout <<"Enter the number of testbenches to be generated and the starting number of the file:\n";
  cin >> j >> starting_number ;

  cout <<"Enter the lower and upper bound of the inputs and outputs respectively.Total of four values:"<<endl;
  cin >> inlow >> inhigh >> outlow >> outhigh ;

  srand(time(0));

//this generates the inputs and outputs of the circuit for each iteration

  for(i=0;i<j;i++){
    retVal = sprintf(name, "abench_%d",starting_number);
    inputs = rand()%(inhigh - inlow) + inlow ;
    outputs = rand()%(outhigh - outlow) + outlow ;
    graph_map(name,inputs,outputs);
    starting_number++;
  }

  return 0;
}
