#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
 * 最长限定400个用户数据 
 * Excel必须按照格式填充ABCD四列分别填充上次统计用户名，上次统计分数，本次统计用户名，本次统计分数
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
    fseek(fp, 5L, SEEK_SET);   // 从文件第二行开始读取
    for(i = 0 ;i < 6 ; i++)
        for(j = 0 ;j < 5 ; j++)
		{
			fscanf(fp,"%f",&da[i][j]);
			fseek(fp, 1L, SEEK_CUR);   /*fp指针从当前位置向后移动*/
		}
           
	for(i = 0 ;i < 6 ; i++)
        printf("%f\t%f\t%f\t%f\t%f\t\n",da[i][0],
         da[i][1],da[i][2],da[i][3],da[i][4]);

	getchar() ;
}
int main(){
    /**
     * 读取undoExcel.xls，取出数据到undoDate中
     */	
    int maxNum=300;//当前数据最大行数
    int lastNum=0;//上次统计数数据行数
    int thisNum=0;//本次统计数据行数
	FILE *fp1,*fp2;//文件读写的指针
	int i,j,n;//计数
    char line[100];
    char *ps;
    
    printf("********CSV文本数据处理程序--比对数据前后一致********\n\n使用说明：\n1.执行程序前将undoSheet.csv放在程序的同一目录\n2.按照格式填充ABCD四列，分别填充上次统计用户名，上次统计分数，本次统计用户名，本次统计分数;\n3.用户名中末尾不能包含空格，比如“小军哥  ”和“小军哥”会判定为不同用户\n4.最长限定400个用户数据，超出无法执行。\n\n******************Wanghz 2019-09-21******************\n\n开始启动程序...\n");

    printf("输入上次统计数据行数（必须输入正确，否则程序无法指定）：");
    scanf("%d",&lastNum);
    printf("输入本次统计数据行数（必须输入正确，否则程序无法指定）：");
    scanf("%d",&thisNum);
    //设置数据最大行数
    maxNum=lastNum>thisNum?lastNum:thisNum;

    printf("正在读取undoSheet.csv中的数据，请稍后...\n");
    fp1=fopen("undoSheet.csv","r");     // fp指针指向文件头部
    for(i = 0 ;i < maxNum ; i++){
        fgets(line,99,fp1);
        if(i<lastNum){//如果user1有值
            ps=strtok(line,",\n");//提取user1姓名
            strcpy(user1[i].name,ps); 
            ps=strtok(NULL,",\n");//提取user1分数
            user1[i].score=atoi(ps);
            if(i<thisNum){
                ps=strtok(NULL,",\n");//提取user2姓名
                strcpy(user2[i].name,ps);
                ps=strtok(NULL,",\n");//提取user2分数
                user2[i].score=atoi(ps);
            }
        }else{
            if(i<thisNum){
                ps=strtok(line,",\n");//提取user2姓名
                strcpy(user2[i].name,ps);
                ps=strtok(NULL,",\n");//提取user2分数
                user2[i].score=atoi(ps);
            }
        }
    }
    printf("undoSheet.csv数据读取完毕，准备比对数据...\n");
    fclose(fp1); 

   

    /**
     * 逐个比较有同一用户的分数是否相同。
     */
    printf("比对数据中...\n");
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
    printf("比对数据完毕!\n");

    /**
     * 将doneData中数据写入到doneExcel.csv
     */
    printf("正在写入数据到doneExcel.csv中...\n");
	fp2 = fopen("doneExcel.txt","w") ;
    //fprintf(fp2,"用户\t上次分数\t本次分数\n",user3[i].name,user3[i].score,user3[i].score2 ) ;
	for (i=0 ; i<n ;i++){
	    fprintf(fp2,"%s\t%d\t%d\n",user3[i].name,user3[i].score,user3[i].score2 ) ;
    }
	fclose(fp2);
    printf("\n*****************************************************\n数据处理成功，请在程序所在文件夹下用记事本查看doneExcel.txt，三列分别是用户，上次分数，本次分数。\n按回车键结束程序！");

    system("pause");
}

