#include <stdio.h>
#include <string.h>

// 函数声明
void convertTime(int hour, int minute);

int main() {
    int hour, minute;
    
    // 提示用户输入24小时制的时间
    printf("请输入24小时制的时间（格式：小时:分钟）：");
    scanf("%d:%d", &hour, &minute);
    
    // 检查输入时间是否有效
    if (hour >= 0 && hour < 24 && minute >= 0 && minute < 60) {
        convertTime(hour, minute);
    } else {
        printf("输入的时间无效，请重新输入。\n");
    }
    
    return 0;
}

// 将24小时制时间转换为12小时制时间的函数
void convertTime(int hour, int minute) {
    int convertedHour = hour;
    char period[3] = "AM";
    
    switch (hour) {
        case 0:
            convertedHour = 12;
            break;
        case 12:
            strcpy(period, "PM");
            break;
        default:
            if (hour > 12) {
                convertedHour = hour - 12;
                strcpy(period, "PM");
            } else {
                strcpy(period, "AM");
            }
            break;
    }
    
    // 输出转换后的时间
    printf("转换后的12小时制时间是：%02d:%02d %s\n", convertedHour, minute, period);
}
