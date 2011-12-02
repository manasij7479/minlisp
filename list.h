/**
 * Singly linked list of strings and their lisp`y evaluation
 */
#ifndef LIST_H
#define LIST_H
#include<string>
#include<vector>

namespace mm
{
	class list
	{
		class node;
	public:
		class iterator
		{
		public:
			iterator operator++(int)
			{
				iterator result = iterator(n);
				n=n->next;
				return result;				
			};
			iterator operator++()
			{
				n=n->next;
				return iterator(n);
			}
			std::string& operator*(){return n->val;};
			bool operator==(iterator it){return n==it.n;};
			bool operator!=(iterator it){return n!=it.n;};
			iterator(node* n_):n(n_){};
			
			friend class list;
		private:
			node* n;			
		};
		iterator begin(){return iterator(begin_sn->next);};
		iterator end(){return iterator(end_->next);};
		
		int size(){return size_val;}
		
		void push_back(std::string s)
		{
			node* new_node = new node(s);
			new_node->next = end_->next;
			end_->next = new_node;
			end_ = new_node;
			size_val++;
		}
		void push_front(std::string s)
		{
			node* new_node = new node(s);
			new_node->next = begin_sn->next;
			begin_sn->next = new_node;
			size_val++;
		}
		iterator insert(const std::string& s,iterator it)//inserts after 'it'
		{
			bool end_flag;
			node* new_node = new node(s);
			node* prev = it.n;
			end_flag = (prev==end_);
			new_node->next = prev->next;
			prev->next = new_node;
			if(end_flag)end_=new_node;
			size_val++;
			return iterator(new_node);
		}
// 		void remove(iterator it)
// 		{
// 			node* n = it.n;
// 			n->val = n->next->val;
// 			bool end_flag=(n==end_);
// 			node* temp = n->next->next;
// 			delete(n->next);
// 			n->next = temp;			
// 			if(end_flag)
// 			{
// 				n->next = nullptr;n->sentinel=true;
// 				//Have to set end_ here...which would be before n
// 			}
// 			size_val++;
// 		}
		std::string eval();
		std::string car();//Returns the first element
		list cdr(); //Returns a list containing the last (size-1) elements.
		
		list(const std::string&);
		list(const std::vector<std::string>&);
		list():size_val(0)
		{
			begin_sn = new node();
			end_ = begin_sn;
			end_->next=new node();
		}
	private: 
		class node
		{
		public:
			node* next;
			bool sentinel;
			std::string val;
			node(std::string val_,node* next_=nullptr):next(next_),sentinel(false),val(val_){};
			node():next(nullptr),sentinel(true){};
		};
		node* begin_sn;//Sentinel node at the beginning
		node* end_;//Node before the end sentinel
		int size_val;

		list(node* b_sn,node* e_,int s_val):begin_sn(b_sn),end_(e_),size_val(s_val){};
		//^Only for special friends !
	};
}
#endif // LIST_H
