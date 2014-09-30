void rhinobreath(int,int,int);
int deflect(int);

void grunt(int b){//GRUNT
	if (mdead[b]) {die(b,1);  return;}
//	if (hear==b && !random(10)) noise(1,0);
	if (!random(6)) md[b]=random(5);
	if (!random(3) && md[b]) {
		x1=mx[b]+dx[md[b]];
		y1=my[b]+dy[md[b]];
		mon[mx[b]][my[b]]=0;
		text(mx[b],my[b],6,2,' ');
		p=map[x1][y1];
		o=mon[x1][y1];
		if (p<100 && o<=0) {mx[b]=x1; my[b]=y1;}
	}
	text(mx[b],my[b],6,2,'”');
	map[mx[b]][my[b]]=0;
	mon[mx[b]][my[b]]=b;
}


void zoom(int b){//ZOOM
	if (mdead[b]) {die(b,4);  return;}
	if (!random(3)) md[b]=random(4)+1;
	int a=0,speed=1;
	if (mx[b]==x) {speed=2;  if (my[b]<y) md[b]=3; else md[b]=1;}
	if (my[b]==y) {speed=2;  if (mx[b]<x) md[b]=2; else md[b]=4;}
	for (a=1;a<=speed;a++){
/*		if (hear==b){
			if (speed==1){
				if (random(10)) noise(3,0);
			} else{
				noise(4,0);
			}
		}
*/		x1=mx[b]+dx[md[b]];
		y1=my[b]+dy[md[b]];
		mon[mx[b]][my[b]]=0;
		text(mx[b],my[b],6,2,' ');
		p=map[x1][y1];
		o=mon[x1][y1];
		if (p<100 && o<=0) {mx[b]=x1; my[b]=y1;}
		else md[b]=random(4)+1;
		if (p==50) {mdead[b]=2; die(b,4); destbul(); return;}
		if (o==-1) a=speed;
		text(mx[b],my[b],5,2,'z');
	}
	map[mx[b]][my[b]]=0;
	mon[mx[b]][my[b]]=b;
}


void tank(int b){//TANK
	if (mdead[b]) {
		var[b][1]--;
		if (mdead[b]==2 && (weapon==5 || weapon==6)) var[b][1]-=2;
		if (var[b][1]<=0) {
						   if (bd[b]) {text(bx[b],by[b],0,2,' ');
									   map[bx[b]][by[b]]=0;}
						   die(b,100);  return;}
		mdead[b]=0;
	}

	if (init[b]) {var[b][1]=3;  init[b]=0;}

	if (!random(8)) md[b]=random(4)+1;
	if (!random(7-var[b][1])){
		x1=mx[b]+dx[md[b]];
		y1=my[b]+dy[md[b]];
		mon[mx[b]][my[b]]=0;
		p=map[x1][y1];
		o=mon[x1][y1];

		int tru=0;
		if (p<100 || p==101 || p==105) tru=1;
		if (o>0){
			int t=mtype[o];
			tru=0;
			if (t!=3 && t!=4 && t!=6 && t!=8 && t!=10 && t!=14 && t!=15
				&& t!=16 && t!=19 && t!=20 && t!=21 && t!=23)
					{tru=1; mdead[o]=3;}
		}

		text(mx[b],my[b],0,2,' ');
		if (tru) {mx[b]=x1; my[b]=y1;}
	}
	text(mx[b],my[b],0,2,'è');
	map[mx[b]][my[b]]=0;
	mon[mx[b]][my[b]]=b;


	if (!bd[b]){
		if (!random(5)){
			bx[b]=mx[b];
			by[b]=my[b];
			int r=random(2);
			if (r) if (x<mx[b]) bd[b]=4; else bd[b]=2;
			else if (y<my[b]) bd[b]=1; else bd[b]=3;
		}
	}
	if (bd[b]){
		int l=0;
		for (l=1;l<=2;l++){
			if (bx[b]!=mx[b] || by[b]!=my[b]) text(bx[b],by[b],8,2,' ');
			x1=bx[b]+dx[bd[b]];
			y1=by[b]+dy[bd[b]];
			map[bx[b]][by[b]]=0;
			o=mon[x1][y1];
			if (bullethrough(map[x1][y1])){
				bx[b]=x1;  by[b]=y1;
				map[x1][y1]=51;
				text(bx[b],by[b],8,2,'ù');
				if (o>0) if (mtype[o]!=14)
					{mdead[o]=1; bd[b]=0; l=3;}
				else
					bd[b]=deflect(bd[b]);
				if (o==-1) {you_die(2); bd[b]=0; l=3;}
			}
			else {bd[b]=0; l=3;}
		}
	}
}


void dumptruck(int b){//DUMP TRUCK
	if (mdead[b]) {die(b,0);  return;}
	if (!random(9) || sykodump){
		if (!random(9)) md[b]=random(4)+1;
		if ((mx[b]==1 || mx[b]==maxx-1) && !random(5)) md[b]=random(4)+1;
		if ((my[b]==2 || my[b]==maxy-1) && !random(5)) md[b]=random(4)+1;
		x1=mx[b]+dx[md[b]];
		y1=my[b]+dy[md[b]];
		mon[mx[b]][my[b]]=0;
		int d1=md[b]+1; if (d1==5) d1=1;
		int x2=mx[b]+dx[d1];
		int y2=my[b]+dy[d1];
		text(mx[b],my[b],6,4,'þ');
		p=map[x2][y2];
		if (p==100 && inside(x2,y2)){
			text(x2,y2,6,2,' ');
			map[x2][y2]=0;
		}
		map[mx[b]][my[b]]=100;
		p=map[x1][y1];
		o=mon[x1][y1];
		if (p<=100 && o<=0 && inside(x1,y1))
			{mx[b]=x1; my[b]=y1;}
	}
	text(mx[b],my[b],5,0,'H');
	mon[mx[b]][my[b]]=b;
	map[mx[b]][my[b]]=0;
}


