void makemendicant(void);
void high_scores(void);
void entername(void);
void letters(void);
void instructions(void);
void ExitApp();

char cC[7][8]={0,0,0,1,1,1,1,0,
				0,1,1,1,0,0,1,1,
				1,1,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,
				1,1,0,0,0,0,0,0,
				0,1,1,0,0,0,0,0,
				0,0,1,1,0,0,0,0};

char cH[8][9]={0,0,0,0,0,1,0,0,0,
				0,0,0,0,0,1,1,0,0,
				0,0,0,0,0,0,1,0,0,
				1,1,0,0,0,1,1,1,0,
				0,1,1,0,1,1,0,1,1,
				0,0,1,1,1,0,0,0,1,
				0,0,0,1,0,0,0,0,1,
				0,0,0,1,1,0,0,0,0};

char cA[8][7]={1,0,0,0,0,1,1,
				1,1,0,0,0,1,0,
				0,1,0,0,0,1,0,
				0,1,1,1,1,1,0,
				0,0,1,0,1,0,0,
				0,0,1,1,1,0,0,
				0,0,0,1,1,0,0,
				0,0,0,1,0,0,0};

char cO[8][6]={0,0,1,1,0,0,
				0,1,1,1,1,0,
				1,1,0,0,1,1,
				1,0,0,0,0,1,
				1,0,0,0,1,1,
				1,1,0,0,1,0,
				0,1,0,1,1,0,
				0,1,1,1,0,0};

char cS[8][8]={0,0,0,0,1,1,1,0,
				0,0,0,1,1,0,1,1,
				0,0,0,1,0,0,0,1,
				0,0,0,1,1,0,0,0,
				1,0,0,0,1,1,0,0,
				1,0,0,0,0,1,0,0,
				1,1,0,0,1,1,0,0,
				0,1,1,1,1,0,0,0};

char xC,yC,xH,yH,xO,yO,xA,yA,xS,yS;

unsigned int count;

void title(void){
	textmode(1);
	textbackground(0);  clrscr();

start:
	textbackground(2);
	//_setcursortype(_NOCURSOR);
	for (y=3;y<=23;y++) {gotoxy(2,y); cputs(spc[0]);}

	initvars();
	maxx=40; maxy=14; count=0; level=9;
	xC=3;  yC=-10;
	xH=9;  yH=22;
	xA=17; yA=-17;
	xO=24; yO=27;
	xS=55; yS=4;

	for (x=1;x<=40;x++) {textcolor(6); textbackground(4);
						 gotoxy(x,14); map[x][14]=100; putch(254);
						 textcolor(4); textbackground(6);
						 gotoxy(x,2);  map[x][2]=100;  putch(254);
						 gotoxy(x,24); map[x][24]=100; putch(254);}
	for (y=3;y<=24;y++) {gotoxy(1,y);  map[1][y]=100;  putch(254);
						 gotoxy(40,y); map[40][y]=100; putch(254);}

	int t=0,my=1,lp;
	//biostime(1,0);

	do{
		//lp=biostime(0,0);
		t++; if (t>1) t=0;
		key=0;
		while (kbhit()) key=getch();
		textbackground(2);

		textcolor(1);  if (my==1 && t) textcolor(14);
		gotoxy(13,15);  cputs("Ú¿³Ú¿À´ ÚÄÃ´Ú¿Ú¿ÚÄ");
		gotoxy(13,16);  cputs("ÃÙÀÃ´ÀÙ ÀÄ³³Ã´ÀÙÀ¿");
		gotoxy(29,17);                  cputs("ÀÙ");

		textcolor(4);  if (my==2 && t) textcolor(12);
		gotoxy(11,17);  cputs("NAME:");
		gotoxy(17,17);  cputs(name);

		textcolor(5);  if (my==3 && t) textcolor(13);
		gotoxy(18,18);  cputs("HOW TO PLAY");

		textcolor(0);  if (my==4 && t) textcolor(11);
		gotoxy(15,19);  cputs("HI SCORES");

		textcolor(6);  if (my==5 && t) textcolor(14);
		gotoxy(8,20);  cputs("TOUGHNESS:");
		gotoxy(19,20);
		if (tuffness==0)  cputs("NO SWEAT       ");
		if (tuffness==1)  cputs("NAMBY-PAMBY    ");
		if (tuffness==2)  cputs("HARD ROW TO HOE");

		textcolor(1);  if (my==6 && t) textcolor(9);
		gotoxy(10,21);  cputs("SCREEN SIZE:");
		gotoxy(23,21);
		if (size)  cputs("GIGANTIC");
		else     cputs("NORMAL  ");

		/*textcolor(4);  if (my==7 && t) textcolor(12);
		gotoxy(14,22);  cputs("SOUND:");
		gotoxy(21,22);
		if (snd) cputs("ON ");
		else     cputs("OFF");*/

		textcolor(8);  if (my==7 && t) textcolor(15);
		gotoxy(11,22);  cputs("Q U I T ù T O ù D O S");

		if (key==SDLK_UP || key==SDLK_w) {my--; if (my<1) my=7;}
		if (key==SDLK_DOWN || key==SDLK_s) {my++; if (my>7) my=1;}
		if (key==SDLK_z || key==SDLK_b || key==SDLK_RETURN || key==SDLK_SPACE) {
			switch(my){
				case 1:  return;
				case 7:  ExitApp();
				case 4:  high_scores(); goto start;
				case 2:  entername(); break;
				case 3:  instructions(); goto start;
			}
		}
		if (key==SDLK_z || key==SDLK_b || key==SDLK_RETURN || key==SDLK_SPACE || key==SDLK_d || key==SDLK_RIGHT) {
			switch(my){
				case 5:  tuffness++; if (tuffness>2) tuffness=0;  break;
				case 6:  size++; if (size>1) size=0;              break;
				//case 7:  snd++; if (snd>1) snd=0;                 break;
			}
		}
		if (key==SDLK_LEFT || key==SDLK_a) {
			switch(my){
				case 5:  tuffness--; if (tuffness<0) tuffness=2;  break;
				case 6:  size--; if (size<0) size=1;              break;
				//case 7:  snd--; if (snd<0) snd=1;                 break;
			}
		}
		if (key==SDLK_ESCAPE) ExitApp();
		count++;

		if (count>=5 && count<=45) letters();
		x=rnd(2,39); y=rnd(3,13);
		if (count>151) monsters();
		if (count>150 && count<=158) makemendicant();
		//while (biostime(0,0)<lp+2);
        snooze(2);

	} while(1);
}


