#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int main(int argc, char**argv){
    double time_spent = 0.0;
    clock_t begin = clock();
    clock_t begin2 = clock();

    FILE * infile;
    FILE * outfile;
    char stringIn[50];
    int numNodes;
    int numEdges;
    int i;
    int j;
    int k;
    int l = 0;
    int x = 0;
    int y;
    int z = 0;
    int s1;
    int s2;
    int in1;
    int in2;
    int node1;
    int node2;
    int weight;
    int** nodeArray;
    int** gain;
    int** partTracker;
    int* partA;
    int* partB;
    int* edgeOut;
    int* edgeIn;
    int* dVal;
    int* nLock;
    int* maxTrack;
    int itTrack = -999999;
    int itCount = 0;
    int cut = 0;
    int offset = 0;
    int max = 0;
    int temp;

    /*printf("Please enter an input file name.\n");
    fscanf(stdin, "%s", in);
    printf("\nPlease enter an output file name.\n ");
    fscanf(stdin, "%s", out);*/

    infile = fopen(argv[1], "r");
    outfile = fopen(argv[2], "w");

    //Initialize the nodes and edges.

    fscanf(infile, "%s", stringIn);
    fscanf(infile, "%d", &numNodes);
    fscanf(infile, "%s", stringIn);
    fscanf(infile, "%d", &numEdges);

    float p40num = .40 * (float)numNodes;
    float p60num = .60 * (float)numNodes;

    printf("NumNodes: %d\nNumEdges: %d\n", numNodes, numEdges);
    fprintf(outfile, "NumNodes: %d\nNumEdges: %d\n", numNodes, numEdges);

    //Check to see if the potential partitions

    if (((((float)numNodes/2) >= p40num) && (((float)numNodes/2) <= p60num)) == 0){
            printf("\n Partions too far out of balance! Ending.\n");
            fprintf(outfile, "\n Partions too far out of balance! Ending.\n");
    return 0;
    }

    //Creates dummy nodes based on how the difference between the two potential partitions.

    while(numNodes % 2 != 0){
        offset++;
        numNodes++;
    }

    //Create a 2D array of node x node, value held inside will be the weights of edges between the nodes.

    nodeArray = (int**)malloc(numNodes * sizeof(int*));
    for(i = 0; i < numNodes; i++){
        nodeArray[i] = (int*)malloc(numNodes * sizeof(int));
    }

    //Initialize the array of weights to all 0s.
    for(i = 0; i < numNodes; i++){
        for(j = 0; j < numNodes; j++){
            nodeArray[i][j] = 0;
        }
    }

    //Iterate through the file, taking the first node, second node, and weight.
    for(i = 0; i < numEdges; i++){
        fscanf(infile, "%d", &in1);
        fscanf(infile, "%d", &in2);
        fscanf(infile, "%d", &weight);

        //Test to see which node is the smaller node, and assign that value to node one.

        if(in1<in2){
            node1 = in1;
            node2 = in2;
        }
        else if(in2<in1){
            node1 = in2;
            node2 = in1;
        }
        else if (in1 == in2){
            node1 = in1;
            node2 = in2;
        }

        //Take the coordinates of the array - 1 to access the weight between the two nodes. Update the weights by adding the edges.

        nodeArray[node1 - 1][node2 - 1] = (nodeArray[node1 - 1][node2 - 1] + weight);
        nodeArray[node2 - 1][node1 - 1] = (nodeArray[node2 - 1][node1 - 1] + weight);
    }

    int psize = (numNodes/2);

    partA = (int*)malloc(psize * sizeof(int));
    partB = (int*)malloc(psize * sizeof(int));
    edgeOut = (int*)malloc(numNodes * sizeof(int));
    edgeIn = (int*)malloc(numNodes * sizeof(int));

    //Initialize the partitions, fill them with the first and second halves of the nodes, including any dummy nodes added. All dummy nodes will rest in B.


    for(i = 0; i < psize; i++)
        partA[i] = i+1;
    for(j = 0; j < psize; j++)
        partB[j] = i + j+1;



    printf("\nInitial Partition A\n");
    fprintf(outfile, "\nInitial Partition A\n");
    for(i = 0; i <psize; i++){
        printf("%d ",partA[i]);
        fprintf(outfile, "%d ",partA[i]);
    }
    printf("\nInitial Partition B\n");
    fprintf(outfile, "\nInitial Partition B\n");
    for(i = 0; i < psize; i++){
        printf("%d ", partB[i]);
        fprintf(outfile, "%d ", partB[i]);
    }

    //Initialize the Edge arrays to count the total edge weight for in and out for each node.

    for(i = 0; i < numNodes; i++){
        edgeIn[i] = 0;
        edgeOut[i] = 0;
    }

    //Find the initial Edges heading out.
    //Partition A

    for(i = 0; i < psize; i++){
        for (j = psize; j < numNodes; j++){
            edgeOut[i] = edgeOut[i] + nodeArray[j][i];
        }
    }

    //Partition B

    for(i = psize; i < numNodes; i++){
        for(j = 0; j < psize; j++){
            edgeOut[i] = edgeOut[i] + nodeArray[i][j];
        }
    }

    //Find the initial Edges in the partitions themselves.
    //Partition A

    for(i = 0; i < psize; i++){
        for(j = 0; j < psize; j++){
            if(i != j)
                edgeIn[i] = edgeIn[i] + nodeArray[i][j];
        }
    }

    //Partition B

    for (i = psize; i < numNodes; i++){
        for(j = psize; j < numNodes; j++){
            if(i != j)
                edgeIn[i] = edgeIn[i] + nodeArray[i][j];
        }
    }

    //Calculate the cut by add the out edges of one partition together.

    for(i = 0; i < psize; i++){
        cut = cut + edgeOut[i];
    }
    printf("\nInitial Cut: %d\n", cut);
    fprintf(outfile, "\nInitial Cut: %d\n", cut);

    //Initialize our Dvalues and The lock array

    dVal = (int*) malloc(numNodes*sizeof(int));
    nLock = (int*) malloc(numNodes*sizeof(int));
    maxTrack = (int*) malloc(psize * sizeof(int));

    for(i = 0; i < numNodes; i++){
        dVal[i] = 0;
        nLock[i] = 0;
    }

    //Calculate and print our initial D values.

    for(i = 0; i < numNodes; i ++){
        dVal[i] = edgeOut[i] - edgeIn[i];
    }

    //Initialize our gain array.

    gain = (int**) malloc(numNodes * sizeof(int*));
    for(i = 0; i < numNodes; i++){
        gain[i] = (int*) malloc(numNodes * sizeof(int));
    }

    //Set all gain values to negative infinity. This makes it so nodes that are connected to themselves, and dummy nodes, can't be moved.

    for(i = 0; i < numNodes; i++)
        for(j = 0; j < numNodes; j++)
            gain[i][j] = -999999;
    for(i = 0; i < psize; i++){
        for(j = 0; j < psize; j++){
            gain[partA[i]-1][partB[j]-1] = dVal[partA[i]-1] + dVal[partB[j]-1] - (2 * nodeArray[partA[i]-1][partB[j]-1]);
            gain[partB[j]-1][partA[i]-1] = gain[partA[i]-1][partB[j]-1];
        }
    }

    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Time elapsed is %f seconds", time_spent);
    fprintf(outfile, "Time elapsed is %f seconds", time_spent);

    //Initialize an array that saves the values of the partitions for each iteration.

    partTracker = (int**)malloc(numNodes * sizeof(int));
    for(i = 0; i < numNodes; i++)
        partTracker[i] = (int*)malloc(psize * sizeof(int));