void aluminum_rod(int b){//ALUMINUM ROD
	if (mdead[b]) {die(b,10);  return;}
	if (random(3)){
//		if (hear==b) noise(2,0);
		int r=random(2)+1;
		if (y==my[b] || x==mx[b]) r=0;
		if (x==mx[b] || r==1) {if (y<my[b]) md[b]=1; else md[b]=3;}
		if (y==my[b] || r==2) {if (x<mx[b]) md[b]=4; else md[b]=2;}
		if (!random(5)) md[b]=random(5);
		x1=mx[b]+dx[md[b]];
		y1=my[b]+dy[md[b]];
		p=map[x1][y1];
		if (p>=50 && p<100) if (random(2))
			 {md[b]++; if (md[b]>4) md[b]=1;}
		else {md[b]--; if (md[b]<1) md[b]=4;}

		x1=mx[b]+dx[md[b]];
		y1=my[b]+dy[md[b]];
		mon[mx[b]][my[b]]=0;
		text(mx[b],my[b],15,2,' ');

		p=map[x1][y1];
		o=mon[x1][y1];
		if (p<100 && o<=0) {mx[b]=x1;  my[b]=y1;}
	}
	var[b][1]=!(var[b][1]); int c;
	if (var[b][1]) c=47; else c=92;
	text(mx[b],my[b],15,2,c);
	mon[mx[b]][my[b]]=b;
	map[mx[b]][my[b]]=0;

	int t=0;
	for (int a=1;a<=4;a++){
		x1=mx[b]+dx[a]; y1=my[b]+dy[a];
		if (map[x1][y1]>=100) t++;}
	if (t==4) mtype[b]=20;
}


void gargoyle(int b){//GARGOYLE
	if (mdead[b]) {die(b,50); return;}

	if (bx[b]==0 || by[b]==0) {bx[b]=random(2)*2-1; by[b]=random(2)*2-1;}
	p=map[mx[b]+bx[b]][my[b]+by[b]];
	if (p==100 || p==102 || !random(10)){
		if (random(2)) bx[b]=-bx[b]; else by[b]=-by[b];
	}
	x1=mx[b]+bx[b];
	y1=my[b]+by[b];
	mon[mx[b]][my[b]]=0;
	if (map[mx[b]][my[b]]==104){
		if (random(2)) text(mx[b],my[b],8,0,'U');
		else text(mx[b],my[b],8,0,'ï');}
	else{
		if (var[b][1])
			{map[mx[b]][my[b]]=0; text(mx[b],my[b],4,2,' ');}
		else
			{map[mx[b]][my[b]]=103;	text(mx[b],my[b],4,2,'*');}
	}
	p=map[x1][y1];
	if (p!=100 && p!=102) {mx[b]=x1; my[b]=y1;}

	text(mx[b],my[b],12,2,'%');
	mon[mx[b]][my[b]]=b;

	if (!random(220)) {mon[mx[b]][my[b]]=0; mtype[b]=0;
					   text (mx[b],my[b],4,2,'*');}
	if (!random(15) &&  var[b][1]) var[b][1]=0;
	if (!random(30) && !var[b][1]) var[b][1]=1;
}


void bomb(int b){//BOMB
	if (mdead[b]){
		if (mdead[b]==2 && var[b][1]==0){
			destbul();  cashola+=2;  keepscore();
			killed[7]++;  var[b][3]=1;
//			if (hear==b) noise(16,1);
		}
		var[b][1]++;
		for(int a=1;a<=rnd(2,4);a++){
			do{
				x1=mx[b]+random(5)-2;
				y1=my[b]+random(5)-2;
			} while(abs(x1-mx[b])+abs(y1-my[b])>3 || !inside(x1,y1));
			p=map[x1][y1];
			if (p && p!=103){
				int x2=x1,y2=y1;
				map[x1][y1]=0;
				if (x1<mx[b] && random(2)) x2--;
				if (x1>mx[b] && random(2)) x2++;
				if (y1<my[b] && random(2)) y2--;
				if (y1>my[b] && random(2)) y2++;
				if (x2<2) x2=2;
				if (x2>maxx-1) x2=maxx-1;
				if (y2<3) y2=3;
				if (y2>maxy-1) y2=maxy-1;
				if (map[x2][y2]==0){
					map[x2][y2]=p;
					gettext(x1,y1,x1,y1,&var[b][4]);
					puttext(x2,y2,x2,y2,&var[b][4]);
				}
			}
			p=map[x1][y1];
			if (p<100 || p==101 || p==103){
				if (var[b][1]<4){
					text(x1,y1,4,2,'*');
					map[x1][y1]=103;
				}else{
					text(x1,y1,4,2,' ');
					map[x1][y1]=0;}
			}
			o=mon[x1][y1];
			if (o>0 && o!=b) {mdead[o]=1+var[b][3]; var[o][1]-=3;}
			if (o==-1) you_die(3);
		}
		if (var[b][1]>5) {die(b,0);  return;}
	}
	else{
		if (!random(5) || var[b][2]){
			if (!random(3) && var[b][2]==0) {md[b]=random(4)+1; if (random(2)) md[b]=0;}
			var[b][2]=0;
			x1=mx[b]+dx[md[b]];
			y1=my[b]+dy[md[b]];
			mon[mx[b]][my[b]]=0;
			text(mx[b],my[b],1,2,' ');

			p=map[x1][y1];
			o=mon[x1][y1];
			if (p==0 && o==0) {mx[b]=x1;  my[b]=y1;}
		}
		text(mx[b],my[b],4,2,'');
		map[mx[b]][my[b]]=0;
		mon[mx[b]][my[b]]=b;
	}
}