void makemendicant(void){//MENDICANTS
	int b=count-150;
	mtype[b]=12; md[b]=random(4)+1; mdead[b]=0;
	do{
		if (b%2) {mx[b]=rnd(36,39); my[b]=rnd(12,13);}
		else     {mx[b]=rnd(2,5);   my[b]=rnd(3,4);}
	} while (mon[mx[b]][my[b]]);
	mon[mx[b]][my[b]]=b;
}


void letters(void){//LETTERS
	if (yC<4){//C
		yC++;
		for (x=0;x<=7;x++) for (y=6;y>=0;y--){
			x1=x+xC; y1=y+yC;
			if (inside(x1,y1) && cC[y][x]){
				if (inside(x1,y1-1)) text(x1,y1-1,0,2,' ');
				text(x1,y1,14,1,'þ');
				if (yC==4) map[x1][y1]=102;
		}  }
	}

	if (yH>5){//H
		yH--;
		for (x=0;x<=8;x++) for (y=0;y<=7;y++){
			x1=x+xH; y1=y+yH;
			if (inside(x1,y1) && cH[y][x]){
			if (inside(x1,y1+1)) text(x1,y1+1,0,2,' ');
				text(x1,y1,4,6,'þ');
				if (yH==5) map[x1][y1]=102;
			}}
	}

	if (yA<4){//A
		yA++;
		for (x=0;x<=6;x++) for (y=7;y>=0;y--){
			x1=x+xA; y1=y+yA;
			if (inside(x1,y1) && cA[y][x]){
				if (inside(x1,y1-1)) text(x1,y1-1,0,2,' ');
				text(x1,y1,8,5,'þ');
				if (yA==4) map[x1][y1]=102;
			}}
	}

	if (yO>5){//O
		yO--;
		for (x=0;x<=5;x++) for (y=0;y<=7;y++){
			x1=x+xO; y1=y+yO;
			if (inside(x1,y1) && cO[y][x]){
				if (inside(x1,y1+1)) text(x1,y1+1,0,2,' ');
				text(x1,y1,9,0,'þ');
				if (yO==5) map[x1][y1]=102;
			}}
	}

	if (xS>31){//S
		xS--;
		for (x=0;x<=7;x++) for (y=0;y<=7;y++){
			x1=x+xS; y1=y+yS;
			if (inside(x1,y1) && cS[y][x]){
				if (inside(x1+1,y1)) text(x1+1,y1,0,2,' ');
				text(x1,y1,5,4,'þ');
				if (xS==31) map[x1][y1]=102;
			}}
	}
}


