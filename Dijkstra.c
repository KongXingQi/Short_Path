#include <stdio.h>

#define MAX_VEX 9
#define MAX_NUM 999



typedef struct
{
	int vexs[MAX_VEX];
	int arcs[MAX_VEX][MAX_VEX];
	int vexnum,arcnum;
}AMGraph;

void AMGraphCreate(AMGraph* G);

void AMGraphPrint(AMGraph G);

//最短路径 Dijkstra  
/*
	G    ----- 该图
	Varc ----- 源点
	P 	 ----- Patharc 顶点的上级关系
	D    ----- ShortPtahTable 各个顶点间的最短路径 
*/ 
void ShortTestPathDijkstra(AMGraph G,int Varc,int* P, int* D);

int main()
{
	int i,j;
	AMGraph G;
	int patharc[MAX_VEX];
	int shortpath[MAX_VEX];
	AMGraphCreate(&G);
	AMGraphPrint(G);
	ShortTestPathDijkstra(G,0,patharc,shortpath);
	
	for (i = 1; i < G.vexnum; i++)
	{

		printf("(0,%d) 的最短路径长度为 %d 倒序最短路径：",i,shortpath[i]); 	
		j = i;
		while(patharc[j] != -1)
		{
			printf("(%d,%d)",j,patharc[j]);
			j = patharc[j];
		}
		printf("\n");
	}
	
	
	return 0;
}


void AMGraphCreate(AMGraph* G)
{
	int i,j;
	
	G -> vexnum = 9;
	G -> arcnum = 16;
	
	
	//顶点
	for (i = 0; i < G -> vexnum; i++)
	{
		G -> vexs[i] = i;
	} 
	
	
	//初始化邻接矩阵 
	for (i = 0; i < G -> vexnum; i++)
	{
		for (j = 0; j < G -> vexnum; j++)
		{
			if(i == j)
			{
				G -> arcs[i][j] = 0;
			}
			else
			{
				G -> arcs[i][j] = MAX_NUM;
			}
		}
	}
	
	//录入边关系
	G->arcs[0][1]=1;
	G->arcs[0][2]=5; 
	G->arcs[1][2]=3; 
	G->arcs[1][3]=7; 
	G->arcs[1][4]=5; 

	G->arcs[2][4]=1; 
	G->arcs[2][5]=7; 
	G->arcs[3][4]=2; 
	G->arcs[3][6]=3; 
	G->arcs[4][5]=3;

	G->arcs[4][6]=6;
	G->arcs[4][7]=9; 
	G->arcs[5][7]=5; 
	G->arcs[6][7]=2; 
	G->arcs[6][8]=7;

	G->arcs[7][8]=4;
 
	for (i = 0; i < G -> vexnum; i++)
	{
		for (j = 0; j < G -> vexnum; j++)
		{
			if(G->arcs[i][j] != MAX_NUM)
			{
				G -> arcs[j][i] = G -> arcs[i][j];
			}
		}
	}
	 
	 
}

void AMGraphPrint(AMGraph G)
{
	int i,j;
	
	printf("该图中的顶点:\n");
	for (i = 0; i < G.vexnum; i++)
	{
		printf("%d ",G.vexs[i]);
	}
	
	printf("\n该图的邻接矩阵:\n");
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
		{
			if (G.arcs[i][j] != MAX_NUM)
			{
				printf("%d ",G.arcs[i][j]);
			}
			else
			{
				printf("%s ","∞");
			} 
		}
		
		printf("\n");
	}
}


//最短路径 Dijkstra  
/*
	G    ----- 该图
	Varc ----- 源点
	P 	 ----- Patharc 顶点的上级关系
	D    ----- ShortPtahTable 各个顶点间的最短路径 
*/ 
void ShortTestPathDijkstra(AMGraph G,int Varc,int* P, int* D)
{
	int i; 
	//final 表示为 1 表示完成， 0 则未完成 
	int final[MAX_VEX];
	
	//初始化 
	for (i = 0; i < G.vexnum; i++)
	{
		final[i] = 0;				//刚开始都未完成 
		D[i] = G.arcs[Varc][i];		//把第一个源点的边录入 
		P[i] = -1;					//全部初始化成 -1 
	}
	
	//源顶点到自身的路径为 0  
	final[Varc] = 1;
	D[Varc] = 0;
	
	//正式循环遍历每个顶点 
	for (i = 1; i < G.vexnum; i++)
	{
		int j,k;
		int min = MAX_NUM; 
		
		//遍历D数组找出其中的最短路径 
		for (j = 0; j < G.vexnum; j++)
		{
			//找最小，并且是未完成的 
			if (D[j] < min && final[j] != 1)
			{
				min = D[j];
				k = j;
			}
		}
		
		//将最短路径对应的顶点记录为完成 
		final[k] = 1;
		
		//因为新的顶点完成，所以去修改D数组，增加或修改新的最短路径
		for (j = 0; j < G.vexnum; j++)
		{
			//如新加入的 比 先有的小， 并且是未完成的 
			if(min + G.arcs[k][j] < D[j] && final[j] != 1)
			{
				//则进来替换 
				D[j] = min + G.arcs[k][j];
				//并且将前驱更新 
				P[j] = k;
			}	
		} 
	} 
	
}


