void rhino(int b){//RHINO
	if (mdead[b]){
		if (var[b][1]){
			if (bd[b]==1 || bd[b]==3){
				for(int x2=bx[b]-1;x2<=bx[b]+1;x2++){
					rhinobreath(' ',x2,by[b]);}}
			else{
				for(int y2=by[b]-1;y2<=by[b]+1;y2++){
					rhinobreath(' ',bx[b],y2);}}
		}
		die(b,70); return;
	}
	if (!random(3) && var[b][1]==0){
		if (!random(5)) md[b]=random(5);
		if (!random(5)) if (random(2))
			{md[b]=2; if (mx[b]>maxx/2) md[b]=4;}
		else{md[b]=3; if (my[b]>maxy/2) md[b]=1;}

		x1=mx[b]+dx[md[b]];
		y1=my[b]+dy[md[b]];
		mon[mx[b]][my[b]]=0;
		text(mx[b],my[b],8,2,' ');

		p=map[x1][y1];
		o=mon[x1][y1];
		if (p<100 && o==0) {mx[b]=x1; my[b]=y1;}
	}
	text(mx[b],my[b],8,2,'R');
	mon[mx[b]][my[b]]=b;
	map[mx[b]][my[b]]=0;

	if (!var[b][1] && !random(20)){
		if (random(7)>2)
			{bd[b]=2; if (mx[b]>maxx/2) bd[b]=4;}
		else
			{bd[b]=3; if (my[b]>maxy/2) bd[b]=1;}
		if (!random(4)) bd[b]=random(4)+1;
		bx[b]=mx[b];
		by[b]=my[b];
		var[b][1]=1;
		var[b][2]=rnd(8,22);
	}

	if (var[b][1]){
		for (int l=1;l<=2;l++){
		if (bx[b]!=mx[b] || by[b]!=my[b]){
			if (bd[b]==1 || bd[b]==3){
				for(int x2=bx[b]-1;x2<=bx[b]+1;x2++){
					rhinobreath(' ',x2,by[b]);}}
			else{
				for(int y2=by[b]-1;y2<=by[b]+1;y2++){
					rhinobreath(' ',bx[b],y2);}}
		}
			var[b][2]--;
			bx[b]+=dx[bd[b]];
			by[b]+=dy[bd[b]];
			if (var[b][2]<=0 || !inside(bx[b],by[b])) {var[b][1]=0; return;}
			if (bd[b]==1 || bd[b]==3){
				for(int x2=bx[b]-1;x2<=bx[b]+1;x2++){
					rhinobreath('*',x2,by[b]);}}
			else{
				for(int y2=by[b]-1;y2<=by[b]+1;y2++){
					rhinobreath('*',bx[b],y2);}}
		}
	}
}
void rhinobreath(int ch,int x2,int y2){
	if (inside(x2,y2)){
		map[x2][y2]=0;
		text(x2,y2,12,2,ch);
		o=mon[x2][y2];
		if (o>0) mdead[o]=3;
		if (o==-1) you_die(4);
}	}


void snake(int b){//SNAKE
	if (mdead[b]) {die(b,13);  return;}

//		if (hear==b && !random(4)) noise(9+random(2),0);
		int r=random(2)+1;
		if (y==my[b] || x==mx[b]) r=0;
		if (x==mx[b] || r==1) {if (y<my[b]) md[b]=1; else md[b]=3;}
		if (y==my[b] || r==2) {if (x<mx[b]) md[b]=4; else md[b]=2;}

		for (int a=1;a<=2;a++){
			x1=mx[b]+a*dx[md[b]];
			y1=my[b]+a*dy[md[b]];
			p=map[x1][y1];
			if ((p>=50 && p<100 || mon[x1][y1]>0) && random(3)){
				a=3;
				md[b]++; if (md[b]>4) md[b]=1;}
		}
		x1=mx[b]+dx[md[b]];
		y1=my[b]+dy[md[b]];
		mon[mx[b]][my[b]]=0;
		text(mx[b],my[b],15,2,' ');

		p=map[x1][y1];
		o=mon[x1][y1];
		if (p<100 && o<=0) {mx[b]=x1;  my[b]=y1;}
		else md[b]++;

	text(mx[b],my[b],10,2,'S');
	mon[mx[b]][my[b]]=b;
	map[mx[b]][my[b]]=0;

}


void ostrich(int b){//OSTRICH
	if (mdead[b]) {
		if (!var[b][3]) {die(b,27); var[b][3]=1;
						 mtype[b]=10; mx[b]=0; my[b]=0;}
		if (!bd[b]) {mtype[b]=0; return;}
	} else {
	if (init[b]) {init[b]=0; gettext(mx[b],my[b],mx[b],my[b],&var[b][1]);
				  var[b][3]=0;}

	if (!random(8) || md[b]==0) md[b]=random(4)+1;

	x1=mx[b]+dx[md[b]];
	y1=my[b]+dy[md[b]];
	mon[mx[b]][my[b]]=0;
	puttext(mx[b],my[b],mx[b],my[b],&var[b][1]);

	if (inside(x1,y1)) {mx[b]=x1; my[b]=y1;}
	else md[b]=random(4)+1;

	p=map[mx[b]][my[b]];
	o=mon[mx[b]][my[b]];
	if (o || p==50 || p==51) text(mx[b],my[b],0,2,' ');
	gettext(mx[b],my[b],mx[b],my[b],&var[b][1]);
	if (o && mtype[o]==16) var[b][1]=var[o][2];
	text (mx[b],my[b],6,2,'ë');
	mon[mx[b]][my[b]]=b;
	}

	if (!bd[b] && !random(40)){
		map[mx[b]][my[b]]=105;
		text(mx[b],my[b],15,2,'o');
		gettext(mx[b],my[b],mx[b],my[b],&var[b][1]);
		bd[b]=rnd(10,70);
		bx[b]=mx[b]; by[b]=my[b];
	}
	if (bd[b]){
		if (map[bx[b]][by[b]]!=105 && bd[b]>=5) {bd[b]=0; return;}
		bd[b]--;
		if (bd[b]<5){
			if (bd[b]==4 && mdead[b] && random(3)){
				mdead[b]=0;
				mx[b]=bx[b]; my[b]=by[b]; md[b]=random(4)+1;
				bd[b]=0;
				text(mx[b],my[b],0,2,' ');
				if (random(2)) mtype[b]=9;
				return;
			}
			for (int a=1;a<=5;a++){
//				if (bd[b]==4) noise(15,1);
				do{
					x1=bx[b]+random(5)-2;
					y1=by[b]+random(5)-2;
				} while(abs(x1-bx[b])+abs(y1-by[b])>3 || !inside(x1,y1));
				if (a==1) {x1=bx[b]; y1=by[b];}
				if (bd[b]<2){
					text(x1,y1,4,2,' ');
					map[x1][y1]=0;}
				else{
					text(x1,y1,4,2,'*');
					map[x1][y1]=103;}
				o=mon[x1][y1];
				if (o>0) {mdead[o]=1; var[o][1]-=3;}
				if (o==-1) you_die(5);
			}
		}
	}
}