void high_scores(void){//HIGH SCORE LIST
	int a;
	textbackground(2);
	for (y=3;y<=23;y++) {gotoxy(2,y); cputs(spc[0]);}

	string(4,4,14,2,"TOP SCORERS");
	for (a=1; a<=5; a++){
		if (his.score[a]>0){
			textcolor(4); if (a==1) textcolor(12);
			gotoxy(2,5+a);   cprintf("%s",his.scorer[a]);
			textcolor(8); if (a==1) textcolor(15);
			gotoxy(14,5+a);
			if (his.score[a]!=1) cprintf("%i",his.score[a]/2);
			if (his.score[a]%2==1)  putch('«');
		}
	}

	string(26,9,1,2,"TOP KILLERS");
	for (a=1; a<=5; a++){
		if (his.kills[a]>0){
			textcolor(6); if (a==1) textcolor(14);
			gotoxy(24,10+a);   cprintf("%s",his.killer[a]);
			textcolor(8); if (a==1) textcolor(15);
			gotoxy(36,10+a);   cprintf("%i",his.kills[a]);
		}
	}

	string(9,15,4,2,"TOP MANIACS");
	for (a=1; a<=5; a++){
		if (his.mpm[a]>0){
			textcolor(1); if (a==1) textcolor(9);
			gotoxy(7,16+a);     cprintf("%s",his.maniac[a]);
			textcolor(8); if (a==1) textcolor(15);
			gotoxy(19,16+a);
			float f=his.mpm[a]; f/=10;
			cprintf("%.1f",f);
		}
	}

	while (!kbhit()) snooze(2);
    
	getch();
}


void entername(void){//ENTER NAME
	int r=0,co=4;
	char ch;
	string(17,17,0,2,"            ");
	name[0]=0;
	x=0;
	do{
		textbackground(2);
		do{
			textcolor(co);
			if (co==1) co=5;
			else if (co==5) co=4;
			else if (co==4) co=1;
			ch='Ü';
			if (r==1) ch='Ý';
			if (r==2) ch='ß';
			if (r==3) ch='Þ';
			gotoxy(x+17,17);
			putch(ch);
			r++; if (r>3) r=0;
            snooze(2);
			//delay(85);
		} while(!kbhit());
		key=getch();

		if (key==8 && x>0) {x--; name[x]=0;}
		if (key>=32 && x<11) {name[x]=key; name[x+1]=0; x++;}

		string (17,17,0,2,"            ");
		string (17,17,4,2,name);
	} while (key!=SDLK_RETURN);

	char name0[12]; strcpy(name0,name);
	strlwr(name0);
	if (!strcmp(name0,"")) strcpy(name,"Dr. Mung");
	if (strstr(name0,"fuck") || strstr(name0,"shit")) {int r=random(3);
		if (r==0) strcpy(name,"Rose Blossom");
		if (r==1) strcpy(name,"Sunshine");
		if (r==2) strcpy(name,"Bunnywugums");
	}
	if (strstr(name0,"code") || strstr(name0,"cheat") || strstr(name0,"god"))
		strcpy(name,"I Reek");
}


