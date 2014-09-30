#include <stdlib.h>
#include <stdio.h>
//#include <conio.h>
//#include <dos.h>
//#include <time.h>
//#include <process.h>
#include <string.h>
//#include <io.h>
#include "Chaos2014.h"
#include "SDL_keycode.h"

//extern "C"{
//#include "chaosnd.c"
//}

void youmove(void);
void initscreen(void);
void bullet(void);
void random_happenings(void);
void countthings(void);
void keepscore(void);
void monsters(void);
void you_die(int);
void crazystuff(void);
void drawlives(void);
void drawwep(void);
void paws(void);
void stats(void);
void destbul(void);
void gotawep(int);
void initbullet(int);
void bulletkill(void);
void text(int,int,int,int,int);
void string(int,int,int,int,const char*);
void die(int,int);
void message(char[30],int);
void zapper(int,int);
void amoeba(int,int);
void putwall(int,int);
void resetsys(void);
int rnd(int,int);
int push(int,int,int);
int inside(int,int);
int bullethrough(int);
void initvars(void);
void records(int,int,int);

int x,y,x1,y1,bulx,buly,p,o;
int cashola,alivetime,amoebafry;
int key,buld,wallcount,destcount;
int howdied,level,face,maxx,maxy,bvar;
int weirdshot,weirdshotdir,dead,initmode;
char size=0,tuffness=1/*,hear*/;
char lives,invuln,messagetime,trail,trailtype,drunk,lethargy;
char fireball,weaponon,snakeshot,shield,weapon,sykodump,frog;

char name[13]="Squiddy";
char map[81][50];
char mon[81][50];
char dx[]={0,0,1,0,-1};
char dy[]={0,-1,0,1,0};
char wepname[][20]={"","Zap Gun","Mega Maimer","Guided Death Rocket",
	"Shuriken","Extermination Beam","Annihilation Bomb","Wall"};
char wepcolor[]={0,5,7,9,15,12,14,6};
int  ammo[10];
char line[50][40];

int  difflev[2][3]={1000,750,500,  750,500,250};

struct{
	int  score[6], kills[6], mpm[6];
	char scorer[6][13], killer[6][13], maniac[6][13];
} his;

#define mt 30
unsigned char killed[mt];
char tufscale[mt]={0,1,4,2,5,13,12,7,10,16,14,11,18,8,25,
				  19,17,3,9,6,22,24,21,20,15,23,0,0,0,0};

#define mm 32
int mx[mm],my[mm],md[mm],mtype[mm],mdead[mm],init[mm];
int bx[mm],by[mm],bd[mm],var[mm][12];

char spc[][80]={"                                      ",
"                                                                              "};

char exist[][50]={
//basic
//"BDDDEE GLM KJRPNHHX CCFIQQSSSUV OW",
"AAABBDDE",
//extended
"AAAABBBDDDEEE GLMM",
//regular
"AABBBDDDEEE GLLMMM KJPN",
"AABBDDDEEE GLLMMM KJJRPNHY",
//tough
"ABBBDDDEEE GLLMMM KJJRRPPNHY CFIQSX",
"BBDDDDEEE GLLMM KJJRRPPNHHY CCFIQQSSUVX",
//dalek
"BBDDDDEEE GLLMM KJJRRPPNHHHXYY CCFIQQSSUVX OW",
"BDDDEE GLM KJRPNHHY CCFIQQSSSUVX OW",
//death
"DCCFHHIOQQSSSUWX",
//title
"AAAABBCCDDDDGGLLLLMMH"
};

int target[]={0,20,70,120,240,415,640,850,1300};

#include "monsters.cpp"
#include "title.cpp"

void (*domonster[mm]) (int);

void chaos_main(){ //*****MAIN*****
	domonster[0]=grunt;
	domonster[1]=zoom;
	domonster[2]=tank;
	domonster[3]=dumptruck;
	domonster[4]=aluminum_rod;
	domonster[5]=gargoyle;
	domonster[6]=bomb;
	domonster[7]=rhino;
	domonster[8]=snake;
	domonster[9]=ostrich;
	domonster[10]=bastardcoward;
	domonster[11]=mendicant;
	domonster[12]=militant_grunt;
	domonster[13]=aluminum_man;
	domonster[14]=dalek;
	domonster[15]=turret;
	domonster[16]=super_zoom;
	domonster[17]=syko_fish;
	domonster[18]=ninja;
	domonster[19]=super_rod;
	domonster[20]=F16;
	domonster[21]=zombie;
	domonster[22]=zookeeper;
	domonster[23]=wurm;
	domonster[24]=doppleganger;

	atexit(resetsys);
	//randomize();
	struct text_info ti;
	gettextinfo(&ti);
	initmode=ti.currmode;

//	initSound();

	FILE *scr;
	if ((scr=fopen("scores.hi","r"))==NULL){
		for (int a=1;a<=5;a++){
			strcpy(his.scorer[a],"            ");
			strcpy(his.killer[a],"            ");
			strcpy(his.maniac[a],"            ");
			his.score[a]=0; his.kills[a]=0; his.mpm[a]=0;
		}
	}else{
		fread(&his,sizeof(his),1,scr);
		fclose(scr);
	}

do{
	title();

	initscreen();

	x=20; y=12;
	text(x,y,14,2,'');

	biostime(1,0);
	int lp,wat=2;
	if (lethargy) wat=1;

	do{
		//lp=biostime(0,0)+wat;
		youmove();
		if (buld) bullet();
		random_happenings();
		countthings();
		monsters();
		//while (biostime(0,0)<lp);
        if(!dead) snooze(wat);
	} while (!dead);
} while(1);
}


