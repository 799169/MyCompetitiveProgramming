#include <cstdio>
#include <cstdlib>

int N,K,dx,dy;
char moves[100008];
typedef struct {
	long long vx;
	long long vy;
	long long minv;
	long long maxv;
}list_structure;
list_structure lists_temp[100008];
int lists_temp_len=0;
list_structure lists[100008];
int lists_len=1;
void list_add(list_structure *ls,long long sx,long long sy,long long mnv,long long mxv) {
	ls->vx=sx;
	ls->vy=sy;
	ls->minv=mnv;
	ls->maxv=mxv;
}
void add_point(long long sx,long long sy,long long mnv,long long mxv) {
	//mod dx �Ő������ꏊ���Z�o���C���̏ꏊ�ɓ_��ǉ��D
	if(dx==0) {
		list_add(&lists_temp[lists_temp_len],sx,sy,mnv,mxv);
		lists_temp_len++;
	} else {
		if(sx>=dx) {
			long long temp=sx/dx;
			add_point(sx-temp*dx,sy-temp*dy,mnv+temp,mxv+temp);
			return;
		}
		if(sx<0) {
			long long temp=-sx/dx+1;
			add_point(sx+temp*dx,sy+temp*dy,mnv-temp,mxv-temp);
			return;
		}
		list_add(&lists_temp[lists_temp_len],sx,sy,mnv,mxv);
		lists_temp_len++;
	}
}
int comp(const void *ka,const void *kb) {
	list_structure *a = (list_structure *)ka;
	list_structure *b = (list_structure *)kb;
	if(a->vx != b->vx) {
		if(a->vx < b->vx) return -1;
		return 1;
	}
	if(a->vy != b->vy) {
		if(a->vy < b->vy) return -1;
		return 1;
	}
	if(a->minv != b->minv) {
		if(a->minv < b->minv) return -1;
		return 1;
	}
	if(a->maxv < b->maxv) return -1;
	if(a->maxv > b->maxv) return 1;
	return 0;
}
int comp_xy(const void *ka,const void *kb) {
	list_structure *a = (list_structure *)ka;
	list_structure *b = (list_structure *)kb;
	if(a->vx != b->vx) {
		if(a->vx < b->vx) return -1;
		return 1;
	}
	if(a->vy != b->vy) {
		if(a->vy < b->vy) return -1;
		return 1;
	}
	return 0;
}
int findl(long long sx,long long sy) {
	//(sx,sy) �ɑ��������Ԃ����X�g�ɂ���΂��̏ꏊ���A�Ȃ��Ȃ� -1 ��Ԃ��D
	//��������Ȃ炻���̈�ԍ��̏ꏊ��Ԃ��D
	int minr=0; int maxr=lists_len-1;
	list_structure temp; temp.vx=sx; temp.vy=sy;
	while(minr<maxr) {
		int hf=(minr+maxr)/2;
		if(comp_xy(&lists[hf],&temp)<0) {
			minr=hf+1;
		} else {
			maxr=hf;
		}
	}
	if(lists[minr].vx!=sx||lists[minr].vy!=sy) return -1;
	return minr;
}
int findr(long long sx,long long sy) {
	//(sx,sy) �ɑ��������Ԃ����X�g�ɂ���΂��̏ꏊ��Ԃ��D
	//��������Ȃ炻���̈�ԉE�̏ꏊ��Ԃ��D
	int minr=0; int maxr=lists_len-1;
	list_structure temp; temp.vx=sx; temp.vy=sy;
	while(minr<maxr) {
		int hf=(minr+maxr+1)/2;
		if(comp_xy(&lists[hf],&temp)>0) {
			maxr=hf-1;
		} else {
			minr=hf;
		}
	}
	return minr;
}
int exist(long long vx,long long vy) {
	//(vx,vy) �ɑ�������ꏊ�� 1 �ȏ��Ԃ����邩����D
	if(dx==0) {
		if(findl(vx,vy)<0) return 0;
		return 1;
	}
	if(vx<0) {
		long long temp=-vx/dx+1;
		return exist(vx+temp*dx,vy+temp*dy);
	}
	if(vx>=dx) {
		long long temp=vx/dx;
		return exist(vx-temp*dx,vy-temp*dy);
	}
	if(findl(vx,vy)<0) return 0;
	return 1;
}
void calcplace(long long vx,long long vy,int *retl,int *retr,long long *retoffset) {
	//(vx,vy) �ɑ��������Ԃ�\���W�� (retl ���� retr �͈̔͂Ƃ��ĕԂ�) �����߂�D
	//retoffset �ɂ́A���ʕ��������Ƃ��ɕK�v�Ȉړ���ۑ��D
	*retoffset=0;
	if(dx) {
		if(vx<0) {
			*retoffset=-vx/dx+1;
			*retoffset=-(*retoffset);
		}
		if(vx>=dx) {
			*retoffset=vx/dx;
		}
	}
	*retl=findl(vx-(*retoffset)*dx,vy-(*retoffset)*dy);
	*retr=findr(vx-(*retoffset)*dx,vy-(*retoffset)*dy);
}
int range_minv_a[100008];
int range_maxv_a[100008];
int range_minv_b[100008];
int range_maxv_b[100008];
int range_minv_temp[100008];
int range_maxv_temp[100008];
int range_a_len,range_b_len;
void range_cpya(int fl,int fr,long long offset) {
	//range_*_a �ɋ�ԗ���R�s�[
	range_a_len=0;
	for(int i=fl;i<=fr;i++) {
		range_minv_a[range_a_len]=lists[i].minv-offset;
		range_maxv_a[range_a_len]=lists[i].maxv-offset;
		range_a_len++;
	}
}
void range_cpyb(int fl,int fr,long long offset) {
	//range_*_b �ɋ�ԗ���R�s�[
	range_b_len=0;
	for(int i=fl;i<=fr;i++) {
		range_minv_b[range_b_len]=lists[i].minv-offset;
		range_maxv_b[range_b_len]=lists[i].maxv-offset;
		range_b_len++;
	}
}
void merge(void) {
	//2 �̋�ԗ� range_*_a �� range_*_b �̋��ʕ����ƂȂ��ԗ���v�Z���Arange_*_a �ɕۑ��D
	int range_temp_len=0;
	int ia=0; int ib=0;
	while(ia<range_a_len&&ib<range_b_len) {
		if(range_minv_a[ia]<range_minv_b[ib]) {
			range_minv_a[ia]=range_minv_b[ib];
			if(range_minv_a[ia]>range_maxv_a[ia]) ia++;
		} else if(range_minv_a[ia]>range_minv_b[ib]) {
			range_minv_b[ib]=range_minv_a[ia];
			if(range_minv_b[ib]>range_maxv_b[ib]) ib++;
		} else {
			range_minv_temp[range_temp_len]=range_minv_a[ia];
			if(range_maxv_a[ia]>range_maxv_b[ib]) {
				range_maxv_temp[range_temp_len]=range_maxv_b[ib];
				ib++;
			} else {
				range_maxv_temp[range_temp_len]=range_maxv_a[ia];
				ia++;
			}
			range_temp_len++;
		}
	}
	for(int i=0;i<range_temp_len;i++) {
		range_minv_a[i]=range_minv_temp[i];
		range_maxv_a[i]=range_maxv_temp[i];
	}
	range_a_len=range_temp_len;
}
int main() {
	scanf("%d%d",&N,&K);
	scanf("%s",moves);
	for(int i=0;i<N;i++) {
		if(moves[i]=='E') dx++;
		if(moves[i]=='N') dy++;
		if(moves[i]=='W') dx--;
		if(moves[i]=='S') dy--;
	}
	if(dx<0) {
		dx=-dx;
		for(int i=0;i<N;i++) {
			if(moves[i]=='E') {
				moves[i]='W';
			} else if(moves[i]=='W') {
				moves[i]='E';
			}
		}
	}
	if(dy<0) {
		dy=-dy;
		for(int i=0;i<N;i++) {
			if(moves[i]=='N') {
				moves[i]='S';
			} else if(moves[i]=='S') {
				moves[i]='N';
			}
		}
	}
	//���͂� dx>0 �ƂȂ�悤�ɉ�]�C���]������ (dx=dy=0 �̂Ƃ��ȊO)�D
	if(dx==0&&dy>0) {
		int temp=dy;
		dy=dx;
		dx=temp;
		for(int i=0;i<N;i++) {
			if(moves[i]=='E') {
				moves[i]='N';
			} else if(moves[i]=='N') {
				moves[i]='E';
			}
			if(moves[i]=='S') {
				moves[i]='W';
			} else if(moves[i]=='W') {
				moves[i]='S';
			}
		}
	}
	//dx=dy=0 �̂Ƃ��CK=1 �Ƃ��Ă����D
	if(dx==0) K=1;
	add_point(0,0,0,K-1);
	int nx=0; int ny=0;
	for(int i=0;i<N;i++) {
		if(moves[i]=='E') nx++;
		if(moves[i]=='N') ny++;
		if(moves[i]=='W') nx--;
		if(moves[i]=='S') ny--;
		add_point(nx,ny,0,K-1);
	}
	//�Z�o�����e��Ԃ̏d�Ȃ������̓��m�������D
	qsort(lists_temp,lists_temp_len,sizeof(list_structure),comp);
	list_add(&lists[0],lists_temp[0].vx,lists_temp[0].vy,lists_temp[0].minv,lists_temp[0].maxv);
	for(int i=1;i<lists_temp_len;i++) {
		if(lists[lists_len-1].vx!=lists_temp[i].vx||lists[lists_len-1].vy!=lists_temp[i].vy) {
			list_add(&lists[lists_len],lists_temp[i].vx,lists_temp[i].vy,lists_temp[i].minv,lists_temp[i].maxv);
			lists_len++;
		} else {
			if(lists[lists_len-1].maxv+1<lists_temp[i].minv) {
				list_add(&lists[lists_len],lists_temp[i].vx,lists_temp[i].vy,lists_temp[i].minv,lists_temp[i].maxv);
				lists_len++;
			} else {
				if(lists[lists_len-1].maxv<lists_temp[i].maxv) lists[lists_len-1].maxv=lists_temp[i].maxv;
			}
		}
	}
	long long sol=0;
	//�����`�̍������Œ肵���ꍇ�̌����v�Z�D
	for(int i=0;i<lists_len;i++) {
		if(i) if(lists[i].vx==lists[i-1].vx&&lists[i].vy==lists[i-1].vy) continue; //���ɒ��ׂĂ���Ȃ珜�O�D
		int bx=lists[i].vx;
		int by=lists[i].vy;
		if(exist(bx+1,by)+exist(bx,by+1)+exist(bx+1,by+1)==3) {
			int fl,fr;
			long long offset;
			calcplace(bx,by,&fl,&fr,&offset);
			range_cpya(fl,fr,offset);
			calcplace(bx+1,by,&fl,&fr,&offset);
			range_cpyb(fl,fr,offset);
			merge();
			calcplace(bx,by+1,&fl,&fr,&offset);
			range_cpyb(fl,fr,offset);
			merge();
			calcplace(bx+1,by+1,&fl,&fr,&offset);
			range_cpyb(fl,fr,offset);
			merge();
			for(int i=0;i<range_a_len;i++) sol+=range_maxv_a[i]-range_minv_a[i]+1;
		}
	}
	printf("%lld\n",sol);
	return 0;
}