void instructions(void){//INSTRUCTIONS
	maxy=23;
	textbackground(2);
	for (y=3;y<=23;y++) {gotoxy(2,y); cputs(spc[0]);}
	string (10,3,5,2,"ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ·");
	string (12,4,14,4, "HOW TO PLAY CHAOS");
	string (10,5,5,2,"ÔÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼");
	text (10,4,5,2,'³');  text(30,4,5,2,'º');

	string (2,7,14,2,"OBJECT-");
	string (2,8,1,2, "  Survive as long as possible, get as");
	string (2,9,1,2, "  much cash as you can, and destroy  ");
	string (2,10,1,2, "  monters.  There is no end to Chaos,");
	string (2,11,1,2,"  if just gets more and more hellish.");
	string (2,12,1,2,"  Why even bother trying then?  Well,");
	string (2,13,1,2,"  you can't just stand there, with   ");
	string (2,14,1,2,"  your ZX81 zap gun and get eaten    ");
	string (2,15,1,2,"  alive by the living scum of the    ");
	string (2,16,1,2,"  the underworld.                    ");
	string (13,23,0,4," PRESS ANY KEY ");
    while (!kbhit()) snooze(2);
    getch();

	textbackground(2);
	for (y=3;y<=23;y++) {gotoxy(2,y); cputs(spc[0]);}
	string (2,3,14,2,"MOVING AROUND-");
	string (2,5,6,2, "   The four arrow keys or WASD will,  ");
	string (2,6,6,2, "   most of the time move you in the   ");
	string (2,7,6,2, "   indicated directions.");
	string (2,9,1,2, "   Z or B + arrows fires.");
	string (2,11,8,2,"   X or N switches between weapons.");
	//string (2,12,8,2,"   weapons.");
	string (2,13,4,2,"   The number keys 1 to 7 also switch ");
	string (2,14,4,2,"   weapons.");
	string (2,16,5,2,"   C or M switches to your zap gun.");
	string (2,18,1,2,"   P pauses.");
	string (2,19,0,2,"   ESC quits to the title screen.");
	string (2,20,6,2,"   F10 quits right to DOS.");
	string (14,23,0,4," PRESS A KEY ");
    while (!kbhit()) snooze(2);
    getch();

	textbackground(2);
	for (y=3;y<=23;y++) {gotoxy(2,y); cputs(spc[0]);}
	string (2,3,14,2,"MATERIAL MANIFESTATIONS-");
	string (2,5,8,2, "   þþþ typical walls");
	string (2,6,8,2, "   ð   pushable walls");
	string (2,7,8,2, "   *   burning flaming fire");
	string (2,8,8,2, "   +   dead zap gun bullets");
	string (2,9,8,2, "   ›$  wads of cash");
	string (2,10,8,2,"     wall creators");
	string (2,11,8,2,"   ÷   general destructors");
	string (2,12,8,2,"     ammunition trees");
	string (2,14,1,2,"  If you see something strange, try  ");
	string (2,15,1,2,"  picking it up and see what it does.");
	text (5,5,4,6,'þ');   text(6,5,1,0,'þ');   text(7,5,6,4,'þ');
	text (5,6,1,5,'ð');   text(5,7,4,2,'*');   text(5,8,15,2,'+');
	string (5,9,14,2,"›$");  string (5,10,1,2,"");
	text (5,11,8,2,'÷');  text(5,12,10,2,''); text(6,12,6,2,'');
	string (11,23,0,4," PRESS ANY OL' KEY ");
    while (!kbhit()) snooze(2);
    getch();

	textbackground(2);
	for (y=3;y<=23;y++) {gotoxy(2,y); cputs(spc[0]);}
	string (2,3,14,2,"LOCAL INHABITANTS OF CHAOS-");
	string (2,5,1,2, " ”  Grunts. About the stupidest      ");
	string (2,6,1,2, "    monster imaginable.");
	string (2,8,1,2, " z  Zooms. It is every zooms greatest");
	string (2,9,1,2, "    ambition to die while charging at");
	string (2,10,1,2,"    their enemy. Quite stupid.");
	string (2,12,1,2," \\  Aluminum Rods. Giant 12 foot long");
	string (2,13,1,2,"    spinning metal rods.");
	string (2,15,1,2," H  Dump Trucks. The hard working");
	string (2,16,1,2,"    engineers of the underworld.");
	string (2,18,4,2,"  There are, in total, more than 24« ");
	string (2,19,4,2,"  different types of monsters to make");
	string (2,20,4,2,"  friends with in Chaos, each type  ");
	string (2,21,4,2,"  with it's own unique personality.");
	text (3,5,6,2,'”');    text (3,8,5,2,'z');
	text (3,15,5,0,'H');   text (3,12,15,2,'\\');
	string (8,23,0,4," PRESS ONE OF THOSE KEYS ");
    while (!kbhit()) snooze(2);
    getch();

	textbackground(2);
	for (y=3;y<=23;y++) {gotoxy(2,y); cputs(spc[0]);}
	string (2,3,14,2,"ALSO-");
	string (2,5,6,2, "  New monsters will start to appear  ");
	string (2,6,6,2, "  as your score increases.");
	string (2,8,1,2, "  There are two screen sizes you can ");
	string (2,9,1,2, "  play on, but keep in mind, the big ");
	string (2,10,1,2,"  one is only for the keen of sight. ");
	string (2,12,5,2,"  The three difficuly levels regulate");
	string (2,13,5,2,"  the rate in which monsters will be ");
	string (2,14,5,2,"  brought into existance.");
	string (2,16,4,2,"  All weapons, except your trusty Zap");
	string (2,17,4,2,"  gun, have limited ammo.  Extra ammo");
	string (2,18,4,2,"  can be found growing on the local  ");
	string (2,19,4,2,"  vegetation.");
	string (2,21,8,2,"  Just one hint: Bombs can be pushed.");

	string (14,23,0,4," PRESS KEY ");
    while (!kbhit()) snooze(2);
    getch();

	textbackground(2);
	for (y=3;y<=23;y++) {gotoxy(2,y); cputs(spc[0]);}
	text(20,5,14,2,'');
	string (2,8,4,2, "Have a holly-jolly time playing Chaos.");
	string (14,14,8,2,"and remember...");
	string (6,17,1,2,"Never take candy from a Dalek.");
	string (10,23,0,4," PRESS ONE MORE KEY ");
    while (!kbhit()) snooze(2);
    getch();

	maxy=14;
}
