#define MAX_SAMPLE 1500
#define SWAP(t,x,y) t=x;x=y;y=t;
#define MAX_ATTRIBUTES 1000
#define MAX_WORD_LENGTH 3000
#define MAX_CLASS 200

//typedef struct Node node;

struct Node
{
   
    float NumericPredict;
    float NumericAttributes[MAX_ATTRIBUTES];
    float distance;
    int validated;
};



//MATH FUNC 
float square(float t);
float absv(float a, float b);


//READING ARFF FILE

struct Node* readfile(char *,int *,int *,char *);

//KNN functions

float NUM_KNN(int index,int k,int predict_attr,struct Node* Sample,int *Sample_Num,int *Atttr_Num,char *Atttr_Seq);
