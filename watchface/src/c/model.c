#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
static const int16_t SINE[91]={0,286,572,857,1143,1428,1713,1997,2280,2563,2845,3126,3406,3686,3964,4240,4516,4790,5063,5334,5604,5872,6138,6402,6664,6924,7182,7438,7692,7943,8192,8438,8682,8923,9162,9397,9630,9860,10087,10311,10531,10749,10963,11174,11381,11585,11786,11982,12176,12365,12551,12733,12911,13085,13255,13421,13583,13741,13894,14044,14189,14330,14466,14598,14726,14849,14968,15082,15191,15296,15396,15491,15582,15668,15749,15826,15897,15964,16026,16083,16135,16182,16225,16262,16294,16322,16344,16362,16374,16382,16384};
int t_sin(int angle){
 angle%=3600;if(angle<0)angle+=3600;
 int sign=1;if(angle>=1800){sign=-1;angle-=1800;}if(angle>900)angle=1800-angle;
 int degree=angle/10,part=angle%10;
 return sign*(SINE[degree]+(degree<90?(SINE[degree+1]-SINE[degree])*part/10:0));
}
static int rounded(int value){return value>=0?(value+8192)/16384:-((-value+8192)/16384);}
TPoint t_point(TPoint p,int radius,int angle){TPoint q={p.x+rounded(radius*t_sin(angle)),p.y-rounded(radius*t_sin(angle+900))};return q;}
bool t_24(int mode,bool system24){return mode==2 || (mode==0 && system24);}
int t_hour(int hour,int mode,bool system24){return t_24(mode,system24)?hour:(hour%12?hour%12:12);}
void t_date(int year,int month,int day,int mode,char *out,int n){
 if(mode==1)snprintf(out,n,"%04d-%02d-%02d",year,month,day);
 else if(mode==2)snprintf(out,n,"%02d/%02d/%04d",month,day,year);
 else if(mode==3)snprintf(out,n,"%02d/%02d/%04d",day,month,year);
 else if(n>0)out[0]=0;
}
void t_layout(int w,int h,int hour,int minute,int second,int phase,int mode,bool system24,TLayout *l){
 (void)h;memset(l,0,sizeof(*l));bool r=w==260;l->center=(TPoint){w/2,r?86:78};l->radius=r?59:48;l->pivot=(TPoint){w/2,r?151:134};l->rod=r?66:58;l->bob_radius=r?12:10;
 l->hour=t_point(l->center,r?34:27,(hour%12)*300+minute*5+second/12);l->minute=t_point(l->center,r?47:38,minute*60+second);
 l->angle=1800+t_sin((phase%2000)*3600/2000+900)*180/16384;l->bob=t_point(l->pivot,l->rod,l->angle);l->value=t_hour(hour,mode,system24);
}
bool t_bounds(int w,int h,const TLayout *l){
 for(int a=0;a<3600;a+=100){TPoint p=t_point(l->bob,l->bob_radius+1,a);if(p.x<0||p.x>=w||p.y<0||p.y>=h)return false;if(w==260){int dx=2*p.x-259,dy=2*p.y-259;if(dx*dx+dy*dy>258*258)return false;}}
 return l->bob.y+l->bob_radius<h-22 && l->center.y-l->radius>18;
}
