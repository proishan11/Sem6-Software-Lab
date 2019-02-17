#include<semaphore.h>
#include<iostream>
#include<unistd.h>

using namespace std;

struct spoon {
    int id;
    sem_t sem;

    spoon(int id) {
        this->id = id;
        if(sem_init(&sem, 0, 1) < 0) {
            throw "Error Initializing chopstick " + id;
        }
    }
};

class Philosopher {
private:
    int id;
    spoon *left;
    spoon *right;

public:
    Philosopher(int id) {
        this->id = id;
    }

    int pick_left(spoon *l) {
        int canPick = sem_trywait(&(l->sem));
        //cout<<"CanPick left = "<<canPick<<endl;
        if(!canPick) {
            this->left = l;
            cout<<"Philosopher "<<id<<" picked spoon "<<l->id<<endl; 
        }
        else {
            cout<<"Philosopher "<<id<<" can't pick spoon "<<left->id<<endl;
        }
        return canPick;
    }

    int pick_right(spoon* r) {
        
        int canPick = sem_trywait(&(r->sem));
        //cout<<"CanPick right = "<<canPick<<endl;
        if(!canPick) {
            this->right = r;
            cout<<"Philosopher "<<id<<" picked spoon "<<right->id<<endl; 
        }else 
            cout<<"Philosopher "<<id<<" can't pick spoon "<<left->id<<endl;
        return canPick;
    }

    int put_left() {
        cout<<"Philosopher "<<id<<" put down spoon "<<left->id<<endl;
        //left = NULL;
        return sem_post(&(left->sem));
    }

    int put_right() {
        cout<<"Philosopher "<<id<<" put down spoon "<<right->id<<endl;
        //right = NULL;
        return sem_post(&(right->sem));
    }

    void eat() {
        cout<<" Philosopher "<< id <<" is eating \n";
        usleep(10000);
    }
};

int initialize_forks() {
    int id;
    for(id = 0; id<4; ++id) {
        int pid = fork();
        if(!pid) break;
    }
    //cout<<"id = "<< id<<endl;
    return id;
}

int main() {
    int no_of_spoons = 3;
    //sem_t s;
    //int ret = sem_init(&s, 1, 1);
    //cout<<ret<<endl;

    spoon* cup_a[3];
    spoon* cup_b[3];

    for(int i=0; i<3; ++i)
        cup_a[i] = new spoon(i+1);

    for(int i=0; i<3; ++i)
        cup_b[i] = new spoon(i+4);

    int x = initialize_forks();

    cout<<"x = "<<x<<endl;
    Philosopher philosopher(x+1);
    
    

    for(int i=0; i<10; ++i) {
        //cout<<"HEre jajajs\n";
        for(int j=0; j<no_of_spoons; ++j) 
            if(!philosopher.pick_left(cup_a[j]))
                break;

        for(int j=0; j<no_of_spoons; ++j)
            if(!philosopher.pick_right(cup_b[j]))
                break;

        cout<<"Inside critical section\n";

        philosopher.eat();
        
        philosopher.put_left();
        philosopher.put_right();
    
    }


    // spoon *sp = new spoon(1);
    // int value;
    // sem_getvalue(&(sp->sem), &value);
    // cout<<value<<endl;
    // sem_wait(&(sp->sem));
    // sem_getvalue(&(sp->sem), &value);
    // cout<<value<<endl;
}