void initscreen(void){ //*****INITSCREEN*****
	if (size){
		textmode(3); textmode(64);
	}

	//_setcursortype(_NOCURSOR);
	struct text_info ti;
	gettextinfo(&ti);
	maxx=ti.screenwidth;
	maxy=ti.screenheight-1;

	initvars();

	textcolor(4);  textbackground(6);
	for (x=1;x<=maxx;x++) {gotoxy(x,2);    map[x][2]=100;    putch(254);
						   gotoxy(x,maxy); map[x][maxy]=100; putch(254);}
	for (y=3;y<=maxy;y++) {gotoxy(1,y);    map[1][y]=100;    putch(254);
						   gotoxy(maxx,y); map[maxx][y]=100; putch(254);}

	textbackground(2);
	for (y=3;y<=maxy-1;y++) {gotoxy(2,y); cputs(spc[size]);}

	keepscore();
	drawlives();
	drawwep();
	message("",0);
	ammo[1]=1;
}


void youmove(void){ //*****YOU MOVE*****
	key=0;
	while (kbhit()) key=getch();

	if (!inside(x,y)) {x=rnd(2,maxx-1); y=rnd(3,maxy-1);}
	x1=x; y1=y;

	o=mon[x][y];
	if (o>0 && mtype[o]!=7 && mtype[o]!=10) {
		you_die(mtype[o]+100);
		mdead[o]=3;
		if (fireball) mdead[o]=2;
	}

	if (buld==0 && inside(bulx,buly) && map[bulx][buly]==50)
		{map[bulx][buly]=0; text(bulx,buly,0,2,' ');}

	if (weirdshot==1) {zapper(0,weirdshotdir); weirdshot=0;}
	if (weirdshot==2) {
		for (int x2=bulx-1;x2<=bulx+1;x2++)
		for (int y2=buly-1;y2<=buly+1;y2++){
			if (inside(x2,y2)) text(x2,y2,14,2,' ');}
		weirdshot=0;
	}

	int d=0;
    int shoot=shootkey();
	switch (key){
        case SDLK_UP: case SDLK_w:
            if(shoot) initbullet(1);
            else d=1;
            break;
        case SDLK_DOWN: case SDLK_s:
            if(shoot) initbullet(3);
            else d=3;
            break;
        case SDLK_LEFT: case SDLK_a:
            if(shoot) initbullet(4);
            else d=4;
            break;
        case SDLK_RIGHT: case SDLK_d:
            if(shoot) initbullet(2);
            else d=2;
            break;
		case SDLK_SPACE:  initbullet(face);  break;
		case SDLK_ESCAPE:  dead=1;  break;
		case SDLK_p: paws();  break;
		//case 0:  break;
		//case 82:
        case SDLK_n:
		case SDLK_x: do{
					weaponon++;
					if (weaponon>=10) weaponon=1;
				 } while(ammo[weaponon]==0);
				 drawwep();
				 break;
		case SDLK_1:
        case SDLK_m:
		case SDLK_c: weaponon=1; drawwep();  break;
		case SDLK_2:  if (ammo[2]) weaponon=2;
		case SDLK_3:  if (ammo[4]) weaponon=4;
		case SDLK_4:  if (ammo[3]) weaponon=3;
		case SDLK_5:  if (ammo[7]) weaponon=7;
		case SDLK_6:  if (ammo[6]) weaponon=6;
		case SDLK_7:  if (ammo[5]) weaponon=5;
		//case 68: exit(0);
		//default: gotoxy(1,1); printf ("%i  ",key);
	}

	if (fireball && d==0) d=face;

	x1+=dx[d];
	y1+=dy[d];

	if (drunk && d>0){
		drunk--;
		d+=2; if (d>4) d-=4;
		x1=x+dx[d];
		y1=y+dy[d];
	}

	if (lethargy){
		lethargy--;
		if (lethargy%2) {x1=x; y1=y; d=0;}
	}

	if (frog){
		x1+=dx[d]*random(4);
		y1+=dy[d]*random(4);
		if (x1<2) x1=2;
		if (x1>maxx-1) x1=maxx-1;
		if (y1<3) y1=3;
		if (y1>maxy-1) y1=maxy-1;
	}

	if (d) face=d;

	mon[x][y]=0;

	if (shield){
		shield--;
		for (int x2=x-1;x2<=x+1;x2++) for (int y2=y-1;y2<=y+1;y2++){
			if ((x2!=x || y2!=y) && inside(x2,y2)){
				text(x2,y2,0,2,' ');
			}
		}
	}

	int moveon=1;
	switch (map[x1][y1]){
		case 0: break;
		case 4: cashola+=5;
		case 3: cashola++;  keepscore();/*noise(7,0);*/ break;
		case 5: wallcount+=3+random(8)*(size+1);  break;
		case 6: destcount+=5+random(16)*(size+1); break;
		case 7: /*noise(17,1);*/ crazystuff(); break;
		case 8:	gotawep(0); break;
		case 9: gotawep(2); break;
		case 10: gotawep(4); break;
		case 11: gotawep(5); break;
		case 51: you_die(13);  break;
		case 101: you_die(14); break;
		case 100: moveon=0; break;
		case 102: moveon=push(x1,y1,d); break;
		case 103: you_die(15); break;
		case 104: you_die(16); amoebafry++; break;
		case 105: cashola+=10; keepscore(); break;
	}

	o=mon[x1][y1];
	if (o>0 && mtype[o]!=7 && mtype[o]!=10) {
		you_die(mtype[o]+100);
		mdead[o]=3;
		if (fireball) mdead[o]=2;
	}
	if (mtype[o]==7) {md[o]=d; var[o][2]=1; moveon=0;}

	if (moveon) {
		switch (trailtype){
			case 0: text(x,y,0,2,' '); break;
			case 1: text(x,y,4,2,'*'); map[x][y]=103; break;
			case 2: text(x,y,1,5,'ð'); map[x][y]=102; break;
			case 3: text(x,y,1,6,'þ'); map[x][y]=100; break;
			case 4: text(x,y,14,2,'›');map[x][y]=3;   break;
			default:text(x,y,15,2,'¥');break;
		}
		x=x1; y=y1;
		map[x][y]=0;
		mon[x][y]=-1;
	}

	text(x,y,14,2,'');

	if (invuln) if (invuln%2) text(x,y,9,2,'');

	if (fireball) if (fireball%2) text(x,y,12,2,''); else
								  text(x,y,4,2,'');

	if (shield){
		for (int x2=x-1;x2<=x+1;x2++) for (int y2=y-1;y2<=y+1;y2++){
			if ((x2!=x || y2!=y) && inside(x2,y2)){
				map[x2][y2]=0;
				o=mon[x2][y2];
				if (o>0) {mdead[o]=3; var[o][1]-=3;}
				int co=14; if (shield%2) co=12;
				if (shield<=12) {co=12; if (shield%2) co=4;}
				if (shield<=5) {co=4;  if (shield%2) co=2;}
				text(x2,y2,co,2,'Û');
			}
		}
	}

	if (level<8) if (cashola>=target[level+1]*2) level++;
}


