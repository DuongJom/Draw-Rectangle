#include<stdio.h>
#include<windows.h>
#define file "HCN.DAT"
typedef struct
{
    int width,height,x,y;
} RECTANGLE;

void typeRec(RECTANGLE *rec){
    printf("\tEnter the width: ");
    scanf("%d",&rec->width);
    printf("\tEnter the height: ");
    scanf("%d",&rec->height);
    printf("\tEnter the x coordinate: ");
    scanf("%d",&rec->x);
    printf("\tEnter the y coordinate: ");
    scanf("%d",&rec->y);
}

void inputListRec(RECTANGLE* recs, int n){
    for(int i=0;i<n;i++){
        if(i==0){
            printf("Type information of the 1st rectangle: \n");
        }
        else{
            printf("Type information of the %dth rectangle: \n",i+1);
        }
        typeRec((recs+i));
    }
}

void showRec(RECTANGLE rec){
    printf("%d\t%d\t%d\t%d\n",rec.width,rec.height,rec.x,rec.y);
}

void showList(RECTANGLE* recs, int n){
    for(int i=0;i<n;i++){
        showRec(recs[i]);
    }
}

void gotoXY(int x, int y){
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void draw(RECTANGLE *recs, int n){
    int i,j,k;
    for(i=0;i<n;i++){
        gotoXY(recs[i].x,recs[i].y);
        int currXCoord=recs[i].x, currYCoord=recs[i].y;
        for(j=0;j<recs[i].height;j++){
            gotoXY(currXCoord,currYCoord);
            for(k=0;k<recs[i].width;k++){
                if(k==0||k==recs[i].width-1||j==0||j==recs[i].height-1){
                    printf("*");
                }
                else{
                    printf(" ");
                }
            }
            currYCoord++;
            printf("\n");
        }
    }
}

void writeFile(RECTANGLE* recs, int n, char fileName[]){
    FILE* f = fopen(fileName,"w");
    fprintf(f,"%d\n",n);
    int i;
    for(i=0;i<n;i++){
        fprintf(f,"%d\t%d\t%d\t%d\n",recs[i].width,recs[i].height,recs[i].x,recs[i].y);
    }
    fclose(f);
}

void readFile(RECTANGLE* recs, int *n, char fileName[]){
    FILE* f = fopen(fileName,"r");
    if(!f){
        printf("Error read file!\n");
        return;
    }
    int m;
    fscanf(f,"%d",&m);
    n=&m;
    int i;
    for(i=0;i<*n;i++){
        fscanf(f,"%d%d%d%d",&recs[i].width,&recs[i].height,&recs[i].x,&recs[i].y);
    }
    fclose(f);
}

int main(){
    RECTANGLE recs[100];
    int n;
    printf("Enter number of rectangles: ");
    scanf("%d",&n);
    inputListRec(recs,n);
    system("cls");
    draw(recs,n);
    writeFile(recs,n,file);
    readFile(recs,&n,file);
    showList(recs,n);
    return 0;
}
