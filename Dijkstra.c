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

//���·�� Dijkstra  
/*
	G    ----- ��ͼ
	Varc ----- Դ��
	P 	 ----- Patharc ������ϼ���ϵ
	D    ----- ShortPtahTable �������������·�� 
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

		printf("(0,%d) �����·������Ϊ %d �������·����",i,shortpath[i]); 	
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
	
	
	//����
	for (i = 0; i < G -> vexnum; i++)
	{
		G -> vexs[i] = i;
	} 
	
	
	//��ʼ���ڽӾ��� 
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
	
	//¼��߹�ϵ
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
	
	printf("��ͼ�еĶ���:\n");
	for (i = 0; i < G.vexnum; i++)
	{
		printf("%d ",G.vexs[i]);
	}
	
	printf("\n��ͼ���ڽӾ���:\n");
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
				printf("%s ","��");
			} 
		}
		
		printf("\n");
	}
}


//���·�� Dijkstra  
/*
	G    ----- ��ͼ
	Varc ----- Դ��
	P 	 ----- Patharc ������ϼ���ϵ
	D    ----- ShortPtahTable �������������·�� 
*/ 
void ShortTestPathDijkstra(AMGraph G,int Varc,int* P, int* D)
{
	int i; 
	//final ��ʾΪ 1 ��ʾ��ɣ� 0 ��δ��� 
	int final[MAX_VEX];
	
	//��ʼ�� 
	for (i = 0; i < G.vexnum; i++)
	{
		final[i] = 0;				//�տ�ʼ��δ��� 
		D[i] = G.arcs[Varc][i];		//�ѵ�һ��Դ��ı�¼�� 
		P[i] = -1;					//ȫ����ʼ���� -1 
	}
	
	//Դ���㵽�����·��Ϊ 0  
	final[Varc] = 1;
	D[Varc] = 0;
	
	//��ʽѭ������ÿ������ 
	for (i = 1; i < G.vexnum; i++)
	{
		int j,k;
		int min = MAX_NUM; 
		
		//����D�����ҳ����е����·�� 
		for (j = 0; j < G.vexnum; j++)
		{
			//����С��������δ��ɵ� 
			if (D[j] < min && final[j] != 1)
			{
				min = D[j];
				k = j;
			}
		}
		
		//�����·����Ӧ�Ķ����¼Ϊ��� 
		final[k] = 1;
		
		//��Ϊ�µĶ�����ɣ�����ȥ�޸�D���飬���ӻ��޸��µ����·��
		for (j = 0; j < G.vexnum; j++)
		{
			//���¼���� �� ���е�С�� ������δ��ɵ� 
			if(min + G.arcs[k][j] < D[j] && final[j] != 1)
			{
				//������滻 
				D[j] = min + G.arcs[k][j];
				//���ҽ�ǰ������ 
				P[j] = k;
			}	
		} 
	} 
	
}


















