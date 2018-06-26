#include <iostream>
#include <fstream>
#include <string>
#define MAX_DATA_LENGTH 12
using namespace std;
ifstream fin("source.txt"); // �Է½�Ʈ��
ofstream fout("source_output.txt"); // ��½�Ʈ��

struct BST
{
	string name;
	string phone_num;
	BST *right = NULL;
	BST *left = NULL;
};

void BST_Read(BST *node) // ���Ͽ��� �� ���� �� ��忡 ����
{
	fin >> node->name;
	fin >> node->phone_num;
}

void BST_Write(BST *root) // ������ȸ��(��������) �� �ؽ�Ʈ�� ���
{
	if (root)
	{
		BST_Write(root->left);
		fout << root->name << " ";
		fout << root->phone_num << endl;
		BST_Write(root->right);
	}
}

void BST_Print(BST *root) // ������ȸ��(��������) �� ���
{
	if (root)
	{
		BST_Print(root->left);
		cout << "Name : " << root->name << " / " << "Phone number : " << root->phone_num << endl;
		BST_Print(root->right);
	}
}

void BST_Search(BST *root, BST search_node) // ������ȸ(��������) �� �˻�
{
	if (root)
	{
		BST_Search(root->left, search_node);
		if (search_node.name == root->name) {
			cout << "Name : " << root->name << " / " << "Phone number : " << root->phone_num << endl;
		}
		BST_Search(root->right, search_node);
	}
}

void BST_Insert(BST *root, BST **main_root) // Ž�� �� ����(�����Է�)
{
	if ((*main_root) == NULL) {
		(*main_root) = new BST;
		BST_Read(*main_root);
		goto end;
	}
	BST *new_node = new BST;
	BST *current_node = root;
	BST_Read(new_node);
	while (root != NULL) // Ž�� ����
	{
		if ((root->name).compare(new_node->name) > 0) {
			current_node = root;
			root = root->left;
		}
		else if ((root->name).compare(new_node->name) <= 0) {
			current_node = root;
			root = root->right;
		}
	}
	if ((current_node->name).compare(new_node->name) > 0) {
		current_node->left = new_node;
	}
	else if ((current_node->name).compare(new_node->name) <= 0)
		current_node->right = new_node;

end:
	cout << " ";
}

void BST_Insert(BST *root, BST Add_node, BST **main_root) // Ž�� �� ����(�ܼ��Է�) - �Լ������ε�
{
	if ((*main_root) == NULL) {
		(*main_root) = new BST;
		(*main_root)->name = Add_node.name;
		(*main_root)->phone_num = Add_node.phone_num;
		goto end;
	}
	BST *current_node = root;
	BST *new_node = new BST;
	*new_node = Add_node;
	while (root != NULL) // Ž�� ����
	{
		if ((root->name).compare(new_node->name) > 0) {
			current_node = root;
			root = root->left;
		}
		else if ((root->name).compare(new_node->name) <= 0) {
			current_node = root;
			root = root->right;
		}
	}
	if ((current_node->name).compare(new_node->name) > 0) {
		current_node->left = new_node;
	}
	else if ((current_node->name).compare(new_node->name) <= 0)
		current_node->right = new_node;

end:
	cout << " ";
}

