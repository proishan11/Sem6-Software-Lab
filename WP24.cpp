#include<iostream>
#include<pthread.h>
#include<stdlib.h>
#include<vector>
#include<unistd.h>

using namespace std;

struct params {
    int* a;
    int start;
    int end;
    int mid;
    int level;
    int index;
};

void merge(struct params left, struct params right) {
    //sleep(2);
    int *a = left.a;
    int p = left.start;
    int mid = left.end;
    int q = right.end;

    int n1 = mid-p+1;
    int n2 = q-mid;

    int left_a[n1];
    int right_a[n2];

    for(int i=0; i<n1; ++i)
        left_a[i] = a[p + i];

    for(int i=0; i<n2; ++i)
        right_a[i] = a[mid+i+1];

    int k = p, i = 0, j = 0;

    while(i<n1 && j<n2)
        if(left_a[i] <= right_a[j])
            a[k++] = left_a[i++];
        else
            a[k++] = right_a[j++];

    while(i<n1)
        a[k++] = left_a[i++];
    
    while(j<n2)
        a[k++] = right_a[j++];
}

void *merge_sort(void *p) {
    struct params *par = (params*)p;
    
    sleep(2);
    
    cout<<"Level of thread "<<par->level<<" ";
    cout<<"Thread no "<<par->index<<endl;
    //cout<<"Left thread id "<<left_thread<<endl;
    //cout<<"Right thread id "<<right_thread<<endl;

    cout<<par->start<<"  "<<par->end<<endl;
    
    if(par->start < par->end) {
        
        par->mid = (par->start+ par->end)/2;
        
        struct params left = {.a = par->a, .start = par->start, .end = par->mid, .mid=0, .level=par->level+1, .index=2*par->level+1};
        struct params right = {.a = par->a, .start = par->mid+1, .end = par->end, .mid=0, .level=par->level+1, .index=2*par->level+2};
        
        pthread_t left_thread, right_thread;

        pthread_create(&left_thread, NULL, merge_sort, &left);
        pthread_create(&right_thread, NULL, merge_sort, &right );
        
        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);
        
        merge(left, right);
    }
    else {
        pthread_exit(NULL);
    }

    return NULL;
}

int main() {
    int n;
    cout<<"Enter no of integers\n";
    cin>>n;
    cout<<"Enter the values\n";
    int a[n];

    for(int i=0; i<n; ++i)
        // cin>>a[i];
        a[i] = rand() % 1000;

    struct params p = {.a = a, .start=0, .end=n-1, .mid=0, .level=0, .index=0};

    merge_sort(&p);

    cout<<"Sorted array is \n";
    for(int i=0; i<n; ++i)
        cout<<a[i]<<" ";
    cout<<endl;
}