void initbullet(int dir){//INITBULLET
	if (drunk) {dir+=2; if (dir>4) dir-=4;}
	int tru=0;
	if (buld==0) weapon=weaponon;

	switch (weapon){
	case 1:
//		noise(0,0);
		if (buld){
			text(bulx,buly,15,2,'+');
			map[bulx][buly]=101;
			if (snakeshot){
				snakeshot--;
				o=0; for (int a=1;a<mm;a++){
					if (mtype[a]==0) {o=a; break;}}
				if (o){
					mx[o]=bulx; my[o]=buly;
					mtype[o]=9; mdead[o]=0;
					map[bulx][buly]=0;
				}
			}
		}
		tru=1;
		break;
	case 2:
		if (!buld) tru=1;
		break;
	case 3:
		if (!buld) {bulx=x; buly=y;}
		if (!buld && drunk) {buld=dir+2; if (buld>4) buld-=4;}
		else buld=dir;
		break;
	case 4:
		if (buld){
			text(bulx,buly,0,2,' ');
			map[bulx][buly]=0;
		}
		tru=1;
		bvar=10;
		break;
	case 5:
		tru=1;
		break;
	case 6:
	case 7:
		if (!buld) {
			tru=1;
			p=map[x+dx[dir]][y+dy[dir]];
			if (p==100 || p==102 || p==104) tru=0;
        }
		if (!tru) destbul();
		break;
	}

	if (tru){
		bulx=x; buly=y;	buld=dir; weirdshot=0;
		if (weapon==5 && weaponon==5){
			zapper(1,dir);
			weirdshot=1; weirdshotdir=dir;
		}
	}

	if (x==bulx && y==buly){
		weapon=weaponon;
		if (weapon>1) ammo[weapon]--;
		if (ammo[weapon]<1) weaponon=1;
	}
	drawwep();
}


void bullet(void){ //*****BULLET*****
	int speed=1; if (weapon==2) speed=2;
	for (int a=1;a<=speed;a++){
		bulletkill();
		if ((bulx!=x || buly!=y) && map[bulx][buly]>=50)
			text(bulx,buly,15,2,' ');
		map[bulx][buly]=0;
		x1=bulx+dx[buld];
		y1=buly+dy[buld];
		p=map[x1][y1];
		if (p==104) amoebafry++;
		if (weapon==7 && (mon[x1][y1] || p==104)) p=100;
		if (bullethrough(p)){
			bulx=x1; buly=y1;
            int ch;
			switch (weapon){
			case 1: text(bulx,buly,15,2,'ù');  break;
			case 2: text(bulx,buly,8,2,'ù');   break;
			case 3:
				ch=24;
				if (buld==2) ch=26;
				if (buld==3) ch=25;
				if (buld==4) ch=27;
				text(bulx,buly,9,2,ch);        break;
			case 4: text(bulx,buly,7,2,'*');   break;
			case 6:
				if (bvar%2) text(bulx,buly,4,2,'ì');
				else        text(bulx,buly,4,2,'é');
				break;
			case 7: text(bulx,buly,4,1,'þ');   break;
			}
			if (mon[bulx][buly]==-1) {you_die(12); destbul();}
			map[bulx][buly]=50;
			if (weapon==7) map[bulx][buly]=100;
		}
		else {
			if (weapon==6) {bulx=x1; buly=y1; destbul();}
			buld=0; map[bulx][buly]=0; a=2;
			if (weapon==7) destbul();
		}
		bulletkill();
		if (weapon==4) {bvar--; if (bvar<=0) buld=0;}
		if (weapon==6) bvar++;
	}
}


