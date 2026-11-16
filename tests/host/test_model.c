#include "model.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static void inside(int w,int h,int x,int y){assert(x>=0&&x<w&&y>=0&&y<h);if(w==260)assert(hypot(x-129.5,y-129.5)<129);}
static void circle(int w,int h,TPoint p,int r){for(int a=0;a<360;a+=10)inside(w,h,p.x+(int)lround(r*sin(a*acos(-1)/180)),p.y-(int)lround(r*cos(a*acos(-1)/180)));}
static void oracle(TPoint p,TPoint c,int r,double degrees){double a=degrees*acos(-1)/180;assert(abs(p.x-(int)lround(c.x+r*sin(a)))<=1);assert(abs(p.y-(int)lround(c.y-r*cos(a)))<=1);}
int main(void){
 for(int platform=0;platform<2;platform++){
  int w=platform?260:200,h=platform?260:228;
  for(int t=0;t<86400;t++){
   int hh=t/3600,mm=t/60%60,ss=t%60;TLayout l;t_layout(w,h,hh,mm,ss,ss%2*1000,2,false,&l);assert(t_bounds(w,h,&l));circle(w,h,l.center,l.radius+1);circle(w,h,l.bob,l.bob_radius+1);
   oracle(l.hour,l.center,platform?34:27,(hh%12)*30+mm*.5+(ss/12)*.1);oracle(l.minute,l.center,platform?47:38,mm*6+ss*.1);
   assert(l.value==hh);assert(l.bob.y+l.bob_radius<h-22);assert(l.bob.y-l.bob_radius>l.center.y+l.radius+2);
  }
  for(int phase=0;phase<2000;phase+=125){TLayout l;t_layout(w,h,13,30,20,phase,1,true,&l);assert(t_bounds(w,h,&l));circle(w,h,l.bob,l.bob_radius+1);oracle(l.bob,l.pivot,l.rod,180+18*cos(phase*2*acos(-1)/2000));assert(l.value==1);}
  TLayout left,right;t_layout(w,h,0,0,0,0,1,0,&left);t_layout(w,h,0,0,1,1000,1,0,&right);assert(left.bob.x<w/2 && right.bob.x>w/2);assert(abs(left.bob.y-right.bob.y)<=1);
  printf("PASS Pendulum %dx%d:86400seconds, smooth phases, bob/dial bounds, separation\n",w,h);
 }
 assert(t_hour(0,1,1)==12 && t_hour(0,2,0)==0 && t_hour(13,0,1)==13 && t_hour(13,0,0)==1);
 char d[20];t_date(2026,11,8,0,d,20);assert(!strcmp(d,""));t_date(2026,11,8,1,d,20);assert(!strcmp(d,"2026-11-08"));t_date(2026,11,8,2,d,20);assert(!strcmp(d,"11/08/2026"));t_date(2026,11,8,3,d,20);assert(!strcmp(d,"08/11/2026"));return 0;
}