//Loop until all nodes are locked. This will calculate the maximum gain, the updated d values, the updated gains, and then loop through using this info.
    while(x != numNodes){
        itCount++;
        printf("\nIteration %d\n", itCount);
        fprintf(outfile, "\nIteration %d\n", itCount);
        printf("----------------");
        fprintf(outfile,"----------------");

        //Determine our maximum gain.

        max = -999998;
        for(i = 0; i < psize; i++){
            for(j = 0; j < psize; j++){
                if(max < gain[partA[i]-1][partB[j]-1]){
                    max = gain[partA[i]-1][partB[j]-1];
                    s1 = i;
                    s2 = j;
                }
            }
        }

        //Add the max to the tracker to determine the largest partial sum.

        if(z == 0)
            maxTrack[z] = max;
        else
            maxTrack[z] = max + maxTrack[z-1];
        z++;

        //Add the swapped nodes the the locked array.

        nLock[x] = partB[s2];
        x++;
        nLock[x] = partA[s1];
        x++;

        //Swap the nodes

        temp = partB[s2];
        partB[s2] = partA[s1];
        partA[s1] = temp;

        //Display the new partitions.

        printf("\nPartition A\n");
        fprintf(outfile, "\nPartition A\n");
        for(i = 0; i < psize; i++){
            printf("%d ",partA[i]);
            fprintf(outfile, "%d ",partA[i]);
        }
        printf("\nPartition B\n");
        fprintf(outfile, "\nPartition B\n");
        for(i = 0; i < psize; i++){
            printf("%d ", partB[i]);
            fprintf(outfile, "%d ", partB[i]);
        }

        //Calculate the new cut.

        cut = cut - max;

        //Add the new partitions to the partition tracker.

        for(i = 0; i < psize; i++){
            partTracker[l][i] = partA[i];
        }
        l++;
        for(i = 0; i < psize; i++){
            partTracker[l][i] = partB[i];
        }
        l++;

        //Print the new cut and the locked nodes

        printf("\nCut = %d",cut);
        fprintf(outfile, "\nCut = %d",cut);

        printf("\nLocked Nodes\n");
        fprintf(outfile, "\nLocked Nodes\n");
        for(i = 0; i < numNodes; i++){
            printf("%d ", nLock[i]);
            fprintf(outfile, "%d ", nLock[i]);
        }

        printf("\n");
        fprintf(outfile, "\n");

        //iterate through the arrays. If the array value is in the locked nodes, skip the iteration.
        //First, part A since the formula for updating the cut depends on the nodes associated with the prior iterations partition.

        for(i = 0; i < psize; i++){
            for(j = 0; j < numNodes; j++){
                if(nLock[j] != partA[i]){
                    y=1;
                }
                else if(nLock[j] == partA[i]){
                    y=0;
                    break;
                }
            }
            if(y == 1){
            dVal[partA[i]-1] = dVal[partA[i]-1] + (2 * nodeArray[partA[i]-1][partB[s2]-1]) - (2 * nodeArray[partA[i]-1][partA[s1]-1]);
            }
        }

        //Same for part B.

        for(i = 0; i < psize; i++){
            for(j = 0; j < numNodes; j++){
                if(nLock[j] != partB[i]){
                    y=1;
                }
                else if(nLock[j] == partB[i]){
                    y=0;
                    break;
                }
            }
            if(y == 1){
            dVal[partB[i]-1] = dVal[partB[i]-1] + (2 * nodeArray[partB[i]-1][partA[s1]-1]) - (2 * nodeArray[partB[i]-1][partB[s2]-1]);
            }
        }

        //Using the same methodology, calculate the new gains.

        for(i = 0; i < psize; i++){
            for(j = 0; j < psize; j++){
                for(k = 0; k<numNodes; k++){
                    if((nLock[k] != partB[j]) && (nLock[k] != partA[i])){
                        y=1;
                    }
                    else if((nLock[k] == partB[j]) || (nLock[k] == partA[i])){
                        y=0;
                        break;
                    }
                }
                if(y == 1){
                gain[partA[i]-1][partB[j]-1] = dVal[partA[i]-1] + dVal[partB[j]-1] - (2 * nodeArray[partA[i]-1][partB[j]-1]);
                gain[partB[j]-1][partA[i]-1] = gain[partA[i]-1][partB[j]-1];
                }
            }
        }

        //Change all gains for the gains associated with our locked nodes to -infinity (-999999).

        for(k = 0; k < x; k++){
            for(i = 0; i < psize; i++){
                gain[nLock[k]-1][partA[i]-1] = -999999;
                gain[partA[i]-1][nLock[k]-1] = gain[nLock[k]-1][partA[i]-1];
                gain[nLock[k]-1][partB[i]-1] = -999999;
                gain[partB[i]-1][nLock[k]-1] = gain[nLock[k]-1][partA[i]-1];
            }
        }
    }

    //Determine the largest partial sum and what iteration this sum occurs at.

    itCount = 0;
    for(i = 0; i < z; i++){
        if(itTrack < maxTrack[i]){
            itTrack = maxTrack[i];
            itCount = i;
        }
    }

    printf("\nThe maximum gain is %d after %d iteration(s). The minimum cut is %d\n", maxTrack[itCount], itCount + 1, cut - maxTrack[itCount]);
    fprintf(outfile, "\nThe maximum gain is %d after %d iteration(s). The minimum cut is %d\n", maxTrack[itCount], itCount + 1, cut - maxTrack[itCount]);
    clock_t end2 = clock();

    time_spent += (double)(end2 - begin2) / CLOCKS_PER_SEC;

    printf("\nTime elapsed for the final cut is %f seconds\n", time_spent);
    fprintf(outfile, "\nTime elapsed for the final cut is %f seconds\n", time_spent);

    //Reset our original numNodes.

    numNodes = numNodes - offset;

    //change all nodes that were dummy nodes to 0. Any nodes with values higher than the original numNodes will be dummy nodes.

    for(i = 0; i < psize; i++){
        if(partA[i] > numNodes)
            partA[i] = 0;
        if(partB[i] > numNodes)
            partB[i] = 0;
    }

    //Print our nodes, skipping any dummy nodes.

    for(i = 0; i < psize; i++){
        if(partTracker[itCount][i] != 0)
            printf("Node %d is in Partition A\n", partTracker[itCount][i]);
            fprintf(outfile, "Node %d is in Partition A\n", partTracker[itCount][i]);
    }
    for(i = 0; i < psize; i++){
        if(partTracker[itCount + 1][i] != 0)
            printf("Node %d is in Partition B\n", partTracker[itCount + 1][i]);
            fprintf(outfile, "Node %d is in Partition B\n", partTracker[itCount + 1][i]);
    }

    //Free our memory.

    fclose(infile);
    fclose(outfile);
    free(partA);
    free(partB);
    free(edgeOut);
    free(edgeIn);
    free(dVal);
    free(nLock);
    free(maxTrack);
    for(i = 0; i < numNodes + offset; i++);{
        free(nodeArray[i]);
        free(gain[i]);
        free(partTracker[i]);
    }
    free(nodeArray);
    free(gain);
    free(partTracker);
}
