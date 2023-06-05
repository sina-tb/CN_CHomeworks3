# CN_CHomeworks3
## Code Structure
The code consists of three classes:
  * **Edge** : This class has three attributes:
    * node1 : The first node of the edge.
    * node2 : The second node of the edge.
    * weight : The wieght of the edge.
  
  The picture below shows the **Edge** class:
  
  ![Screenshot from 2023-06-05 10-56-49](https://github.com/sina-tb/CN_CHomeworks3/assets/88041997/0ab4159b-868b-478a-b55e-dd28cf8aa2e1)
  
  * **Node**: Shis class has two attributes. Also, this class has some **methods** that can be explained by their name, so the explanation of methods are unnecessary.
    * Id : Shows the id number of node in graph
    * Edges: A vector of **Edge** objects that their first node is equal to the **Id** of the node. in other word, a vector consist of all edges that are connected to neighbors of the node.
    
  The picture below shows the **Node** class:
  
  ![Screenshot from 2023-06-05 11-07-48](https://github.com/sina-tb/CN_CHomeworks3/assets/88041997/b96fe8aa-3680-4287-98c0-aeab262def40)
  
  * **Graph**: This class has one attribute. Also, this class has some **methods** that we explain them later.
    * Nodes : A vector of all nodes that have been added to graph so far.
   
   
  The picture below shows the **Graph** class:
  
  ![Screenshot from 2023-06-05 11-12-39](https://github.com/sina-tb/CN_CHomeworks3/assets/88041997/78d5793b-4dd7-4bb4-8c3f-48aa18d2a3d5)
  
  
 ## Code Verification
 ### Topology
 The input graph is the given graph in project description:
 
 ![1](https://github.com/sina-tb/CN_CHomeworks3/assets/88041997/67e8f679-7eb7-4c79-8550-d54e0ab748bf)
 
 ### Show
 The adjacency matrix is shown below:
 
 ![2](https://github.com/sina-tb/CN_CHomeworks3/assets/88041997/1a45c02c-1e71-48c9-bd7c-8f8ce4790c15)
 
 ### Modify
 The modify command has been done on the graph shown in **Show** section:
 
 ![3](https://github.com/sina-tb/CN_CHomeworks3/assets/88041997/1b73dfe2-2a41-4022-b028-192340a046cc)
 
 ### Remove
 The remove command has been done on the graph shown in **Modify** section:
 
 ### BGP
 ### LSRP
 
 ![4](https://github.com/sina-tb/CN_CHomeworks3/assets/88041997/549ccd1e-b34c-4722-b69a-6820e2a85f59)
 
 ### Distance Vector(DVRP)
 The code of this secction is shown below. As you can see, we used **Bellman Ford algorithm** to find distance vector. we iterate over all edges in graph and update their weight and save the    lowest-price from each node to other nodes. If updating doesn't occur for all edges, we stop the algorithm:
 
 ![Screenshot from 2023-06-05 11-46-27](https://github.com/sina-tb/CN_CHomeworks3/assets/88041997/0475fd17-2c85-4049-b60f-a3aa131784d0)
 
 The result is shown in picture below:
 
 ![5](https://github.com/sina-tb/CN_CHomeworks3/assets/88041997/b76341c9-b978-4f84-98f6-7ef2da19932d)

 
## Comparison
The Chart shown below is the time of each algorithm for each node in given graph **before** removing **4-10 Edge** (The time is micro-second):

Source | BGP | LSRP | DVRP |
--- | --- | --- | --- |
1 |  |  | 97.221 |
2 |  |  | 86.267 |
3 |  |  | 86.776 |
4 |  |  | 88.452 |
5 |  |  | 90.255 |
6 |  |  | 86.889 |
7 |  |  | 84.488 |
8 |  |  | 90.364 |
9 |  |  | 64.518 |
10 |  |  | 89.32 |
11 |  |  | 85.312 |
12 |  |  | 85.236 |
13 |  |  | 66.527 |

The Chart shown below is the time of each algorithm for each node in given graph **after** removing **4-10 Edge**  (The time is micro-second):

Source | BGP | LSRP | DVRP |
--- | --- | --- | --- |
1 |  |  | 229.632 |
2 |  |  | 215.271 |
3 |  |  | 213.403 |
4 |  |  | 226.374 |
5 |  |  | 216.644 |
6 |  |  | 214.348 |
7 |  |  | 206.88 |
8 |  |  | 217.512 |
9 |  |  | 210.369 |
10 |  |  | 226.721 |
11 |  |  | 226.213 |
12 |  |  | 211.954 |
13 |  |  | 214.909 |

 
