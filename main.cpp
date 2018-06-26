#include <iostream>
#include <fstream>
#include <string>
#define MAX_DATA_LENGTH 12
using namespace std;
ifstream fin("source.txt"); // 입력스트림
ofstream fout("source_output.txt"); // 출력스트림

struct BST
{
	string name;
	string phone_num;
	BST *right = NULL;
	BST *left = NULL;
};

void BST_Read(BST *node) // 파일에서 값 읽은 뒤 노드에 삽입
{
	fin >> node->name;
	fin >> node->phone_num;
}

void BST_Write(BST *root) // 중위순회값(오름차순) 값 텍스트로 출력
{
	if (root)
	{
		BST_Write(root->left);
		fout << root->name << " ";
		fout << root->phone_num << endl;
		BST_Write(root->right);
	}
}

void BST_Print(BST *root) // 중위순회값(오름차순) 값 출력
{
	if (root)
	{
		BST_Print(root->left);
		cout << "Name : " << root->name << " / " << "Phone number : " << root->phone_num << endl;
		BST_Print(root->right);
	}
}

void BST_Search(BST *root, BST search_node) // 중위순회(오름차순) 값 검색
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

void BST_Insert(BST *root, BST **main_root) // 탐색 후 삽입(파일입력)
{
	if ((*main_root) == NULL) {
		(*main_root) = new BST;
		BST_Read(*main_root);
		goto end;
	}
	BST *new_node = new BST;
	BST *current_node = root;
	BST_Read(new_node);
	while (root != NULL) // 탐색 시작
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

void BST_Insert(BST *root, BST Add_node, BST **main_root) // 탐색 후 삽입(콘솔입력) - 함수오버로딩
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
	while (root != NULL) // 탐색 시작
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

	while (current_node != NULL) // 값 찾으러 트리 탐색 시작
	{
		if ((current_node->name).compare(search_node.name) > 0) { // 찾으려는 값이 현재 노드보다 작으면 왼쪽!
			parent_node = current_node;
			delete_node = current_node;
			current_node = current_node->left;
		}
		else if ((current_node->name).compare(search_node.name) < 0) { // 찾으려는 값이 현재 노드보다 크면 오른쪽!
			parent_node = current_node;
			delete_node = current_node;
			current_node = current_node->right;
		}
		else if ((current_node->name).compare(search_node.name) == 0) { // 해당 값 발견! 이제 비교 시작!
																		// 여기서부터 다시 아래의 Case 1, 2, 3판별을 해야한다!
																		/*
																		- 현재상황
																		current_node = 찾으려는 값을 가리키는 포인터
																		parent_node = 찾으려는 값의 부모 노드를 가리키는 포인터
																		*/
			if (current_node->left == NULL && current_node->right == NULL) { // Case 1 시작 (삭제노드의 서브트리 없음)
				if ((parent_node->name).compare(current_node->name) > 0) { // 부모노드보더 더 작은 값이면 부모의 왼쪽 연결해제
					parent_node->left = NULL;
					delete_node = current_node;
					current_node = root;
					delete delete_node;
				}
				else if ((parent_node->name).compare(current_node->name) < 0) { // 부모노드보더 더 큰 값이면 부모의 오른쪽 연결해제
					parent_node->right = NULL;
					delete_node = current_node;
					current_node = root;
					delete delete_node;
				}
				else { // 루트 노드가 유일한 노드일 경우
					(*main_root) = NULL;
					cout << "- System : Tree is Empty" << endl;
					break;
				}
			}
			else if (current_node->left != NULL && current_node->right == NULL) { // Case 2-1 시작 (왼쪽 서브트리 존재)
				delete_node = current_node;
				current_node = current_node->left; // 현재 노드는 parent-delete-current 순서
				if (delete_node == (*main_root)) { // 한쪽 서브트리만 남은 루트 노드 삭제시 포인터를 아래로 내림
					(*main_root) = current_node;
				}
				else
					delete delete_node;
				if ((parent_node->name).compare(current_node->name) > 0) { // 부모노드보더 더 작은 값이면 부모의 왼쪽에 연결
					parent_node->left = current_node;
				}
				else if ((parent_node->name).compare(current_node->name) <= 0) { // 부모노드보더 더 큰 값이면 부모의 오른쪽에 연결
					parent_node->right = current_node;
				}
			}
			else if (current_node->left == NULL && current_node->right != NULL) { // Case 2-2 시작 (오른쪽 서브트리 존재)
				delete_node = current_node;
				current_node = current_node->right;
				if (delete_node == (*main_root)) { // 한쪽 서브트리만 남은 루트 노드 삭제시 포인터를 아래로 내림
					(*main_root) = current_node;
				}
				else
					delete delete_node;
				if ((parent_node->name).compare(current_node->name) > 0) { // 부모노드보더 더 작은 값이면 부모의 왼쪽에 연결
					parent_node->left = current_node;
				}
				else if ((parent_node->name).compare(current_node->name) <= 0) { // 부모노드보더 더 큰 값이면 부모의 오른쪽에 연결
					parent_node->right = current_node;
				}
			}
			else if (current_node->left != NULL && current_node->right != NULL) { // Case 3 시작 (양쪽 서브트리 존재)
				left_node = current_node;
				left_tail_node = current_node;
				left_node = left_node->left;
				while (left_node->right != NULL) { // 왼쪽 서브트리의 가장 큰 값을 찾을 때 까지 내려감
					left_tail_node = left_node;
					left_node = left_node->right;
				}
				right_node = current_node;
				right_tail_node = current_node;
				right_node = right_node->right;
				while (right_node->left != NULL) { // 오른쪽 서브트리의 가장 큰 작은 값을 찾을 때 까지 내려감
					right_tail_node = right_node;
					right_node = right_node->left;
				}
				// right_node 와 left_node 의 값을 비교에서 큰 놈을 current_node에 복사 후 기존 노드는 삭제

				if ((left_node->name).compare(right_node->name) > 0) { // 왼쪽 서브트리 노드가 큼
					current_node->name = left_node->name;
					if (left_node->left != NULL) // 제거하려는 서브트리가 자식노드를 가질 때
						left_tail_node->right = left_node->left;
					else {
						if (current_node == left_tail_node)
							current_node->left = NULL;
						else
							left_tail_node->right = NULL; // 제거하려는 서브트리의 자식노드가 없을 때
					}
					delete left_node;
				}
				else if ((left_node->name).compare(right_node->name) <= 0) { // 오른쪽 서브트리 노드가 큼
					current_node->name = right_node->name;
					if (right_node->right != NULL) // 제거하려는 서브트리가 자식노드를 가질 때
						right_tail_node->left = right_node->right;
					else {
						if (current_node == right_tail_node)
							current_node->right = NULL;
						else
							right_tail_node->left = NULL; // 제거하려는 서브트리의 자식노드가 없을 때
					}
					delete right_node;
				}
			}
		}
	}
}