void bulletkill(void){//BULLETKILL
	o=mon[bulx][buly];
	if (o>0) if (mtype[o]==14 || mtype[o]==25 && var[o][0]==14)
		buld=deflect(buld);
	else{
		mdead[o]=2;
		map[bulx][buly]=0;
		destbul();
		return;
	}
}


void destbul(void){//DESTROY BULLET
	if (weapon!=4) buld=0;
	if (weapon==6){
			int x2,y2;
			for (x2=bulx-1;x2<=bulx+1;x2++)
			for (y2=buly-1;y2<=buly+1;y2++){
				if (inside(x2,y2)){
					text(x2,y2,14,2,'');
					p=map[x2][y2];
					if (p==104) amoebafry++;
					if (p==51){
						for (int t=1;t<=mm-1;t++){
							if (bx[t]==x2 && by[t]==y2) bd[t]=0;}}
					map[x2][y2]=0;
					o=mon[x2][y2];
					if (o==-1) you_die(17);
					if (o>0) mdead[o]=2;
			}	}
			weirdshot=2;
	}
	if (weapon==7){
		if (mon[bulx][buly]==0)	map[bulx][buly]=100;
		text(bulx,buly,4,1,'þ');
	}
}


void zapper(int z,int dir){//ZAPPER
		bvar++;
		int col=4;
		if (bvar%3==1) col=12;
		if (bvar%3==2) col=14;
		for(int a=1;a<=6;a++){
			int x2=x+a*dx[dir];
			int y2=y+a*dy[dir];
			if (inside(x2,y2)){
				p=map[x2][y2];
				o=mon[x2][y2];
				if (o>0) {mdead[o]=2; var[o][1]-=3;}
				map[x2][y2]=0;
				if (p==104) amoebafry++;
				if (p==51){
					for (int t=1;t<=mm-1;t++){
						if (bx[t]==x2 && by[t]==y2) bd[t]=0;}}
				if (!z) text(x2,y2,0,2,' ');
				else text(x2,y2,col,2,'Û');
			}
		}
}


void random_happenings(void){ //*RANDOM HAPPENINGS*****
	int r=random(1000)+1;
	do{ x1=rnd(2,maxx-1);
		y1=rnd(3,maxy-1);
	} while(abs(x1-x)<5 && abs(y1-y)<5);
	if (r>0 && r<=9)      {text(x1,y1,14,2,'›'); map[x1][y1]=3;}
	if (r>100 && r<=106)  {text(x1,y1,14,2,'$'); map[x1][y1]=4;}
	if (r>200 && r<=206+level/3)  {if (random(2)) text(x1,y1,1,2,'');
						   else text(x1,y1,1,2,'');
						   map[x1][y1]=5;}
	if (r>300 && r<=302)  {text(x1,y1,8,2,'÷');  map[x1][y1]=6;}
	if (r>400 && r<=400+level/3)  {text(x1,y1,14,2,'?'); map[x1][y1]=7;}
	if (r>500 && r<=503)  {for(int a=0;a<=random(8);a++){
						   int x2=x1+random(3)-1;
						   int y2=y1+random(3)-1;
						   if (inside(x2,y2)){
								text(x2,y2,1,5,'ð');
								map[x2][y2]=102;
						  }}}
	if (r>=600 && r<=600 && level>2)  {amoeba(x1,y1);}
	if (r>700 && r<703+level/2) {int co=10,ch='';
						   if (random(2)) co=6;
						   if (random(2)) ch='';
						   text(x1,y1,co,2,ch); map[x1][y1]=8;}
}


