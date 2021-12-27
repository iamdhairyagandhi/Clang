#include <stdio.h>
#include <math.h>


static double cal_score(int ass_num[], int stu_score[], int weight[], int days_late[], int num_ass, int pen_day, int ass_drop);
static void drop_scores(int ass_num[], int stu_score[], int weight[], int ass_drop, int num_ass);
static void output(int ass_num[], int score[], int weight[], int days_late[],int num_ass,int ass_drop, int pen_day, int ig);
static double compute_mean(int ass_num[], int stu_score[], int weight[], int days_late[], int num_ass, int pen_day);
static double compute_sd(int ass_num[], int stu_score[], int weight[], int days_late[], int num_ass, int pen_day);

static double cal_score(int ass_num[], int stu_score[], int weight[], int days_late[], int num_ass, int pen_day, int ass_drop){
    int i, assign_late;
    double num_score = 0, weight_sum=0;

    if(ass_drop>0){
        drop_scores(ass_num, stu_score, weight, ass_drop,num_ass);
    }

    for ( i = 0; i < num_ass; i++) {
        weight_sum+= weight[i];
    }

    if(weight_sum>100.0){
        printf("ERROR: Invalid values provided\n");
        return -1;
    }
    else{
        for ( i = 0; i < num_ass; i++){
            assign_late = stu_score[i] - (days_late[i]*pen_day);
            if(assign_late>0){
                num_score += assign_late * (weight[i] / weight_sum);
            }
        }
    }
    return num_score;
}

void drop_scores(int ass_num[], int stu_score[], int weight[], int ass_drop, int num_ass){
    int i, min, value, count=0, drop_i=0;
    
    while(count++ < ass_drop){

        min = (stu_score[0] * weight[0]);
        for(i=0;i<num_ass;i++){
            value = (stu_score[i] * weight[i]);

            if(value!=0){
                if(value<min || (value == min && i < drop_i)){
                    min = value;
                    drop_i=i;
                }
            }
        }

        weight[drop_i]=0;

    }
}

static double compute_mean(int ass_num[], int stu_score[], int weight[], int days_late[], int num_ass, int pen_day){
    int i;
    double mean;
    int sum_scores = 0;


    for (i = 0; i < num_ass; i ++) {
        sum_scores += (stu_score[i] - (days_late[i]*pen_day));
    }
    mean = (sum_scores / (double) num_ass);
    return mean;
}
static double compute_sd(int ass_num[], int stu_score[], int weight[], int days_late[], int num_ass, int pen_day){
    int i, score;
    double mean, sum = 0, variance, std;
    mean = compute_mean(ass_num, stu_score, weight, days_late, num_ass, pen_day);


    for (i = 0; i < num_ass; i ++) {
        score = stu_score[i] - (days_late[i]* pen_day);
        sum += pow((score - mean), 2);
    }
    variance = sum / (float) num_ass;
    std = sqrt(variance);

    return std;
}


int main() {
    int num_ass, pen_day, ass_drop, i;
    int ass_num[50]={0}, score[50]={0}, weight[50]={0}, days_late[50]={0};
    char info_gen;

    scanf(" %d %d %c", &pen_day, &ass_drop, &info_gen );
    scanf(" %d", &num_ass);


    for ( i = 0; i < num_ass; i++) {
        scanf(" %d, %d, %d, %d", &ass_num[i], &score[i], &weight[i], &days_late[i]);
    }

    /* printf("raw data:\n");
    for (i = 0; i < num_ass; i++) {
            printf(" %d, %d, %d, %d\n", ass_num[i], score[i], weight[i], days_late[i]);
    } */


    if(num_ass>=0 && pen_day >=0 && ass_drop >= 0){
        output(ass_num, score, weight, days_late, num_ass, ass_drop, pen_day, info_gen);
    }


    return 0;

}

void output(int ass_num[], int score[], int weight[], int days_late[],int num_ass,int ass_drop, int pen_day, int ig) {
    int i, flag = 1;
    double scorel, meanl, sdl;

    int fl_score[50] = {0};

    int w_nup[50];
    for(i=0; i<num_ass; i++) {
	w_nup[i]=weight[i];	
    }
    for (i = 0; i < num_ass; i++) {
        fl_score[i] = score[i];
    }
    if (ass_drop >= 0 && ass_drop < num_ass) {
        scorel = cal_score(ass_num, score, weight, days_late, num_ass, pen_day, ass_drop);
    } else {
        score = 0;
    }

    printf("Numeric Score: %5.4f\n", scorel);
    printf("Points Penalty Per Day Late: %d\n", pen_day);
    printf("Number of Assignments Dropped: %d\n", ass_drop);

    printf("Values Provided:\nAssignment, Score, Weight, Days Late\n");

    while (flag<=num_ass) {
        for (i = 0; i < num_ass; i++) {
            if (ass_num[i]==flag) {
                printf("%d, %d, %d, %d\n", ass_num[i], score[i], w_nup[i], days_late[i]);
            }
        }
        flag += 1;
    }
    if (ig == 'Y' || ig == 'y') {
        meanl = compute_mean(ass_num, score, weight, days_late, num_ass, pen_day);
        sdl = compute_sd(ass_num, score, weight, days_late, num_ass, pen_day);
        printf("Mean: %5.4f, Standard Deviation: %5.4f\n", meanl, sdl);
    }


}
