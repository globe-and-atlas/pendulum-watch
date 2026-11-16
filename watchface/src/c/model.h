#pragma once
#include <stdbool.h>
#include <stdint.h>
typedef struct {int16_t x,y;} TPoint;
typedef struct {TPoint center,pivot,hour,minute,bob;int radius,rod,bob_radius,angle,value;} TLayout;
int t_sin(int angle);TPoint t_point(TPoint p,int r,int a);bool t_24(int mode,bool system24);int t_hour(int hour,int mode,bool system24);void t_date(int y,int m,int d,int mode,char *out,int n);
void t_layout(int w,int h,int hour,int minute,int second,int phase,int mode,bool system24,TLayout *out);
bool t_bounds(int w,int h,const TLayout *l);