void countthings(void){ //*****COUNT THINGS*****
	if (wallcount && !random(5)){
		wallcount--;
		x1=rnd(-2,maxx-1);
		y1=rnd(-1,maxy-1);
		int f=8,b=4;
		switch (random(8)){
		case 0: f=0;  b=1; break;
		case 1: f=3;  b=4; break;
		case 2: f=9;  b=6; break;
		case 3: f=5;  b=4; break;
		case 4: f=14; b=1; break;
		case 5: f=4;  b=0; break;
		}
		textcolor(f);  textbackground(b);
		putwall(x1,y1);
		switch (random(3)){
			case 0: {putwall(x1+1,y1); putwall(x1,y1+1); putwall(x1+1,y1+1);
					 break;}
			case 1: {putwall(x1,y1+1); putwall(x1,y1+2); putwall(x1,y1+3);
					 break;}
			case 2: {putwall(x1+1,y1); putwall(x1+2,y1); putwall(x1+3,y1);
					 break;}
		}
	}

	if (destcount){
		destcount--;
		x1=rnd(2,maxx-2);
		y1=rnd(3,maxy-2);
		text(x1,y1,0,2,'É');   text(x1+1,y1,0,2,'»');
		text(x1,y1+1,0,2,'È'); text(x1+1,y1+1,0,2,'¼');
		text(x1,y1,0,2,' ');   text(x1+1,y1,0,2,' ');
		text(x1,y1+1,0,2,' '); text(x1+1,y1+1,0,2,' ');
		map[x1][y1]=0;   map[x1+1][y1]=0;
		map[x1][y1+1]=0; map[x1+1][y1+1]=0;
	}

	if (invuln) invuln--;
	if (messagetime) {messagetime--; if (messagetime==0) message("",0);}
	if (trail) {trail--; if (trail==0) trailtype=0;}
	if (fireball) fireball--;
	if (sykodump) sykodump--;
	if (frog) frog--;

	for (int a=1;a<=6;a++){
		do{
			x1=rnd(2,maxx-1);
			y1=rnd(3,maxy-1);
		}while (abs(x1-x)<5 && abs(y1-y<5));
		if (map[x1][y1]==104) amoeba(x1,y1);
	}   

	for (int a=1;a<=25;a++){
		x1=rnd(2,maxx-1);
		y1=rnd(3,maxy-1);
		if (map[x1][y1]==104){
			int ch='ï'; if (random(2)) ch='U';
			text(x1,y1,9+random(7),5,ch);
	}   }
}


void monsters(void){ //!!!!!!!! MoNsTeRs !!!!!!!!
	int snakemake=0,snakex=0,snakey=0,a;
//	int dis=70;

/*	for (a=1;a<mm;a++){
		if (mtype[a]){
			int x2=abs(x-mx[a]), y2=abs(y-my[a]);
			if (x2<dis && y2<dis){
				dis=x2; if (y2>x2) dis=y2;
				hear=a;
	}	}	}
*/
	for (a=1;a<mm;a++){
		if (mtype[a]){
			(*domonster[mtype[a]-1]) (a);
			if (mtype[a]==25) (*domonster[var[a][0]-1]) (a);
			if (!inside(mx[a],my[a])) {
				mdead[a]=1;
			}
		}
		else{
			if (!random(difflev[size][tuffness]-level*10) || snakemake){
				do{
					int lev=level;
					if (!random(20) && level<9) lev++;
					int r=random(strlen(exist[lev]));
					mtype[a]=exist[level][r]-64;
					if (mtype[a]==11 && random(3)) mtype[a]=0;
					if ((mtype[a]==8 || mtype[a]==14 || mtype[a]==22
						|| mtype[a]==23 || mtype[a]==25) && random(2))
						mtype[a]=0;
				} while(mtype[a]<=0);
				if (snakemake>0) {snakemake--; if (snakemake>0) mtype[a]=9;}
				int tru;
				mdead[a]=0;  init[a]=1;
				for (o=0;o<11;o++) var[a][o]=0;
				bx[a]=0;  by[a]=0;  bd[a]=0;  md[a]=random(4)+1;
				do{
					tru=1;
					mx[a]=rnd(2,maxx-1);  my[a]=rnd(3,maxy-1);
					if (mtype[a]==9 && snakex){
						mx[a]=snakex+random(7)-3;
						my[a]=snakey+random(7)-3;
						if (!inside(mx[a],my[a])) tru=0;
					}
					if (map[mx[a]][my[a]]>0) tru=0;
					if (abs(x-mx[a])<10 && abs(y-my[a])<9) tru=0;
				} while(!tru);
				if (mtype[a]==9 && snakemake==0)
					{snakex=mx[a]; snakey=my[a]; snakemake=rnd(2,7);}
				(*domonster[mtype[a]-1]) (a);
			}
		}
	}
}


void you_die(int h){//***YOU DIE***
	if (invuln) return;
	if ((shield || fireball) && h!=7) return;
	invuln=20;
	lives--;
	drawlives();

	if (lives==0){
		alivetime=biostime(0,0);
		howdied=h;
		text(x,y,8,2,'x');
		x1=maxx/2-4; y1=maxy/2;
		gotoxy(x1,y1); textcolor(14);
		cprintf("GAME OVER");
		for (int a=0;a<=3;a++){
			map[x1+a][y1]=100; map[x1+a+5][y1]=100;}
        int lp;
		do{
			//lp=biostime(0,0);
			x=rnd(2,maxx-1);
			y=rnd(3,maxy-1);
			monsters();
			countthings();
			p=0;
			if (kbhit()) p=getch();
			//while (biostime(0,0)<lp+2);
            snooze(2);
		} while (p!=32);
		stats();
		dead=1;
	}
}


