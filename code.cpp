#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct node {
  int id;
  int level;
  int number_of_inputs,number_of_outputs;
  vector<int> inputs,outputs;
  string type;

};

string type_list[] = {"and","or","not","adder","subtractor","multiplier","divider","mux","modulus"};



int * nodes_per_level_generator(int number_of_nodes,int number_of_levels){

  int node_list[number_of_levels] ={0}; // stores the number of nodes stored in a level.
  int j=0;

  for(int i=0;i<number_of_nodes;i++){
    j = rand()%number_of_levels ; // this genrates the level number randomly
    node_list[j] += 1; // this stores the number of times a level got a hit

  }

  //make a code segment to check if any of the levels are empty
  //also re evaluate the whole thing and check for mistakes and logical errors

  for(int i = 0; i<number_of_levels;i++){

      if(node_list[i]==0){

        j = i+1;
        while(node_list[j]<2){
          j++;
        }

        node_list[i] += 1;
        node_list[j] -=1;

      }
  }


  return node_list;

}

 void graph_map(){

  int inputs,outputs,levels,nodes;
  int node_counter  = 0 ;
  int possible_nodes = 0;
  int i,j,k,l,value;


  cout<<"enter the number of inputs,outputs,levels and total number of nodes"<<endl; // here total number of nodes is equal to inputs outputs and the intermediate node elements.
  cin >> inputs >> outputs >> levels >> nodes;
  cout << "Inputs: " << inputs <<" " << "Outputs: " << outputs << " "  << "Levels: " << levels << " "  << "Nodes: " << nodes << endl;

  node graph[nodes];

  // random nodes per levels

  int* nodes_in_level = nodes_per_level_generator((nodes - inputs - outputs),(levels-2)); // this passes the values of intermideate nodes and the the intermideate levels, where intermideate means number of nodes/levels elcluding the input/output levels
  int nodes_per_level[levels];

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

        for(int m =0;m<graph[node_counter].number_of_inputs;m++){


          int condition =1;                                                          //searches for nodes present in the input vector to prevent duplication of nodes ------ not present in the main code segment
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

  graph_map();

  return 0;
}
