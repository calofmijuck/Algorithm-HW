#ifndef HW2
#define HW2

void init() { // initialize

}

int os_insert(int x) { // insert x
    return -1;
}

int os_delete(int x) { // delete x
    return -1;
}

int os_select(int i) { // select i-th element
    return -1;
}

int os_rank(int x) { // rank of element with key x
	return -1;
}

bool check(int opt_seq[], int in_seq[], int out_seq[], int n){
    init();
    for(int i = 0; i < n; ++i) {
		if(opt_seq[i] == 0) {
            if(os_insert(in_seq[i]) != out_seq[i]) {
                return false;
            }
        } else if(opt_seq[i] == 1) {
            if(os_delete(in_seq[i]) != out_seq[i]) {
                return false;
            }
        } else if(opt_seq[i] == 2) {
            if(os_select(in_seq[i]) != out_seq[i]) {
                return false;
            }
        } else if(opt_seq[i] == 3) {
            if(os_rank(in_seq[i]) != out_seq[i]) {
                return false;
            }
        }
    }
    return true;
}

#endif
