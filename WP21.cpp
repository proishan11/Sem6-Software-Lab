#include<iostream>
#include<queue>
#include<stack>
using namespace std;

struct node {
	node(int data) {
		this->data = data;
		this->left = NULL;
		this->right = NULL;
	}

	int data;
	struct node* left;
	struct node* right;
};

struct node* createNode(int data) {
	return new node(data);
}

struct node* root = NULL;

void insert(int data) {
	struct node* newNode = createNode(data);

	if(root == NULL) {
		root = newNode;
		return;
	}
	
	queue<node*> q;
	q.push(root);
	
	while(!q.empty()) {
		//cout<<"in loop\n";
		bool flag = true;
		struct node* front = q.front();
		q.pop();
		
		if(front->left != NULL) {
			q.push(front->left);
		}

		if(front->left == NULL) {
			front->left = newNode;
			return;
		}
		
		if(front->right != NULL) {
			q.push(front->right);
		}
		if(front->right == NULL) {
			
			front->right = newNode;
			return;
		}
	}
	cout<<"Inserted\n";
}

void swapData() {
	stack<node*> s;
	queue<node*> q;

	q.push(root);


	while(!q.empty()) {
		struct node* front = q.front();
		s.push(front);
		q.pop();

		if(front->left != NULL)
			q.push(front->left);
		if(front->right != NULL)
			q.push(front->right);

	}

	while(!s.empty()) {
		struct node* front = s.top();
		s.pop();
		struct node* largest = front;
		if(front->left != NULL) {
			if(front->left->data < largest->data) {
				largest = front->left;
			}
		}
		if(front->right != NULL) {
			if(front->right->data < largest->data) {
				largest = front->right;
			}
		}

		int temp = largest->data;
		largest->data = front->data;
		front->data = temp;
	}
}

void inorder(struct node* temp) {
	//cout<<"here\n";
	

	if(temp == NULL) {
		return;
	}
	
	inorder(temp->left);
	cout<<temp->data<<"  ";
	inorder(temp->right);
	
}

void postorder(struct node* temp) {
	if(temp == NULL) {
		//cout<<"end\n";
		return;
	}
	postorder(temp->left);
	postorder(temp->right);
	cout<<temp->data<<" ";
}

int main() {
	int n, data;
	
	cin>>n;
	
	for(int i=0; i<n; ++i) {
		cin>>data;
		insert(data);
	}
	
	cout<<"inorder\n";
	inorder(root);
	cout<<endl;
	cout<<"postorder\n";
	postorder(root);
	swapData();


	cout<<"after  swapping\n";
	inorder(root);

	//cout<<a<<endl;



}