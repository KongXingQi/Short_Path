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

//Floyd 弗罗伊德算法 
void ShortTestPathFloyd(AMGraph G,int P[][MAX_VEX],int D[][MAX_VEX]);

int main()
{
	AMGraph G;
	int i, j;
	int patharc[MAX_VEX][MAX_VEX];
	int shortpath[MAX_VEX][MAX_VEX];
	AMGraphCreate(&G);
	AMGraphPrint(G);
	ShortTestPathFloyd(G,patharc,shortpath);


	//查看所有只需再加一层循环 将 下面的 0 改为 变量即可 
	for (i = 0; i < G.vexnum; i++)
	{
		int v;
		printf("(0,%d)的最短路径长度是%d,路径是:",i,shortpath[0][i]);
		v = 0;
		while (patharc[v][i] != i)
		{
			printf("(%d,%d)", v, patharc[v][i]);
			v = patharc[v][i];
		}
		printf("(%d,%d)\n", v, patharc[v][i]);
	}
	
	
	
	printf("最短路径长度图为:\n");
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
		{
			printf("%-2d ",shortpath[i][j]);
		}
		printf("\n");
	}
	
		
	printf("最短路径长度图为:\n");
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
		{
			printf("%-2d ",patharc[i][j]);
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


//Floyd 弗罗伊德算法 
void ShortTestPathFloyd(AMGraph G,int P[][MAX_VEX],int D[][MAX_VEX])
{
	int k,v,w;
	
	
	//初始化P和D两个矩阵
	for (v = 0; v < G.vexnum;v++)
	{
		for (w = 0; w < G.vexnum; w++)
		{
			D[v][w] = G.arcs[v][w];		//邻接矩阵副本
			P[v][w] = w;				//路径 
		}
	}
	
	
	
	//三层for循环
	//k是中转节点  
	for (k = 0; k < G.vexnum; k++)
	{
		//v 是开始节点 
		for (v = 0; v < G.vexnum; v++)
		{
			//w 是结尾节点
			for (w = 0; w < G.vexnum; w++)
			{
				if(D[v][w] > D[v][k] + D[k][w])
				{
					D[v][w] = D[v][k] + D[k][w];
					P[v][w] = P[v][k]; 
				}	
			} 
		}
	} 
}





