void bastardcoward(int b){//BASTARD COWARD
	if (mdead[b]) {die(b,23); return;}

//	if (hear==b && !random(10)) noise(18+random(2),0);
	int t=0;
	if (abs(mx[b]-x)<10 && abs(my[b]-y)<10){
		do{
			t++;
			int r=random(2)+1;
			if (r==1) {if (y<my[b]) md[b]=3; else md[b]=1;}
			if (r==2) {if (x<mx[b]) md[b]=2; else md[b]=4;}
			if (mx[b]==x) if (random(2)) md[b]=2; else md[b]=4;
			if (my[b]==y) if (random(2)) md[b]=1; else md[b]=3;
		} while (map[mx[b]+dx[md[b]]] [my[b]+dy[md[b]]] && t<6);
	} else {
		if (!random(3)) md[b]=random(4)+1;
	}
	for (int di=1;di<=4;di++){
		for (int a=1;a<=2;a++){
			x1=mx[b]+a*dx[di];
			y1=my[b]+a*dy[di];
			p=map[x1][y1];
			if (p>=50 && p<100){
				md[b]=di+random(2)*2-1;
				if (md[b]>4) md[b]=1;
				if (md[b]<1) md[b]=4;
	}	}	}
	x1=mx[b]+dx[md[b]];
	y1=my[b]+dy[md[b]];
	mon[mx[b]][my[b]]=0;
	text(mx[b],my[b],15,2,' ');

	p=map[x1][y1];
	o=mon[x1][y1];
	if (p==0 && o==0) {mx[b]=x1;  my[b]=y1;}
	else md[b]+=random(3)-1;

	text(mx[b],my[b],12,2,'');
	mon[mx[b]][my[b]]=b;
	map[mx[b]][my[b]]=0;
}


void mendicant(int b){//MENDICANT
	if (mdead[b]) {die(b,5); return;}

//	if (hear==b && !random(10)) noise(12,0);
	if (mx[b]==bx[b] && my[b]==by[b]) bx[b]=0;
	if (bx[b]==0){
		if (!random(4)) md[b]=random(4)+1;
		for (int a=0;a<=12;a++){
			x1=mx[b]+random(7)-3;
			y1=my[b]+random(7)-3;
			p=0;
			if (inside(x1,y1)) p=map[x1][y1];
			if (p==102 || p==105 || p==101 || p>0 && p<50) {bx[b]=x1; by[b]=y1;}
		}
	} else {
		int r=random(2)+1;
		if (by[b]==my[b] || bx[b]==mx[b]) r=0;
		if (bx[b]==mx[b] || r==1) {if (by[b]<my[b]) md[b]=1; else md[b]=3;}
		if (by[b]==my[b] || r==2) {if (bx[b]<mx[b]) md[b]=4; else md[b]=2;}
		if (!random(10)) bx[b]=0;
	}
	x1=mx[b]+dx[md[b]];
	y1=my[b]+dy[md[b]];
	mon[mx[b]][my[b]]=0;
	text(mx[b],my[b],15,2,' ');

	p=map[x1][y1];
	o=mon[x1][y1];
	if (p==102){
		int d=md[b]; if (!random(3)) d+=random(3)-1;
		if (d<1) d=4;
		if (d>4) d=1;
		int x2=x1,y2=y1;
		if (!mon[x1+dx[d]][y1+dy[d]]){
			if (push(x2,y2,d) && map[x1][y1]==0) {mx[b]=x1; my[b]=y1;}
			else {md[b]+=random(3)-1; bx[b]=0;}
		}
	}
	if ((p<100 || p==105 || p==101) && o<=0)
		{mx[b]=x1;  my[b]=y1;}
	else {md[b]+=random(3)-1; bx[b]=0;}

	if (md[b]<1) md[b]+=4;
	if (md[b]>4) md[b]-=4;

	text(mx[b],my[b],1,2,'Œ');
	mon[mx[b]][my[b]]=b;
	map[mx[b]][my[b]]=0;
}


void militant_grunt(int b){//MILITANT GRUNT
	if (mdead[b]) {
		if (bd[b]){
			map[bx[b]][by[b]]=0;
			text(bx[b],by[b],0,2,' ');}
		die(b,6);  return;
	}
//	if (hear==b && !random(10)) noise(5,0);
	if (!random(6)) md[b]=random(5);
	if (!random(3)) {
		x1=mx[b]+dx[md[b]];
		y1=my[b]+dy[md[b]];
		mon[mx[b]][my[b]]=0;
		text(mx[b],my[b],6,2,' ');
		p=map[x1][y1];
		o=mon[x1][y1];
		if (p<100 && o<=0) {mx[b]=x1; my[b]=y1;}
	}
	text(mx[b],my[b],8,2,'™');
	map[mx[b]][my[b]]=0;
	mon[mx[b]][my[b]]=b;

	if (!bd[b] && !random(10)){
//		if (hear==b) noise(6,0);
		bx[b]=mx[b];
		by[b]=my[b];
		bd[b]=0;
		for (int a=1;a<=4;a++){
			for (int d=1;d<=5;d++){
				x1=mx[b]+d*dx[a];
				y1=my[b]+d*dy[a];
				if (inside(x1,y1)){
					if (map[x1][y1]==104) bd[b]=a;
		}	}	}
		if (bd[b]==0){
			do{ bd[b]=random(4)+1;
			} while(bd[b]==md[b]);
		}
	}
	if (bd[b]){
		if (bx[b]!=mx[b] || by[b]!=my[b]) text(bx[b],by[b],8,2,' ');
		x1=bx[b]+dx[bd[b]];
		y1=by[b]+dy[bd[b]];
		map[bx[b]][by[b]]=0;
		o=mon[x1][y1];
		if (bullethrough(map[x1][y1])){
			bx[b]=x1;  by[b]=y1;
			map[x1][y1]=51;
			text(bx[b],by[b],0,2,'ø');
			if (o>0) {mdead[o]=1; bd[b]=0;}
			if (o==-1) {you_die(6); bd[b]=0;}
		}
		else bd[b]=0;
	}
}


void aluminum_man(int b){//ALUMINUM MAN
	if (mdead[b]){
		if (mdead[b]==3 || (mdead[b]==2 && (weapon==6 || weapon==5 || fireball)))
			{die(b,0); return;}
		for(int a=1;a<mm-1;a++){
			if (mx[b]==bx[a] && my[b]==by[a]) bd[a]=deflect(bd[a]);
	}   }
	if (!random(6)) md[b]=random(5);
	if (!random(4)) {
//		if (hear==b) noise(8,0);
		x1=mx[b]+dx[md[b]];
		y1=my[b]+dy[md[b]];
		mon[mx[b]][my[b]]=0;
		text(mx[b],my[b],6,2,' ');
		p=map[x1][y1];
		o=mon[x1][y1];
		if (p<100 && o<=0) {mx[b]=x1; my[b]=y1;}
	}
	text(mx[b],my[b],11,2,'ä');
	map[mx[b]][my[b]]=0;
	mon[mx[b]][my[b]]=b;

	int t=0;
	for (int a=1;a<=4;a++){
		x1=mx[b]+dx[a]; y1=my[b]+dy[a];
		if (map[x1][y1]>=100) t++;}
	if (t==4){
		for (int a=0;a<=4;a++){
			x1=mx[b]+dx[a]; y1=my[b]+dy[a];
			if (inside(x1,y1)){
				map[x1][y1]=4;
				text(x1,y1,14,2,'$');}
		}
		killed[14]++;
		die(b,0);
	}
}
int deflect(int dd){
	dd+=1+random(3);
	if (dd>4) dd-=4;
	return dd;}