void BST_Delete(BST *root, BST search_node, BST **main_root)
{
	BST *parent_node = NULL;
	BST *current_node = NULL;
	BST *delete_node = NULL;
	BST *left_node = NULL;
	BST *left_tail_node = NULL;
	BST *right_node = NULL;
	BST *right_tail_node = NULL;
	parent_node = root;
	current_node = root;
	delete_node = root;

	while (current_node != NULL) // �� ã���� Ʈ�� Ž�� ����
	{
		if ((current_node->name).compare(search_node.name) > 0) { // ã������ ���� ���� ��庸�� ������ ����!
			parent_node = current_node;
			delete_node = current_node;
			current_node = current_node->left;
		}
		else if ((current_node->name).compare(search_node.name) < 0) { // ã������ ���� ���� ��庸�� ũ�� ������!
			parent_node = current_node;
			delete_node = current_node;
			current_node = current_node->right;
		}
		else if ((current_node->name).compare(search_node.name) == 0) { // �ش� �� �߰�! ���� �� ����!
																		// ���⼭���� �ٽ� �Ʒ��� Case 1, 2, 3�Ǻ��� �ؾ��Ѵ�!
																		/*
																		- �����Ȳ
																		current_node = ã������ ���� ����Ű�� ������
																		parent_node = ã������ ���� �θ� ��带 ����Ű�� ������
																		*/
			if (current_node->left == NULL && current_node->right == NULL) { // Case 1 ���� (��������� ����Ʈ�� ����)
				if ((parent_node->name).compare(current_node->name) > 0) { // �θ��庸�� �� ���� ���̸� �θ��� ���� ��������
					parent_node->left = NULL;
					delete_node = current_node;
					current_node = root;
					delete delete_node;
				}
				else if ((parent_node->name).compare(current_node->name) < 0) { // �θ��庸�� �� ū ���̸� �θ��� ������ ��������
					parent_node->right = NULL;
					delete_node = current_node;
					current_node = root;
					delete delete_node;
				}
				else { // ��Ʈ ��尡 ������ ����� ���
					(*main_root) = NULL;
					cout << "- System : Tree is Empty" << endl;
					break;
				}
			}
			else if (current_node->left != NULL && current_node->right == NULL) { // Case 2-1 ���� (���� ����Ʈ�� ����)
				delete_node = current_node;
				current_node = current_node->left; // ���� ���� parent-delete-current ����
				if (delete_node == (*main_root)) { // ���� ����Ʈ���� ���� ��Ʈ ��� ������ �����͸� �Ʒ��� ����
					(*main_root) = current_node;
				}
				else
					delete delete_node;
				if ((parent_node->name).compare(current_node->name) > 0) { // �θ��庸�� �� ���� ���̸� �θ��� ���ʿ� ����
					parent_node->left = current_node;
				}
				else if ((parent_node->name).compare(current_node->name) <= 0) { // �θ��庸�� �� ū ���̸� �θ��� �����ʿ� ����
					parent_node->right = current_node;
				}
			}
			else if (current_node->left == NULL && current_node->right != NULL) { // Case 2-2 ���� (������ ����Ʈ�� ����)
				delete_node = current_node;
				current_node = current_node->right;
				if (delete_node == (*main_root)) { // ���� ����Ʈ���� ���� ��Ʈ ��� ������ �����͸� �Ʒ��� ����
					(*main_root) = current_node;
				}
				else
					delete delete_node;
				if ((parent_node->name).compare(current_node->name) > 0) { // �θ��庸�� �� ���� ���̸� �θ��� ���ʿ� ����
					parent_node->left = current_node;
				}
				else if ((parent_node->name).compare(current_node->name) <= 0) { // �θ��庸�� �� ū ���̸� �θ��� �����ʿ� ����
					parent_node->right = current_node;
				}
			}
			else if (current_node->left != NULL && current_node->right != NULL) { // Case 3 ���� (���� ����Ʈ�� ����)
				left_node = current_node;
				left_tail_node = current_node;
				left_node = left_node->left;
				while (left_node->right != NULL) { // ���� ����Ʈ���� ���� ū ���� ã�� �� ���� ������
					left_tail_node = left_node;
					left_node = left_node->right;
				}
				right_node = current_node;
				right_tail_node = current_node;
				right_node = right_node->right;
				while (right_node->left != NULL) { // ������ ����Ʈ���� ���� ū ���� ���� ã�� �� ���� ������
					right_tail_node = right_node;
					right_node = right_node->left;
				}
				// right_node �� left_node �� ���� �񱳿��� ū ���� current_node�� ���� �� ���� ���� ����

				if ((left_node->name).compare(right_node->name) > 0) { // ���� ����Ʈ�� ��尡 ŭ
					current_node->name = left_node->name;
					if (left_node->left != NULL) // �����Ϸ��� ����Ʈ���� �ڽĳ�带 ���� ��
						left_tail_node->right = left_node->left;
					else {
						if (current_node == left_tail_node)
							current_node->left = NULL;
						else
							left_tail_node->right = NULL; // �����Ϸ��� ����Ʈ���� �ڽĳ�尡 ���� ��
					}
					delete left_node;
				}
				else if ((left_node->name).compare(right_node->name) <= 0) { // ������ ����Ʈ�� ��尡 ŭ
					current_node->name = right_node->name;
					if (right_node->right != NULL) // �����Ϸ��� ����Ʈ���� �ڽĳ�带 ���� ��
						right_tail_node->left = right_node->right;
					else {
						if (current_node == right_tail_node)
							current_node->right = NULL;
						else
							right_tail_node->left = NULL; // �����Ϸ��� ����Ʈ���� �ڽĳ�尡 ���� ��
					}
					delete right_node;
				}
			}
		}
	}
}

int main()
{
	if (!fin || !fout) { // ���� �б� üũ
		cout << "- System : File checking error" << endl;
		return 1;
	}
	else
		cout << "- System : File checking complete" << endl;

	BST *root = new BST; // root ��带 ����Ű�� ������ ����
	BST_Read(root);
	for (int i = 0; i < MAX_DATA_LENGTH - 1; i++) // ������ �� ���� Ʈ�� ���� �ǽ�
		BST_Insert(root, &root);

	BST temp;
	int input;

	while (1) {
		cout << endl
			<< " < Menu > " << endl
			<< "1. Insert" << endl
			<< "2. Delete" << endl
			<< "3. Print" << endl
			<< "4. Search" << endl
			<< "5. Data write" << endl
			<< "0. Exit" << endl
			<< endl;
		cin >> input;
		if (input == 1) // ����
		{
			cout << "Name : ";
			cin >> temp.name;
			cout << "Phone number : ";
			cin >> temp.phone_num;
			BST_Insert(root, temp, &root);
			cout << "< Result >" << endl;
			BST_Print(root);
		}
		else if (input == 2) { // ����
			cout << "< Result >" << endl;
			cout << "Name : ";
			cin >> temp.name;
			BST_Delete(root, temp, &root);
			cout << "< Result >" << endl;
			BST_Print(root);
		}
		else if (input == 3) { // �ܼ� ���
			cout << "< Result >" << endl;
			BST_Print(root);
		}
		else if (input == 4) { // �˻�
			cout << "Name : ";
			cin >> temp.name;
			cout << "< Result >" << endl;
			BST_Search(root, temp);
		}
		else if (input == 5) { // ���� ���
			BST_Write(root);
			cout << "- System : Date write complete" << endl;
		}
		else {
			break;
		}
	}
	fin.close();
	fout.close();
	return 0;
}