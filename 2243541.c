//Author:Berk Limoncu ID:2243541
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define MAX 25

struct AOI{
	char name;
	int topLeftX;
	int width;
	int topLeftY;
	int height;
	int fixationCount;
	int dwellTime;
};

struct Fixation{
	int index;
	int x;
	int y;
	int duration;		
};

struct AOI* initialiseAOI(char *,int *);
struct Fixation* initialiseFixation(char *,int *);
void computeFixationCount(struct AOI*,struct Fixation*,int,int);
void computeDwellTime(struct AOI*,struct Fixation*,int,int);
void heapify(struct AOI*,int,int,int);
void buildHeap(struct AOI*,int,int);
void heapSort(struct AOI*,int,int);
void printAOIs(struct AOI *,int);
void swap(struct AOI *,struct AOI *);

void main(int argc,char *argv[])
{	
	printf("Welcome to Eye-tracking Data Analyser!\n\n");
	
	int i,sizeAOI,sizeFixation;
	int numberOfPeople=atoi(argv[4]);	//To convert # of people from string to integer in order to make iteration
	char fileName[MAX],pathName[MAX];
	
	struct AOI *myAOI;					//my initialized AOI list
	struct Fixation *myFixation;		
	
	
	myAOI=initialiseAOI(argv[2],&sizeAOI);
	
	
	for(i=1;i<=numberOfPeople;i++)	 //to read each person's data 1.txt 2.txt to n.txt
	{
		strcpy(pathName,argv[3]);	//pathname
		strcat(pathName,"/");		//pathname
	
		sprintf(fileName,"%d",i);
		strcat(fileName,".txt"); 	//file name as format x.txt where x is an integer 1 to numberOfPeople
		strcat(pathName,fileName);	//path+filename
		
		myFixation=initialiseFixation(pathName,&sizeFixation);
		computeFixationCount(myAOI,myFixation,sizeAOI,sizeFixation);
		computeDwellTime(myAOI,myFixation,sizeAOI,sizeFixation);
	}
	
	if(atoi(argv[1])==1)
		heapSort(myAOI,sizeAOI,1);	
	else if(atoi(argv[1])==2)
		heapSort(myAOI,sizeAOI,2);
	else
		printf("Please enter a valid sorting criteria!");
	
	printAOIs(myAOI,sizeAOI);
}
			

struct AOI* initialiseAOI(char *fileName,int *sizeAOI)
{
	FILE *myFile;
	
	myFile=fopen(fileName,"r");

	struct AOI temp;
	struct AOI *myData;
	
	int i=0;
	
	if(myFile == NULL) 	//Fail 
	{
		printf("Failed!\n");
		exit(0);
	}
	
	while(!feof(myFile)) 
	{
		fscanf(myFile,"%c %d %d %d %d\n",&temp.name,&temp.topLeftX,&temp.width,&temp.topLeftY,&temp.height);
		i++; //To determine the size of AOI
	}
	*sizeAOI=i;
	myData=malloc((*sizeAOI) * sizeof(struct AOI)); //Alocate AOI
	fclose(myFile);
	
	
	myFile=fopen(fileName,"r");
	
	if(myFile == NULL)
	{
		printf("Failed!\n");
		exit(0);
	}
	
	i=0;
	while(!feof(myFile))
	{
		fscanf(myFile,"%c %d %d %d %d\n",&myData[i].name,&myData[i].topLeftX,&myData[i].width,&myData[i].topLeftY,&myData[i].height); //To fill the AOI struct
		myData[i].dwellTime=0; //Initialize all dwell time as 0
		myData[i].fixationCount=0;	//Initialize all fixation count as 0
		i++;
	}
	
	printf("The %s file has been loaded succesfully!\n",fileName);
	fclose(myFile);
	
	
	return myData; //return as type of struct AOI
}

struct Fixation* initialiseFixation(char *fileName,int *sizeFixation)
{
	FILE *myFile;
	
	myFile=fopen(fileName,"r");

	struct Fixation temp;
	struct Fixation *myData;
	
	int i=0;
		
	if(myFile == NULL) //fail case
	{
		printf("Failed!\n");
		exit(0);
	}
	
	fscanf(myFile,"index x y duration\n"); //First line
	while(!feof(myFile))
	{
		fscanf(myFile,"%d %d %d %d\n",&temp.index,&temp.x,&temp.y,&temp.duration);
		
		i++; //To determine the size of fixation
	}
	*sizeFixation=i;
	fclose(myFile);
	
	myFile=fopen(fileName,"r");
	