void crazystuff(void){// CRAZY STUFF 
	int r=random(17)+1;
    int ra,r2,rmax;
	if (r==16 && random(2)) r=2;
	switch (r){
	case  1: rmax=10+random(11);
			 for (int a=0;a<rmax;a++){
				int x2=rnd(2,maxx-1);
				int y2=rnd(3,maxy-1);
				text(x2,y2,14,2,'$');
				map[x2][y2]=4;
			 }
			 break;

	case  2: lives++;
			 message("Bonus Life!",15);
			 drawlives();
			 break;

	case  3:
			 for (int x2=x1-1;x2<=x1+1;x2++) for (int y2=y1-1;y2<=y1+1;y2++){
				if ((x2!=x1 || y2!=y1) && inside(x2,y2)){
					map[x2][y2]=102;
					text(x2,y2,1,5,'ð');
				}
			 }
			 break;

	case  4: r2=rnd(5,50);
			 cashola+=r2*2;
			 char m[16];
			 sprintf(m,"Wow, a $%i bill!",r);
			 message(m,14);
			 keepscore();
			 break;

	case  5: shield=rnd(30,180);
			 break;

	case  6: trail=rnd(20,100);
			 trailtype=random(4)+1; break;

	case  7: drunk=rnd(10,70);
			 message("Doi!",13);
			 break;

	case  8: lethargy=rnd(50,250);
			 message("Everything seems to be moving so fast!",9);
			 break;

	case  9: message("Where am I?",1);
			 map[x1][y1]=0;
			 text(x1,y1,0,2,' ');
			 do{
				 x1=rnd(2,maxx-1); y1=rnd(3,maxy-1);
			 } while(map[x1][y1]);
			 break;

	case 10: ra=exist[level][random(strlen(exist[level]))]-64;
			 for (int l=1;l<mm;l++){
				int t=mtype[l];
				if (t && t!=3 && t!=8 && t!=10 && t!=13 && t!=15 && t!=16
					&& t!=19 && t!=21 && t!=23)  mtype[l]=ra;
			 }
			 break;

	case 11: message("Fireball!",4);
			 ra=rnd(40,100);
			 fireball=ra;  trail=ra-8;  trailtype=1;
			 break;

	case 12: message("Dumptruck frenzy!!",6);
			 sykodump=rnd(30,75);
			 break;

	case 13: message("Jeepers creepers, Quantum leapers",10);
			 frog=rnd(30,90);
			 break;

	case 14: message("My gun seems to be alive?!",7);
			 snakeshot=rnd(3,6);
			 break;

	case 15: ra=rnd(5,11);
			 for (int a=1;a<mm;a++){
				if (mtype[a]==0){
					mdead[a]=0;
					mtype[a]=21; init[a]=1;
					md[a]=random(4)+1;
					ra--;  if (ra<=0) break;
			 }	}
			 break;

	case 16: for (int x2=2;x2<=maxx-1;x2++)
			 for (int y2=3;y2<=maxy-1;y2++){
				if (map[x2][y2]==100){
					map[x2][y2]=103;
					text(x2,y2,4,2,'*');}
				else{
				if (map[x2][y2]==103){
					map[x2][y2]=100;
					text(x2,y2,6,4,'þ');}}
			 }
			 break;

	case 17: gotawep(5); break;

	}
}


int push(int px,int py,int pd){//PUSH
	if (pd==0) return 0;
	int x2=px+dx[pd];
	int y2=py+dy[pd];
	p=map[x2][y2];
	o=mon[x2][y2];
	int tru=0;
	if (p==0 && o==0 && mon[px][py]==0) tru=1;
	if (p==102) tru=push(x2,y2,pd);
	if (tru){
		int t; gettext(px,py,px,py,&t);
		map[px][py]=0;
		map[x2][y2]=102;
		puttext(x2,y2,x2,y2,&t);
	}
	return(tru);
}


void amoeba(int x1,int y1){//AMOEBA
	for(int a=0;a<=4;a++){
		int x2=x1+dx[a];
		int y2=y1+dy[a];
		if (inside(x2,y2)) if (map[x2][y2]==0){
			o=mon[x2][y2];
			if (o==-1) you_die(16);
			if (o>0) {mdead[o]=1; var[o][1]-=3;}
			int ch='ï'; if (random(2)) ch='U';
			text(x2,y2,9+random(7),5,ch);
			map[x2][y2]=104;
}   }   }


void gotawep(int r){//GOT A WEAPON
	int a;
	if (r==0){
		do {r=random(6)+2;
		} while(r==5);
	}
	switch (r){
		case 4:
		case 2: a=random(50)+1; break;
		case 6:
		case 3: a=random(10)+1; break;
        case 5:
		case 7: a=random(25)+1; break;
	}
	ammo[r]+=a; char ch[30];
	sprintf(ch,"Wow, %i %s",a,wepname[r]);
	if (a>1) strcat(ch,"s");
	message(ch,wepcolor[r]);
	drawwep();
}


void paws(void){//PAUSE
	//int t=biostime(0,0);
	textbackground(0);
	do{
		gotoxy(maxx/2-10,1);
		textcolor(random(16));
		cputs("ú P ú A ú U ú S ú E ú ");
        snooze(2);
		//delay(50);
	} while(!kbhit());
	getch();
	message ("",0);
	//delay(250);
	//biostime(1,t);
    snooze(10);
}


void initvars(void){//INIT VARS
	for (x=0;x<80;x++) for (y=0;y<50;y++) {map[x][y]=0; mon[x][y]=0;}
	for (int a=1;a<mm;a++){
		mx[a]=0; my[a]=0; mdead[a]=0; mtype[a]=0;}
	for (int a=1;a<10;a++) ammo[a]=0;
	for (int a=1;a<mt;a++)  killed[a]=0;
	cashola=0; lives=5; level=0; amoebafry=0; dead=0; face=2;
	wallcount=0; destcount=0; invuln=0;
	shield=0; trail=0; trailtype=0; drunk=0; lethargy=0; fireball=0;
	sykodump=0; frog=0; snakeshot=0;
	weapon=1; weaponon=1; bvar=0; buld=0; weirdshot=0;
}