void dalek(int b){//DALEK
	if (mdead[b]){
		if (bd[b]){
			for(int a=1;a<=var[b][2];a++){
				x1=mx[b]+a*dx[bd[b]];
				y1=my[b]+a*dy[bd[b]];
				if (inside(x1,y1)) text(x1,y1,0,2,' ');
			}
		}
	die(b,199); return;
	}

	if (init[b] || !random(100)){
		init[b]=0;
		message ("EXTERMINATE!!!",12);
	}

	if (!random(3) && !bd[b]){
		if (!random(4)){
			md[b]=random(5);
			if (random(2)){
				if (random(2)) {md[b]=1; if (my[b]<maxy/2) md[b]=3;}
				else {md[b]=4; if (mx[b]<maxx/2) md[b]=2;}
			}
		}
		x1=mx[b]+dx[md[b]];
		y1=my[b]+dy[md[b]];
		mon[mx[b]][my[b]]=0;
		text(mx[b],my[b],15,2,' ');

		p=map[x1][y1];
		o=mon[x1][y1];
		if ((p<100 || p==101 || p==103 || p==105) && o<=0)
			{mx[b]=x1; my[b]=y1;}
	}
	text (mx[b],my[b],11,2,'ê');
	mon[mx[b]][my[b]]=b;
	map[mx[b]][my[b]]=0;

	int rs=random(4)+1,a,r=random(4)+4,tru=0;
	for(int a1=rs;a1<=rs+3;a1++){
		a=a1; if (a>4) a-=4;
		for(int di=1;di<=r;di++){
			x1=mx[b]+di*dx[a];
			y1=my[b]+di*dy[a];
			if (inside(x1,y1)){
				p=map[x1][y1];
				o=mon[x1][y1];
				if (p>=50 && p<100 || o==-1){
					if (bd[b]) var[b][3]=1; else tru=1;}
				if (o>0 && mtype[o]!=15 && !bd[b]) tru=1;
			}
		}
		if (!random(70) && !bd[b]) tru=1;
		if (tru){
			bd[b]=a; a1=10;
			var[b][2]=r;
			var[b][3]=4+random(8);
		}
	}

	if (bd[b]){
		var[b][3]--;
		int col=4, r=var[b][3]%3;
		if (r==1) col=12;
		if (r==2) col=14;
		for(int a=1;a<=var[b][2];a++){
			x1=mx[b]+a*dx[bd[b]];
			y1=my[b]+a*dy[bd[b]];
			if (inside(x1,y1)){
				p=map[x1][y1];
				o=mon[x1][y1];
				if (o==-1) you_die(7);
				if (o>0) {mon[x1][y1]=0; mdead[o]=3; var[o][1]-=3;}
				map[x1][y1]=0;
				if (p==50) buld=0;
				if (p==51){
					for (int t=1;t<=mm-1;t++){
						if (bx[t]==x1 && by[t]==y1) bd[t]=0;}}
				if (var[b][3]==0) text(x1,y1,0,2,' ');
				else text(x1,y1,col,2,'Û');
			}
		}
		if (var[b][3]==0) bd[b]=0;
	}
}


void turret(int b){//TURRET
	if (mdead[b]){
		if (bd[b]){
			map[bx[b]][by[b]]=0;
			text(bx[b],by[b],0,2,' ');}
		die(b,20); return;
	}
	if (init[b]){
		init[b]=0;
		int a=0;
		while(map[mx[b]][my[b]]!=100 && a<50){
			a++;
			mx[b]=rnd(2,maxx-1);
			my[b]=rnd(3,maxy-1);}
		gettext(mx[b],my[b],mx[b],my[b],&var[b][2]);
	}
	var[b][1]++; if (var[b][1]>1) var[b][1]=0;
	if (var[b][1]%2){
		int d1=md[b]+random(2)*2+1; if (d1>4) d1-=4;
		if (map[mx[b]+dx[d1]][my[b]+dy[d1]]==100 && random(2)
		    && inside(mx[b]+dx[d1],my[b]+dy[d1])) md[b]=d1;

		x1=mx[b]+dx[md[b]];
		y1=my[b]+dy[md[b]];
		mon[mx[b]][my[b]]=0;
		map[mx[b]][my[b]]=100;
		puttext(mx[b],my[b],mx[b],my[b],&var[b][2]);

		p=map[x1][y1];
		o=mon[x1][y1];

		if (inside(x1,y1) && o<=0 && p==100) {mx[b]=x1; my[b]=y1;}
		else md[b]++; if (md[b]>4) md[b]-=4;
		gettext(mx[b],my[b],mx[b],my[b],&var[b][2]);
	}
	int ch=''; if (md[b]==2 || md[b]==4) ch='';
	text (mx[b],my[b],7,0,ch);
	mon[mx[b]][my[b]]=b;
	map[mx[b]][my[b]]=0;

	if (!bd[b]){
		bd[b]=md[b]+random(2)*2+1; if (bd[b]>4) bd[b]-=4;
		bx[b]=mx[b]; by[b]=my[b];
		var[b][3]=5;
	}

	if (bd[b]){
		var[b][3]--;
		if (bx[b]!=mx[b] || by[b]!=my[b]) text(bx[b],by[b],8,2,' ');
		x1=bx[b]+dx[bd[b]];
		y1=by[b]+dy[bd[b]];
		if (map[bx[b]][by[b]]<100) map[bx[b]][by[b]]=0;
		o=mon[x1][y1];
		if (bullethrough(map[x1][y1]) && var[b][3]){
			bx[b]=x1;  by[b]=y1;
			map[x1][y1]=51;
			text(bx[b],by[b],0,2,'ú');
			if (o>0) {mdead[o]=1; bd[b]=0;}
			if (o==-1) {you_die(8); bd[b]=0;}
		}
		else bd[b]=0;
	}
}