int main()
{
	if (!fin || !fout) { // 파일 읽기 체크
		cout << "- System : File checking error" << endl;
		return 1;
	}
	else
		cout << "- System : File checking complete" << endl;

	BST *root = new BST; // root 노드를 가리키는 포인터 생성
	BST_Read(root);
	for (int i = 0; i < MAX_DATA_LENGTH - 1; i++) // 파일의 끝 까지 트리 삽입 실시
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
		if (input == 1) // 삽입
		{
			cout << "Name : ";
			cin >> temp.name;
			cout << "Phone number : ";
			cin >> temp.phone_num;
			BST_Insert(root, temp, &root);
			cout << "< Result >" << endl;
			BST_Print(root);
		}
		else if (input == 2) { // 삭제
			cout << "< Result >" << endl;
			cout << "Name : ";
			cin >> temp.name;
			BST_Delete(root, temp, &root);
			cout << "< Result >" << endl;
			BST_Print(root);
		}
		else if (input == 3) { // 콘솔 출력
			cout << "< Result >" << endl;
			BST_Print(root);
		}
		else if (input == 4) { // 검색
			cout << "Name : ";
			cin >> temp.name;
			cout << "< Result >" << endl;
			BST_Search(root, temp);
		}
		else if (input == 5) { // 파일 출력
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