void stats(void){//STATS
	char moname[][25]={"","grunt","zoom","tank","helpless dumptruck",
		"aluminum rod","flaming gargoyle","bomb",
		"fire breathing rhino","asp","ostrich bomb farter",
		"smiling bastard coward","mendicant","militant grunt",
		"aluminum man","evil dalek","turret","sonic zoom","psychofish",
		"ninja","resonating aluminum rod","F-16","zombie","cyclops",
		"dispicable xangappa","doppleg„nger"};
	unsigned long tot=0;
	int a;
	for (a=0;a<=40;a++) strnset(line[a],0,40);

	switch(howdied){
	case 2: sprintf(line[1],"Target practice for the tank."); break;
	case 3: sprintf(line[1],"Caught within the blast radius."); break;
	case 4: sprintf(line[1],"The Rhino scorched you!"); break;
	case 5: sprintf(line[1],"Egg hunting can get dangerous."); break;
	case 6: sprintf(line[1],"You would have shot him."); break;
	case 7: sprintf(line[1],"Vaporized by the evil Dalek!!!"); break;
	case 8: sprintf(line[1],"Pecked off by the Turret."); break;
	case 9: sprintf(line[1],"Unseamed from the nave to the chops."); break;
	case 10: sprintf(line[1],"Shuriken, right between the eyes!"); break;
	case 11: sprintf(line[1],"Shot down by the F-16!"); break;
	case 12: sprintf(line[1],"Yes, your bullets can kill you too."); break;
	case 13: sprintf(line[1],"At least you died like a warrior!"); break;
	case 14: sprintf(line[1],"How embarrassing."); break;
	case 15: if (random(2))
				sprintf(line[1],"Fire is hot, and hot things burn.");
			 else
				sprintf(line[1],"Toasted!");
			 break;
	case 16: sprintf(line[1],"Swallowed by the hideous amoeba."); break;
	case 17: sprintf(line[1],"Those bombs are a long range weapon."); break;
	case 18: sprintf(line[1],"Electrocuted by the Xangappas tail."); break;
	case 102: sprintf(line[1],"Zoomed!"); break;
	case 117: sprintf(line[1],"Sonicly Zoomed!"); break;
	case 122: sprintf(line[1],"That monster wasn't quite dead."); break;
	case 118: sprintf(line[1],"Psychofishfood."); break;
	case 123: sprintf(line[1],"Stomped to death by the Cyclops."); break;
	default:
		if (howdied<100) sprintf(line[1],"You died...");
		else{
			int h=howdied-100,r=random(6);
			switch(r){
			case 0: sprintf(line[1],"The %ss will feast tonight!",moname[h]); break;
			case 1: sprintf(line[1],"The %s is not your friend.",moname[h]); break;
			case 2: sprintf(line[1],"You were killed by a %s.",moname[h]); break;
			case 3: sprintf(line[1],"R.I.P."); break;
			case 4: sprintf(line[1],"The chaos was too much for you."); break;
			case 5: sprintf(line[1],"Farewell brave warrior."); break;
			}
		}
	}
	if (cashola%2) sprintf(line[3],"%s, you died with $%i«",name,cashola/2);
	else sprintf(line[3],"%s, you died with $%i",name,cashola/2);
	sprintf(line[4],"and killed:");

	y=6;

	for (int aa=1;aa<mt;aa++){
		int a=tufscale[aa];
		if (killed[a] && a>0){
			if (killed[a]==1) sprintf(line[y],"    1 %s",moname[a]);
			else {
				switch (a){
					case 14: sprintf(line[y],"   %2i aluminum men",killed[a]);  break;
					case 18: sprintf(line[y],"   %2i %s",killed[a],moname[a]);    break;
					case 23: sprintf(line[y],"   %2i cyclopi",killed[a],moname[a]);  break;
					default: sprintf(line[y],"   %2i %ss",killed[a],moname[a]);   break;
				}
			}
			y++;
			tot+=killed[a];
		}
	}
	if (tot>0) {sprintf(line[y],"  ÄÄÄ");
				sprintf(line[y+1],"  %3i",tot); y+=3;}
	else {sprintf(line[y],"Nothing! Geez you're hopeless..."); y+=2;}

	alivetime/=CLK_TCK;
	int h=0,m=0,s=alivetime;
	char st[3];
	while(s>=3600)
		{s-=3600; h++;}
	while(s>=60)
		{s-=60; m++;}
	sprintf(line[y],"and survived the chaos for:");
	y++;
	if (h){
		strcat(line[y],itoa(h,st,10));
		strcat(line[y]," hour");
		if (h>1) strcat(line[y],"s");
		if (m || s) strcat(line[y],", ");}
	if (m){
		strcat(line[y],itoa(m,st,10));
		strcat(line[y]," minute");
		if (m>1) strcat(line[y],"s");
		if (s) strcat(line[y],", ");}
	if (s){
		strcat(line[y],itoa(s,st,10));
		strcat(line[y]," second");
		if (s>1) strcat(line[y],"s");
	}
	y+=2;
	float avg=(tot*600)/alivetime; 	avg/=10;
	sprintf(line[y],"killing an average of %.1f",avg);
	sprintf(line[y+1],"monsters per minute.");
	y+=3;

	if (amoebafry){
		sprintf(line[y],"while frying %i pseudopods of amoeba.",amoebafry);
		y+=3;}

	records(cashola,tot,avg*10);

	//--//
	p=0;
	do{
		if (size) textmode(1);
		textbackground(2); clrscr();
		gotoxy(6,25); textcolor(0); textbackground(4);
		cprintf("    scrolls  <space> quits  ");
		textcolor(1);  textbackground(2);
		for(a=1;a<=24;a++){
			gotoxy(1,a);
			cputs(line[a+p]);
		}
		int key=getch();
		if ((key==SDLK_DOWN || key==SDLK_s) && p<y-24) p++;
		if ((key==SDLK_UP || key==SDLK_w) && p>0) p--;
		if (key==SDLK_SPACE || key==SDLK_z || key==SDLK_RETURN) return;
	} while (1);
}