void super_zoom(int b){//SUPER ZOOM
	if (mdead[b]) {die(b,30);  return;}
	if (!random(6)) md[b]=random(4)+1;
	int a=0,speed=1;
	if (mx[b]==x) {speed=3;  if (my[b]<y) md[b]=3; else md[b]=1;}
	if (my[b]==y) {speed=3;  if (mx[b]<x) md[b]=2; else md[b]=4;}

	for (a=1;a<=speed;a++){

		x1=mx[b]+3*dx[md[b]];
		y1=my[b]+3*dy[md[b]];
		p=map[x1][y1];
		if (p==50 || p==51) {md[b]+=random(2)*2-1; a=4;}

		x1=mx[b]+dx[md[b]];
		y1=my[b]+dy[md[b]];
		mon[mx[b]][my[b]]=0;
		text(mx[b],my[b],6,2,' ');
		p=map[x1][y1];
		o=mon[x1][y1];
		if (p<100 && o<=0) {mx[b]=x1; my[b]=y1;}
		else md[b]=random(4)+1;
		if (p==50) {mdead[b]=2; die(b,30); destbul(); return;}
		if (o==-1) a=speed;
		text(mx[b],my[b],5,2,'Z');
	}
	map[mx[b]][my[b]]=0;
	mon[mx[b]][my[b]]=b;
}


void syko_fish(int b){//SYKO FISH
	int co=9;
    if (var[b][2]) var[b][2]--;
	if (mdead[b] && !var[b][2]){
		if (var[b][1]) {die(b,40); return;}
		var[b][1]=1;
		if (mdead[b]==2) destbul();
		co=14;
		mdead[b]=0;
		var[b][2]=2;
	}

	md[b]=random(4)+1;
	for(int a=0;a<=var[b][1];a++){
		x1=mx[b]+dx[md[b]];
		y1=my[b]+dy[md[b]];
		p=map[x1][y1];
		o=mon[x1][y1];
		mon[mx[b]][my[b]]=0;
		text(mx[b],my[b],1,2,' ');
		if (p<100 && o<=0) {mx[b]=x1;my[b]=y1;}
		if (p==50) {mdead[b]=2; die(b,40); destbul(); return;}
		if (o==-1) a=2;
		text(mx[b],my[b],co,2,'à');
	}
	map[mx[b]][my[b]]=0;
	mon[mx[b]][my[b]]=b;
}


void ninja(int b){//NINJA
	if (mdead[b]){
		if (bd[b]){
			map[bx[b]][by[b]]=0;
			text(bx[b],by[b],0,2,' ');}
		if (var[b][2]){
			text(var[b][3],var[b][4],0,2,' ');}
		die(b,60); return;
	}

	if (!random(3)){
		md[b]=random(5);
		if (random(2)){
			if (random(2)) {if (x<mx[b]) md[b]=4; else md[b]=2;}
			else {if (y<my[b]) md[b]=1; else md[b]=3;}
	}   }
	if (var[b][2]) md[b]=0;

	x1=mx[b]+dx[md[b]];
	y1=my[b]+dy[md[b]];
	p=map[x1][y1];
	o=mon[x1][y1];
	mon[mx[b]][my[b]]=0;
	text(mx[b],my[b],1,2,' ');
	if (p<100 && o<=0) {mx[b]=x1; my[b]=y1;}
	if (p==102) if (push(x1,y1,md[b])) {mx[b]=x1; my[b]=y1;}

	text(mx[b],my[b],0,2,'&');
	map[mx[b]][my[b]]=0;
	mon[mx[b]][my[b]]=b;

	if (!var[b][2]){
		int tru=0;
		for(x1=mx[b]-1;x1<=mx[b]+1;x1++) for(y1=my[b]-1;y1<=my[b]+1;y1++){
			if (mon[x1][y1] && mon[x1][y1]!=b) tru=1;
		}
		if (!random(30)) tru=1;
		if (tru) {var[b][2]=random(8)+1; var[b][6]=var[b][2];}
	}
	else{
		int ch;
		x1=mx[b]; y1=my[b];
		switch (var[b][2]){
		case 1: x1--; y1--; ch='\\'; break;
		case 2:       y1--; ch='³'; break;
		case 3: x1++; y1--; ch='/'; break;
		case 4: x1++;       ch='Ä'; break;
		case 5: x1++; y1++; ch='\\'; break;
		case 6:       y1++; ch='³'; break;
		case 7: x1--; y1++; ch='/'; break;
		case 8: x1--;       ch='Ä'; break;
		case 9: x1--; y1--; ch='\\'; break;
		}

		if (var[b][3]) text(var[b][3],var[b][4],0,2,' ');
		if (inside(x1,y1)){
			var[b][3]=x1; var[b][4]=y1;
			text(x1,y1,8,2,ch);
			p=map[x1][y1];
			o=mon[x1][y1];
			map[x1][y1]=0;
			if (p==50) buld=0;
			if (o==-1) you_die(9);
			if (o>0) mdead[o]=3;
		}
		var[b][2]++;
		if (var[b][2]>8) var[b][2]=1;
		if (var[b][2]==var[b][6]){
			text(var[b][3],var[b][4],0,2,' ');
			var[b][2]=0; var[b][3]=0;
		}
	}


	if (!bd[b]){
		int tru=0;
		if (!random(10)){
			tru=1;
			do {bd[b]=random(4)+1;
			} while(bd[b]==md[b]);
		}
		if (x==mx[b]) {tru=1; if (y<my[b]) bd[b]=1; else bd[b]=3;}
		if (y==my[b]) {tru=1; if (x<mx[b]) bd[b]=4; else bd[b]=2;}
		if (tru){
			bx[b]=mx[b]; by[b]=my[b];
			var[b][1]=4+random(10);
	}   }

	if (bd[b]){
		var[b][1]--;
		if (bx[b]!=mx[b] || by[b]!=my[b]) text(bx[b],by[b],8,2,' ');
		x1=bx[b]+dx[bd[b]];
		y1=by[b]+dy[bd[b]];
		if (map[bx[b]][by[b]]<100) map[bx[b]][by[b]]=0;
		o=mon[x1][y1];
		if (bullethrough(map[x1][y1]) && var[b][1]){
			bx[b]=x1;  by[b]=y1;
			map[x1][y1]=51;
			text(bx[b],by[b],7,2,'*');
			if (o>0) {mdead[o]=1;}
			if (o==-1) {you_die(10);}
		}
		else bd[b]=0;
	}
}


