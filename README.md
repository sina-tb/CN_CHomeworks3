#CN_CHomeworks3
## Code Structure
The code consists of three classes:
  * **Edge** : This class has three attributes:
    * node1 : The first node of the edge.
    * node2 : The second node of the edge.
    * weight : The wieght of the edge.
  
  The picture below shows the **Edge** class:
  
  ![Screenshot from 2023-06-05 10-56-49](https://github.com/sina-tb/CN_CHomeworks3/assets/88041997/0ab4159b-868b-478a-b55e-dd28cf8aa2e1)
  
  * **Node**: This class has two attributes. Also, this class has some **methods** that can be explained by their name, so the explanation of methods are unnecessary.
    * Id : Shows the id number of node in graph
    * Edges: A vector of **Edge** objects that their first node is equal to the **Id** of the node. in other word, a vector consist of all edges that are connected to neighbors of the node.
    
  The picture below shows the **Node** class:
  
  ![Screenshot from 2023-06-05 11-07-48](https://github.com/sina-tb/CN_CHomeworks3/assets/88041997/b96fe8aa-3680-4287-98c0-aeab262def40)
  
  * **Graph**: This class has one attribute. Also, this class has some **methods** that we explain them later.
    * Nodes : A vector of all nodes that have been added to graph so far.
   
   
  The picture below shows the **Graph** class:
  
  ![Screenshot from 2023-06-05 11-12-39](https://github.com/sina-tb/CN_CHomeworks3/assets/88041997/78d5793b-4dd7-4bb4-8c3f-48aa18d2a3d5)
  
  The following picture shows **Customer** class:

  ![image](https://github.com/sina-tb/CN_CHomeworks3/assets/98649020/70b48461-065a-4058-b86d-640d647e8112)

  * **Customer**: this class is the base of inheritance for the `Provider` class (so a `Provider` can be a `Customer` as well).
  * _prvoiders: indicates the providers for this customer
  * _prvLengthPref: holds a provider ID along with its length of connection and its preference to that provider
  
  The following picture shows **Provider** class:
  
  ![image](https://github.com/sina-tb/CN_CHomeworks3/assets/98649020/e582ac12-4062-4451-ad93-f18c60d1f836)
  
  * _cstmLengthPref: list of customerIDs mapped to their length and preferences.
  * _peerLengthPref: list of peerIDs mapped to their path length and prefernce.
  * _routeTable: routing information about a prefix(ASID) mapped to the its nextHop and the path length. 
  
  Picture of **BGP** class:
  
  ![image](https://github.com/sina-tb/CN_CHomeworks3/assets/98649020/434cff0c-00c1-44c9-9c56-82207ff8c394)
  
  _potentialCustomers: list of Customers and Providers(which can also be a customer) on the network.
  
  **Note**: we can classify **AS**s as follows:
  * Stub AS
  * Multihomed AS
  * Transit AS
  
  For simplicity we excluded Transit AS in out project, however one could argue that having a multihomed AS is more difficult than a Transit AS, because, 
  a Multihomed AS can be a customer and a provider at the same time.
  
  
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
 
  ![4](https://github.com/sina-tb/CN_CHomeworks3/assets/88041997/549ccd1e-b34c-4722-b69a-6820e2a85f59)
 ### BGP
 At first after entering 2 in the menu and `bgp` after that, user will encounter a *BGP* Menu as follows:
 
 ![image](https://github.com/sina-tb/CN_CHomeworks3/assets/98649020/14776344-40e3-4fcf-801d-5ccd609b6ec3)
 
 after choosing each option a guide for the chosen command will be printed for the user.
 Here we will go forward on a few examples:
 
 #### Add Provider/Add Customer
 after pressing `1` or `2` on the BGP menu, the command guide corresponding to each option will be appeared:
 
![image](https://github.com/sina-tb/CN_CHomeworks3/assets/98649020/0e5d04ef-e111-48ff-af66-f831f087e579)
 
for example in this photo we chose the Add customer option
the *ASID* corresponds to id of the Autonomous System

#### Advertise routing
after pressing `5` on the BGP menu, we are able to announce a new routing path.
the first input would be the AS introducing this route (**note** that for simplicity we introduce `AS`s instead of `prefixes`).

![image](https://github.com/sina-tb/CN_CHomeworks3/assets/98649020/4614b9b1-26d8-4fc7-92f6-5b1483178dc0)

The first input indicates the *provider* which is inroducing the path.
The second input indicates the destination which would use this routing information (More likely another provider)
The third input indicates the actual prefix(i,e **AS**)
and the final input as it was described in the hint, the cost/length of the path.

#### Advertise Errors
##### Hijacked
Whenever an incoming route to a destination with a different source of what has already been in the routing table comes this error will be printed

![image](https://github.com/sina-tb/CN_CHomeworks3/assets/98649020/1bb876f5-58e8-4166-8f37-d6cacd38df20)

##### Role of Relations
If a AS `X` wants to advertise some routing information to AS `Y` two of which must be connected. Either by being peer of one another or by being in provider-customer relatioship

![image](https://github.com/sina-tb/CN_CHomeworks3/assets/98649020/69351128-11ad-46a9-85e9-121a29f3d86b)


#### Show Providers:
after pressing `6` on the menu each of the previously added providers will be printed one by one (their IDs)

![image](https://github.com/sina-tb/CN_CHomeworks3/assets/98649020/88156954-d521-4e00-be13-0b5a43f1d0f3)

 

 ### LSRP
 In this section we send information about directly connected links to all nodes (not just neighbors) then we used **Dijkstra's shortest path algorithm** to find the shortest path.It takes n iterations(n is number of nodes).Iteration start at source node and then we use information about directly connected links to this node and find shortest path,then after we confirm a new node(shortest cost),with information of it's directly connected links,we update the paths and find the shortest one again.after n iterastions we got shortest paths from source node. 
 
The result is shown in picture below:

![Screenshot from 2023-06-05 20-07-14](https://github.com/sina-tb/CN_CHomeworks3/assets/126562944/3a005d60-4450-489d-b5be-7b8c3533555c)

![Screenshot from 2023-06-05 20-07-40](https://github.com/sina-tb/CN_CHomeworks3/assets/126562944/89315a59-df1c-4de1-ab81-c669833479ee)
 
 ### Distance Vector(DVRP)
 The code of this secction is shown below. As you can see, we used **Bellman Ford algorithm** to find distance vector. we iterate over all edges in graph and update their weight and save the    lowest-price from each node to other nodes. If updating doesn't occur for all edges, we stop the algorithm:
 
 ![Screenshot from 2023-06-05 11-46-27](https://github.com/sina-tb/CN_CHomeworks3/assets/88041997/0475fd17-2c85-4049-b60f-a3aa131784d0)
 
 The result is shown in picture below:
 
 ![5](https://github.com/sina-tb/CN_CHomeworks3/assets/88041997/b76341c9-b978-4f84-98f6-7ef2da19932d)

 
## Comparison
time complexity of link state algorithm is O(v^3) and time complexity of distance vector is O(V.E) so we expect that lsrp is slower than dvrp and the tables below shows this too.

The Chart shown below is the time of each algorithm for each node in given graph **before** removing **4-10 Edge** (The time is micro-second):

Source | LSRP | DVRP |
--- | --- | --- |
1 | 508.429 | 97.221 |
2 | 588.393 | 86.267 |
3 | 658.618 | 86.776 |
4 | 557.613 | 88.452 |
5 | 541.48 | 90.255 |
6 | 506.863 | 86.889 |
7 | 514.849 | 84.488 |
8 | 625.234 | 90.364 |
9 | 497.395 | 64.518 |
10 | 762082 | 89.32 |
11 | 714.658 | 85.312 |
12 | 558.117 | 85.236 |
13 | 645.143 | 66.527 |

The Chart shown below is the time of each algorithm for each node in given graph **after** removing **4-10 Edge**  (The time is micro-second):

Source | LSRP | DVRP |
--- | --- | --- |
1 | 505.976 | 229.632 |
2 | 493.916 | 215.271 |
3 | 494.925 | 213.403 |
4 | 588.712 | 226.374 |
5 | 471.593 | 216.644 |
6 | 462.807 | 214.348 |
7 | 460.787 | 206.88 |
8 | 481.432 | 217.512 |
9 | 427.8 | 210.369 |
10 | 465.016 | 226.721 |
11 | 510.542 | 226.213 |
12 | 503.95 | 211.954 |
13 | 507.221 | 214.909 |


 
