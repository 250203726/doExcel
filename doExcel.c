#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
 * ��޶�400���û����� 
 * Excel���밴�ո�ʽ���ABCD���зֱ�����ϴ�ͳ���û������ϴ�ͳ�Ʒ���������ͳ���û���������ͳ�Ʒ���
 */
struct user
{
    char name[50];
    int score;
    int score2;
}user1[400],user2[400],user3[400];

void charRead1(){
    
    FILE *fp;
    char filename[40]  ;
    int i,j ;
    float da[6][5] = {0} ;
    fp=fopen("undoSheet.csv","r");
    fseek(fp, 5L, SEEK_SET);   // ���ļ��ڶ��п�ʼ��ȡ
    for(i = 0 ;i < 6 ; i++)
        for(j = 0 ;j < 5 ; j++)
		{
			fscanf(fp,"%f",&da[i][j]);
			fseek(fp, 1L, SEEK_CUR);   /*fpָ��ӵ�ǰλ������ƶ�*/
		}
           
	for(i = 0 ;i < 6 ; i++)
        printf("%f\t%f\t%f\t%f\t%f\t\n",da[i][0],
         da[i][1],da[i][2],da[i][3],da[i][4]);

	getchar() ;
}
int main(){
    /**
     * ��ȡundoExcel.xls��ȡ�����ݵ�undoDate��
     */	
    int maxNum=300;//��ǰ�����������
    int lastNum=0;//�ϴ�ͳ������������
    int thisNum=0;//����ͳ����������
	FILE *fp1,*fp2;//�ļ���д��ָ��
	int i,j,n;//����
    char line[100];
    char *ps;
    
    printf("********CSV�ı����ݴ������--�ȶ�����ǰ��һ��********\n\nʹ��˵����\n1.ִ�г���ǰ��undoSheet.csv���ڳ����ͬһĿ¼\n2.���ո�ʽ���ABCD���У��ֱ�����ϴ�ͳ���û������ϴ�ͳ�Ʒ���������ͳ���û���������ͳ�Ʒ���;\n3.�û�����ĩβ���ܰ����ո񣬱��硰С����  ���͡�С���硱���ж�Ϊ��ͬ�û�\n4.��޶�400���û����ݣ������޷�ִ�С�\n\n******************Wanghz 2019-09-21******************\n\n��ʼ��������...\n");

    printf("�����ϴ�ͳ����������������������ȷ����������޷�ָ������");
    scanf("%d",&lastNum);
    printf("���뱾��ͳ����������������������ȷ����������޷�ָ������");
    scanf("%d",&thisNum);
    //���������������
    maxNum=lastNum>thisNum?lastNum:thisNum;

    printf("���ڶ�ȡundoSheet.csv�е����ݣ����Ժ�...\n");
    fp1=fopen("undoSheet.csv","r");     // fpָ��ָ���ļ�ͷ��
    for(i = 0 ;i < maxNum ; i++){
        fgets(line,99,fp1);
        if(i<lastNum){//���user1��ֵ
            ps=strtok(line,",\n");//��ȡuser1����
            strcpy(user1[i].name,ps); 
            ps=strtok(NULL,",\n");//��ȡuser1����
            user1[i].score=atoi(ps);
            if(i<thisNum){
                ps=strtok(NULL,",\n");//��ȡuser2����
                strcpy(user2[i].name,ps);
                ps=strtok(NULL,",\n");//��ȡuser2����
                user2[i].score=atoi(ps);
            }
        }else{
            if(i<thisNum){
                ps=strtok(line,",\n");//��ȡuser2����
                strcpy(user2[i].name,ps);
                ps=strtok(NULL,",\n");//��ȡuser2����
                user2[i].score=atoi(ps);
            }
        }
    }
    printf("undoSheet.csv���ݶ�ȡ��ϣ�׼���ȶ�����...\n");
    fclose(fp1); 

   

    /**
     * ����Ƚ���ͬһ�û��ķ����Ƿ���ͬ��
     */
    printf("�ȶ�������...\n");
    n=0;
    for(i=0;i<lastNum;i++){
        int flg=0;
        for(j=0;j<thisNum;j++){
            if(strcmp(user1[i].name,user2[j].name)==0){
                flg=1;
                if(user1[i].score!=user2[j].score){
                    strcpy(user3[n].name,user1[i].name);
                    user3[n].score=user1[i].score;
                    user3[n].score2=user2[j].score;
                    n++;
                    break;
                }
            }
            // if(j==thisNum-1&&flg==0){
            //     strcpy(user3[n].name,user1[i].name);
            //     user3[n].score=user1[i].score;
            //     n++;
            // }
        }
    }
    printf("�ȶ��������!\n");

    /**
     * ��doneData������д�뵽doneExcel.csv
     */
    printf("����д�����ݵ�doneExcel.csv��...\n");
	fp2 = fopen("doneExcel.txt","w") ;
    //fprintf(fp2,"�û�\t�ϴη���\t���η���\n",user3[i].name,user3[i].score,user3[i].score2 ) ;
	for (i=0 ; i<n ;i++){
	    fprintf(fp2,"%s\t%d\t%d\n",user3[i].name,user3[i].score,user3[i].score2 ) ;
    }
	fclose(fp2);
    printf("\n*****************************************************\n���ݴ���ɹ������ڳ��������ļ������ü��±��鿴doneExcel.txt�����зֱ����û����ϴη��������η�����\n���س�����������");

    system("pause");
}