void super_rod(int b){//SUPER ROD
	if (mdead[b]) {die(b,80);  return;}

	int c='Ä';
		switch (var[b][1]){
			case 1: c='\\'; break;
			case 2: c='³'; break;
			case 3: c='/'; break;
		}
	for (int a=0;a<=1;a++){
		int r=random(2)+1;
		if (y==my[b] || x==mx[b]) r=0;
		if (x==mx[b] || r==1) {if (y<my[b]) md[b]=1; else md[b]=3;}
		if (y==my[b] || r==2) {if (x<mx[b]) md[b]=4; else md[b]=2;}
		x1=mx[b]+dx[md[b]];
		y1=my[b]+dy[md[b]];
		p=map[x1][y1];
		if (p>=50 && p<100) if (random(2))
			 {md[b]++; if (md[b]>4) md[b]=1;}
		else {md[b]--; if (md[b]<1) md[b]=4;}

		x1=mx[b]+dx[md[b]];
		y1=my[b]+dy[md[b]];
		mon[mx[b]][my[b]]=0;
		text(mx[b],my[b],15,2,' ');

		p=map[x1][y1];
		o=mon[x1][y1];
		if (p<100 && o<=0) {mx[b]=x1;  my[b]=y1;}
		if (p==50) {mdead[b]=2; die(b,80); destbul(); return;}
		if (o==-1) a=2;

		text(mx[b],my[b],11,2,c);
	}
	var[b][1]++; if (var[b][1]>3) var[b][1]=0;
	mon[mx[b]][my[b]]=b;
	map[mx[b]][my[b]]=0;
}


void F16(int b){//F-16
	if (mdead[b]) {
		x1=mx[b]+2*dx[md[b]];
		y1=my[b]+2*dy[md[b]];
		if (inside(x1,y1)) {text(x1,y1,0,2,' ');}
		die(b,100); return;
	}

	if (init[b]){
		init[b]=0;
		switch (md[b]){
			case 1: mx[b]=rnd(3,maxx-2); my[b]=maxy-1;
					var[b][2]=''; break;
			case 2: mx[b]=2; my[b]=rnd(4,maxy-2);
					var[b][2]=''; break;
			case 3: mx[b]=rnd(3,maxx-2); my[b]=2;
					var[b][2]=''; break;
			case 4: mx[b]=maxx-1; my[b]=rnd(4,maxy-2);
					var[b][2]=''; break;
		}
		gettext(mx[b],my[b],mx[b],my[b],&var[b][1]);
		message ("*Closing on ground targets.*",7);
	}

	for (int a=0;a<=1;a++){
		mon[mx[b]][my[b]]=0;
		puttext (mx[b],my[b],mx[b],my[b],&var[b][1]);
		mx[b]+=dx[md[b]];
		my[b]+=dy[md[b]];
		if (!inside(mx[b],my[b])) {mtype[b]=0; return;}
		p=map[mx[b]][my[b]];
		if (p==50) {mdead[b]=2; die(b,100); destbul(); return;}
		if (mon[mx[b]][my[b]] || p==0 || p==50 || p==51) text(mx[b],my[b],0,2,' ');
		gettext (mx[b],my[b],mx[b],my[b],&var[b][1]);
		text (mx[b],my[b],8,2,var[b][2]);

		x1=mx[b]+2*dx[md[b]];
		y1=my[b]+2*dy[md[b]];
		if (inside(x1,y1) && var[b][3]) {var[b][3]=0; text(x1,y1,0,2,' ');}
		x1+=dx[md[b]]; y1+=dy[md[b]];
		if (inside(x1,y1)){
			o=mon[x1][y1];
			p=map[x1][y1];
			if (p<100 || p==101 || p==103 || p==104){
				int co=0; int r=random(3);
				if (r==2) co=4;
				if (r==3) co=8;
				if (md[b]==2 || md[b]==4) text(x1,y1,co,2,':');
				else text(x1,y1,co,2,34);
				map[x1][y1]=0;
				var[b][3]=1;
			}
			if (o==-1) you_die(11);
			if (o>0) {mdead[o]=3; message ("*Shot one! down in flames.*",15);}
		}
	}
	mon[mx[b]][my[b]]=b;
}


void zombie(int b){//ZOMBIE
	if (mdead[b]) {
		var[b][1]--;
		if (mdead[b]==2 && (weapon==5 || weapon==6)) var[b][1]-=2;
		if (var[b][1]<=0) {die(b,24);  return;}
		mdead[b]=0;
	}

	if (init[b]) {var[b][1]=3;  init[b]=0;}

	int r=15;
	if (abs(x-mx[b])<7 && abs(y-my[b])<7) r=30;
	if (abs(x-mx[b])<3 && abs(y-my[b])<3) r=2;
	if (!random(r)){
		r=random(2)+1;
		if (y==my[b] || x==mx[b]) r=0;
		if (x==mx[b] || r==1) {if (y<my[b]) md[b]=1; else md[b]=3;}
		if (y==my[b] || r==2) {if (x<mx[b]) md[b]=4; else md[b]=2;}
		x1=mx[b]+dx[md[b]];
		y1=my[b]+dy[md[b]];
		mon[mx[b]][my[b]]=0;
		p=map[x1][y1];
		o=mon[x1][y1];
		text(mx[b],my[b],0,2,' ');
		if ((p<100 || p==101) && o<=0) {mx[b]=x1; my[b]=y1;}
	}
	text(mx[b],my[b],8,2,'x');
	map[mx[b]][my[b]]=0;
	mon[mx[b]][my[b]]=b;
}