void records(int yerscore,int yerkills,int yermpm){//RECORDS
	int a,b;
	FILE *scr;
	char place[][5]={"","1st ","2nd ","3rd ","4th ","5th "};

if ((scr=fopen("scores.hi","w+"))!=NULL){

	for(a=1; a<=5; a++){
		if (yerscore>his.score[a]){
			if (a<5){
				for(b=4; b>=a; b--){
					his.score[b+1]=his.score[b];
					strcpy(his.scorer[b+1], his.scorer[b]);
			} 	}
			his.score[a]=yerscore;
			strcpy(his.scorer[a],name);
			sprintf(line[y],"You are the %shighest scorer.",place[a]);
			y+=1; a=6;
		}
	}

	for(a=1; a<=5; a++){
		if (yerkills>his.kills[a]){
			if (a<5){
				for(b=4; b>=a; b--){
					his.kills[b+1]=his.kills[b];
					strcpy(his.killer[b+1], his.killer[b]);
			} 	}
			his.kills[a]=yerkills;
			strcpy(his.killer[a],name);
			sprintf(line[y],"You got the %smost kills.",place[a]);
			y+=1; a=6;
		}
	}

	for(a=1; a<=5; a++){
		if (yermpm>his.mpm[a]){
			if (a<5){
				for(b=4; b>=a; b--){
					his.mpm[b+1]=his.mpm[b];
					strcpy(his.maniac[b+1], his.maniac[b]);
			} 	}
			his.mpm[a]=yermpm;
			strcpy(his.maniac[a],name);
			sprintf(line[y],"You are the %scraziest maniac.",place[a]);
			y+=2; a=6;
		}
	}

	fwrite(&his,sizeof(his),1,scr);
	fclose(scr);

}
}



//              MINOR STUFF              //
void text(int tx,int ty,int tco,int tbc,int tch){
	if (inside(tx,ty)){
		gotoxy(tx,ty);textcolor(tco);textbackground(tbc);putch(tch);}}

void string(int tx,int ty,int tco,int tbc,const char*tch){
	gotoxy(tx,ty);textcolor(tco);textbackground(tbc);cputs(tch);}

int rnd(int rmin,int rmax){
	int rres=random(rmax-rmin+1)+rmin;
	return rres;}

void message(char ch[35],int co){
	textcolor(co);  textbackground(0);
	gotoxy(maxx/2-19,1);
	cputs("                                       ");
	gotoxy((maxx-strlen(ch))/2,1);
	cputs(ch);
	if (ch!="") messagetime=30;
}

void drawlives(void){
	char ch[10];
	textbackground(0);  textcolor(14);
	for (int a=1;a<=lives;a++){
		gotoxy(maxx-6-a,maxy+1);
		putch('');
	}
	gotoxy(maxx-7-lives,maxy+1);  putch(' ');
}

int inside(int x3,int y3){
	int r=0;
	if (x3>1 && y3>2 && x3<maxx && y3<maxy) r=1;
	return r;}

void keepscore(void){
	gotoxy(maxx-5,maxy+1);  textcolor(14);  textbackground(0);
	if (cashola!=1) cprintf("%i",cashola/2);
	if (cashola%2==1) putch('«');  else putch(' ');
}

int bullethrough(int th){
	if (th<100 || th==101 || th==103 || th==104) return 1;
	return 0;}

void putwall(int wx,int wy){
	if ((wx!=x || wy!=y) && !mon[wx][wy] && inside(wx,wy)){
		gotoxy(wx,wy);
		putch('þ');
		map[wx][wy]=100;
}   }

void drawwep(void){
	char ch[25];
	gotoxy(1,maxy+1); textbackground(0);
	cputs("                         ");
	if (weaponon>1) sprintf(ch,"%i %s",ammo[weaponon],wepname[weaponon]);
	else sprintf(ch,"%s",wepname[weaponon]);
	if (ammo[weaponon]>1) strcat(ch,"s");
	textcolor(wepcolor[weaponon]); gotoxy(1,maxy+1);
	cputs(ch);
}

void resetsys(void){
//	deInitSound();
	textbackground(0);
	textmode(initmode);}