	if(myFile == NULL)
	{
		printf("Failed!\n");
		exit(0);
	}
	
	myData=malloc(i*sizeof(struct Fixation)); //Alocate Fixation
	i=0;
	
	
	fscanf(myFile,"index x y duration\n"); //First line
	while(!feof(myFile))
	{
		fscanf(myFile,"%d %d %d %d\n",&myData[i].index,&myData[i].x,&myData[i].y,&myData[i].duration); //to fill fixation struct
		i++;
	}
	
	printf("The %s file has been loaded succesfully!\n",fileName);
	fclose(myFile);
	
	return myData; //return type as struct Fixation
}

void computeFixationCount(struct AOI *a,struct Fixation *f,int sizeAOI,int sizeFixation)
{
	int i,j;
	
	for(i=0;i<sizeAOI;i++)
	{
		for(j=0;j<sizeFixation;j++)
		{
			if( (a[i].topLeftX<=f[j].x) & (a[i].topLeftX+a[i].width>=f[j].x) & (a[i].topLeftY<=f[j].y) & (a[i].topLeftY+a[i].height>=f[j].y)) //If fixation appears on an AOI then it must be true
				a[i].fixationCount++;
		}
	}
}

void computeDwellTime(struct AOI *a,struct Fixation *f,int sizeAOI,int sizeFixation)
{
	int i,j;
	
	for(i=0;i<sizeAOI;i++)
	{
		for(j=0;j<sizeFixation;j++)
		{
			if( (a[i].topLeftX<=f[j].x) & (a[i].topLeftX+a[i].width>=f[j].x) & (a[i].topLeftY<=f[j].y) & (a[i].topLeftY+a[i].height>=f[j].y)) //If fixation appears on an AOI then dwelltime is dwell time+duration of each fixation
				a[i].dwellTime+=f[j].duration;
		}
	}
}
 
void heapify(struct AOI *a,int n,int i,int criteria) // my implementation is a little bit different 
{
	int largest=i;
	int l=2*i+1; 
	int r=2*i+2;
	if(criteria==1) //If criteria==1 then sort type is fixationCount
	{
		if(l<n && a[l].fixationCount > a[largest].fixationCount)
			largest=l;
	
		if(r<n && a[r].fixationCount > a[largest].fixationCount)
			largest=r;
	
		if(largest!=i)
		{
			swap(&a[i],&a[largest]);
			heapify(a,n,largest,criteria);
		}
	}
	else // Otherwise sort type is dwellTime
	{
		if(l<n && a[l].dwellTime > a[largest].dwellTime)
			largest=l;
	
		if(r<n && a[r].dwellTime > a[largest].dwellTime)
			largest=r;
	
		if(largest!=i)
		{
			swap(&a[i],&a[largest]);
			heapify(a,n,largest,criteria);
		}
	}
}

void buildHeap(struct AOI *a,int n,int criteria)
{
	int i;
	
	for(i= n/2- 1; i>=0;i--)
		heapify(a,n,i,criteria); 
}

void heapSort(struct AOI *a,int n,int criteria)
{
	int i;
	
	buildHeap(a,n,criteria);
	
	for(i=n-1;i>0;i--)
	{
		swap(&a[0],&a[i]);
		heapify(a,i,0,criteria);
	}
}

void printAOIs(struct AOI *a,int sizeAOI)
{
	int i;
	
	printf("AOI\t\tFixation-count\tDwell-time\n");
	
	for(i=sizeAOI-1;i>=0;i--)
		printf("%c\t\t%d\t\t%d ms\n",a[i].name,a[i].fixationCount,a[i].dwellTime);
}

void swap(struct AOI *a,struct AOI *b) //typical swap code with pass by reference
{
	struct AOI temp; 
	
	temp.name=a->name;
	temp.topLeftX=a->topLeftX;
	temp.width=a->width;
	temp.topLeftY=a->topLeftY;
	temp.height=a->height;
	temp.fixationCount=a->fixationCount;
	temp.dwellTime=a->dwellTime;
	
	a->name=b->name;
	a->topLeftX=b->topLeftX;
	a->width=b->width;
	a->topLeftY=b->topLeftY;
	a->height=b->height;
	a->fixationCount=b->fixationCount;
	a->dwellTime=b->dwellTime;
	
	b->name=temp.name;
	b->topLeftX=temp.topLeftX;
	b->width=temp.width;
	b->topLeftY=temp.topLeftY;
	b->height=temp.height;
	b->fixationCount=temp.fixationCount;
	b->dwellTime=temp.dwellTime;
}
//Author:Berk Limoncu ID:2243541