void zookeeper(int b){//ZOOKEEPER
	if (mdead[b]) {
		var[b][1]--;
        if (mdead[b]==2 && (weapon==5 || weapon==6)) var[b][1]-=2;
		if (var[b][1]<=0) {
			if (mdead[b]==2){
				cashola+=300; keepscore();
				killed[23]++;}
			mtype[b]=0;
			for (x1=mx[b]-1;x1<=mx[b]+1;x1++) for (y1=my[b]-1;y1<=my[b]+1;y1++){
				map[x1][y1]=0;
				mon[x1][y1]=0;
				text(x1,y1,8,2,'x');
			}
			return;
		}
		mdead[b]=0;
	}

	if (init[b]) {
		var[b][1]=rnd(9,20);  init[b]=0;
		if (mx[b]<3) mx[b]=3;
		if (my[b]<4) my[b]=4;
		if (mx[b]>maxx-2) mx[b]=maxx-2;
		if (my[b]>maxy-2) my[b]=maxy-2;
	}

	if (!random(3)){
		int r=random(2)+1;
		if (y==my[b] || x==mx[b]) r=0;
		if (x==mx[b] || r==1) {if (y<my[b]) md[b]=1; else md[b]=3;}
		if (y==my[b] || r==2) {if (x<mx[b]) md[b]=4; else md[b]=2;}
		if (!random(6)) md[b]=random(5);
		x1=mx[b]+dx[md[b]];
		y1=my[b]+dy[md[b]];

		for(int x2=mx[b]-1;x2<=mx[b]+1;x2++) for(int y2=my[b]-1;y2<=my[b]+1;y2++){
			text(x2,y2,15,2,' ');
			mon[x2][y2]=0;
		}

		if (x1>2 && y1>3 && x1<maxx-1 && y1<maxy-1) {mx[b]=x1;  my[b]=y1;}
	}
	textcolor(8); textbackground(2);
	gotoxy(mx[b]-1,my[b]-1);
		cputs("Õ ¸");
	gotoxy(mx[b]-1,my[b]);
		cputs("¾ Ô");
	gotoxy(mx[b]-1,my[b]+1);
	textcolor(0);
		cputs("ÞßÝ");
	text(mx[b],my[b],8,0,'ß');
	text(mx[b],my[b]-1,0,4,'§');

	for(int x2=mx[b]-1;x2<=mx[b]+1;x2++) for(int y2=my[b]-1;y2<=my[b]+1;y2++){
		o=mon[x2][y2];
		if (o>0 && o!=b) mdead[o]=3;
		map[x2][y2]=0;
		mon[x2][y2]=b;
	}
}


void wurm(int b){//WURM
	if (mdead[b]) {die(b,66);  return;}

	if (init[b]){
		for (int a=0;a<=10;a+=2){
			var[b][a]=mx[b];
			var[b][a+1]=my[b];
		}
		init[b]=0;
	}

	if (!random(10)) md[b]=random(4)+1;
	bd[b]++; if (bd[b]>5) bd[b]=0;

	int d=md[b];
	if (bd[b]==2) d--;
	if (bd[b]==5) d++;
	if (d<1) d=4;
	if (d>4) d=1;

	x1=mx[b]+dx[d];
	y1=my[b]+dy[d];

	mon[mx[b]][my[b]]=0;
	p=map[x1][y1];
	o=mon[x1][y1];
	text(mx[b],my[b],0,2,' ');
	if ((p<100 || p==103 || p==105) && o<=0){
		text(var[b][10],var[b][11],0,2,' ');
		map[var[b][10]][var[b][11]]=0;
		for (int a=10;a>=2;a-=2){
			var[b][a]=var[b][a-2];
			var[b][a+1]=var[b][a-1];
		}
		var[b][0]=mx[b];
		var[b][1]=my[b];
		mx[b]=x1;  my[b]=y1;
	}
	else{
		int d1=d+1,d2=d+3;
		if (d1>4) d1-=4;
		if (d2>4) d2-=4;
		p=map[ mx[b]+dx[d1] ][ my[b]+dy[d1] ];
		if (p<100 || p==103 || p==105) md[b]=d1; else md[b]=d2;
	}

	int t=0;
	for (int a=1;a<=4;a++){
		x1=mx[b]+dx[a]; y1=my[b]+dy[a];
		p=map[x1][y1];
		if (p>=100 && p!=103 && p!=105 || mon[x1][y1]>0) t++;}
	if (t==4 && !random(3)){
		do{
			mx[b]=rnd(2,maxx-1);
			my[b]=rnd(3,maxy-1);
		} while(map[mx[b]][my[b]]!=0 || abs(mx[b]-x)<6 && abs(my[b]-y)<6);
	}

	for (int a=0;a<=8;a+=2){
		text(var[b][a],var[b][a+1],4+a,2,'');
		map[var[b][a]][var[b][a+1]]=100;
	}
	text(var[b][10],var[b][11],8+random(8),2,'');
	map[var[b][10]][var[b][11]]=100;
	text(mx[b],my[b],5,2,'');
	map[mx[b]][my[b]]=0;
	mon[mx[b]][my[b]]=b;

	for (x1=var[b][10]-1;x1<=var[b][10]+1;x1++)
	for (y1=var[b][11]-1;y1<=var[b][11]+1;y1++){
		o=mon[x1][y1];
		if (o && o!=b) text(x1,y1,15,2,'X');
		if (o==-1) you_die(18);
		if (o>0){
			p=mtype[o];
			if (p!=24 && p!=20 && p!=14 && p!=5 && p!=16 && p!=4) mdead[o]=1;
		}
	}
}


void doppleganger(int b){//DOPPLEGŽNGER
	int bar=0,clos=0,a,d,now,turn,r;

	if (mdead[b] && var[b][0]==7) return;

	if (init[b]) {init[b]=0; var[b][0]=1;}
	now=var[b][0];
	turn=now;

	for(a=1;a<=4;a++) for (d=1;d<=4;d++){
		p=map[mx[b]+d*dx[a]][my[b]+d*dy[a]];
		if (p==50 || p==51) bar=1;
	}

	if (abs(mx[b]-x)<5 && abs(my[b]-y)<5) clos=1;

	if (clos && bar)   turn=7;
	if (!clos && bar)  turn=14;
	if (clos && !bar && now!=2)  turn=5;
	if (!clos && !bar){
		r=random(100);
		if (r==0) turn=1;
		if (r==1) turn=13;
		if (r==2) turn=12;
		if (mx[b]==x || my[b]==y) turn=2;
	}

	if (now==13 && bd[b]) turn=13;
	if (random(2)) var[b][0]=turn;

}



void die(int b,int val){//***DIE***
	if (mdead[b]==2) {
		destbul();
		if (mtype[b]==25) cashola+=40; else cashola+=val;
		keepscore();
		killed[mtype[b]]++;
	}
	p=map[mx[b]][my[b]];
	if (p!=104 && p!=4){
		text(mx[b],my[b],8,2,'x');
		map[mx[b]][my[b]]=0;
		if (mtype[b]==3 && random(3))
			{text(mx[b],my[b],8,2,'­');  map[mx[b]][my[b]]=9;}
		if (mtype[b]==19 && random(2))
			{text(mx[b],my[b],15,2,'*'); map[mx[b]][my[b]]=10;}
		if (mtype[b]==15)
			{text(mx[b],my[b],1,2,'ö');  map[mx[b]][my[b]]=11;}
		if (mtype[b]==11)
        	{text(mx[b],my[b],14,2,'?'); map[mx[b]][my[b]]=7;}
	}
	mtype[b]=0;
	mon[mx[b]][my[b]]=0;
}
