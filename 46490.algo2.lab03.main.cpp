#include <iostream>
#include <time.h>
struct stored_data
{
	int int_data;
	char char_data;

	void generate_data()
	{
		const char letters[] = "abcdefghijklmnopqrstuvwxyz";
		this->int_data = rand() % 10000;
		this->char_data = letters[rand() % (sizeof(letters) - 1)];

	}
	friend std::ostream& operator<<(std::ostream& os, const stored_data& sd)
	{
		os  << sd.int_data << " " << sd.char_data << "\n";
		return os;
	}
	friend bool operator==(const stored_data &st, const stored_data&sd)
	{
		if (st.int_data == sd.int_data &&st.char_data == sd.char_data)
			return true;
		else
			return false;
	}
	friend bool operator !=(const stored_data& st, const stored_data&sd)
	{
		if (st.int_data == sd.int_data &&st.char_data == sd.char_data)
			return false;
		else
			return true;
	}
	friend bool operator >(const stored_data&  so1, const stored_data& so2)
	{
		int diff = so1.int_data - so2.int_data;
		if (diff > 0)
			return true;
		else
			return false;
	}
};
template<typename T>
struct node
{
	T field;
	node *left;
	node *right;
	node *parent;
	
	int index_node;
	node(T field, size_t size)
	{
		
		this->field = field;
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
		this->index_node = size;
	}

	void set_field(T field)
	{
		this->field = field;
	}
};
template<typename T>
class BST
{
public:
	size_t size = 0;
	node<T> *root;

	bool add(T data)
	{

		node<T> *node_to_add = new node<T>(data, size);

		if (root == NULL)
		{
			this->root = node_to_add;
			size++;
			return true;
		}
		node<T> *temp;
		temp = root;
		while (temp != NULL)
		{

			if (temp->field == node_to_add->field)
			{
				return false;
			}

			if (temp->field > node_to_add->field)
			{
				if (temp->left != NULL)
				{
					temp = temp->left;
				}
				else
				{
					size++;
					temp->left = node_to_add;
					temp->left->parent = temp;
					return true;
				}
			}
			else
			{
				if (temp->right != NULL)
				{
					temp = temp->right;
				}
				else
				{
					size++;
					temp->right = node_to_add;
					temp->right->parent = temp;
					return true;
				}
			}

		}
		return false;
	}
	node<T>*search(T data)
	{
		node<T> *temp;
		temp = root;
		while (temp != NULL)
		{

			if (temp->field == data)
			{
				
				return temp;
			}

			if (temp->field > data)
			{
				if (temp->left != NULL)
				{
					temp = temp->left;
				}
				else
					return NULL;
			}
			else
			{
				if (temp->right != NULL)
				{
					temp = temp->right;
				}
				else
				{
					return NULL;
				}
			}
		}
		return NULL;
	}
	void delete_node(T data)
	{
		
		T data2;
		node<T>*to_delete = search(data);
		
		size--;
		if (to_delete != NULL)
		{
			if (!to_delete->right && !to_delete->left)
			{
				if (to_delete->parent)
				{
					node<T>*temp = to_delete->parent;
					if (temp->left == to_delete) { 
						temp->left =NULL;
						delete to_delete;
					}
					else if (temp->right == to_delete)
					{
						temp->right = NULL;
						delete to_delete;
					}
					

				}
				else if(!to_delete->parent)
				{
					delete to_delete;
					this->root=NULL;
				}
			}
			else if ((to_delete->right == NULL) || (to_delete->left == NULL))
			{
				node<T>*tmp = to_delete->left ? to_delete->left : to_delete->right;
				if (to_delete->parent)
				{
					if (to_delete->parent->left == to_delete)
					{
						to_delete->parent->left = tmp;
						tmp->parent = to_delete->parent;

					}
					else
					{
						to_delete->parent->right = tmp;
						tmp->parent = to_delete->parent;
					}
					delete to_delete;
				}
				else
				{
					tmp->parent = NULL;
					root = tmp;
					delete to_delete;

				}
			}
			else
			{
				node<T>*temp = to_delete->left;
					while (temp->right != NULL)
					{
						temp = temp->right;
					}
					data2 = temp->field;
					to_delete->set_field(data2);
					temp = NULL;
					delete temp;
				

			}
		}

	}

	void BST_clear(node<T>*root)
	{
		if (root != NULL)
		{
			BST_clear(root->left);
			BST_clear(root->right);
			size--;
			delete root;
		}
		this->root = NULL;
	}
	void preorder(node<T>*root)
	{

		if (root == NULL)
		{
			return;
		}
		std::cout << root->field << "\n";
		preorder(root->left);
		preorder(root->right);

	}
	void in_order(node<T>*root)
	{

		if (root == NULL)
		{
			return;
		}
		in_order(root->left);
		std::cout << root->field << "\n";
		in_order(root->right);

	}
	void display_preorder(node<T>*root) 
	{
		if (root == NULL)
		{
			return;
		}
		std::cout << root->index_node << ": [p: ";
		if (root->parent == NULL)
		{
			std::cout << "NULL, ";
		}
		else std::cout << root->parent->index_node << " ";
		if (root->left == NULL)
		{
			std::cout << "l: NULL";
		}
		else std::cout << "l: " << root->left->index_node << " ";
		if (root->right == NULL)
		{
			std::cout << "r: NULL";
		}
		else std::cout << "r: " << root->right->index_node << " ";
		std::cout << "] , data: " << root->field << "\n";


		display_preorder(root->left);

		display_preorder(root->right);
	}
	
	int height(node<T>*root)
	{
		if (root == NULL)
			return 0;
		else
		{
			int left_height = height(root->left);
			int right_height = height(root->right);

			if (left_height > right_height)
				return(left_height + 1);
			else return(right_height + 1);
		}
	}

};
int main()
{
	srand(time(NULL));
	BST<stored_data>*bst= new BST<stored_data>();
	stored_data so[6];
	for (int i = 0; i < 6; i++)
	{
		
		so[i].generate_data();
		bst->add(so[i]);
		
	}
	
	bst->display_preorder(bst->root);
	
	std::cout << "\n";
	
	int height = bst->height(bst->root);
	std::cout << "Wysokosc drzewa: " << height << "\n";
	bst->delete_node(so[5]);
	

	bst->display_preorder(bst->root);
	bst->BST_clear(bst->root);
	
	return(0);
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
