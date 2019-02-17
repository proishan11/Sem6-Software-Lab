#include<semaphore.h>
#include<iostream>
#include<sys/mman.h>
#include<unistd.h>
using namespace std;

struct spoon {
    int id;
    sem_t *sem;
    spoon(int id) {
        this->id = id;
        sem = (sem_t*) mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);

        if(sem_init(sem, 1, 1) < 0)
            cout<<"Error initializing chopstick "<<id<<endl;
    }
};

spoon* A[3];
spoon* B[3];

class Philosopher {
private:
    int id;
    spoon *left, *right;

public:
    Philosopher(int id) {
        this->id = id;
    }

    int get_id() {
    	return id;
    }

    int pick_left(spoon* l) {
        int canPick = sem_trywait(l->sem);
        if(canPick == 0) {
            left = l;
            cout<<"Philosopher "<<id<<" picked spoon "<<l->id<<endl;
        }
        return canPick;
    }

    int pick_right(spoon* r) {
        int canPick = sem_trywait(r->sem);
        if(canPick == 0) {
            right = r;
            cout<<"Philosopher "<<id<<" picked spoon "<<r->id<<endl;
        }
        return canPick;
    }

    int put_left() {
        cout<<"Philosopher "<<id<<" put down spoon "<<left->id<<endl;
        sem_post(left->sem);
    }

    int put_right() {
        cout<<"Philosopher "<<id<<" put down spoon "<<right->id<<endl;
        sem_post(right->sem);
    }

    void eat() {
        cout<<"Philosopher "<<id<<" eating "<<endl;
    }
};

int main() {
    for(int i=0; i<3; ++i)
        A[i] = new spoon(i+1);
    for(int i=0; i<3; ++i)
        B[i] = new spoon(i+4);

    int x;
    for(x=0; x<4; ++x) {
        int pid = fork();
        if(pid == 0)  {
        	break;
        }
    }



    Philosopher p(x+1);

    for(int i=0; i<10; ++i) {
        for(int i=0; i<3; ++i)
            if(p.pick_left(A[i]) == 0)
                break;

        for(int i=0; i<3; ++i)
            if(p.pick_right(B[i]) == 0)
                break;
        
        p.eat();
        p.put_left();
        p.put_right();
        cout<<"Philosopher "<<p.get_id()<<" is thinking\n";
    }
}
