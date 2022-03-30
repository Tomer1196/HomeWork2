#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	long unsigned id;
	char* name;
	long int salary;
	int gregYear;
	char hebYear[6];
}Worker;

typedef struct WorkerList
{
	Worker* data;
	struct WorkerList* next;
} WorkerList;

Worker* CreateWorker(Worker* n);
void PrintWorker(Worker* n, int type);
WorkerList* AddWorker(WorkerList* head, Worker* w);
int indexLoop(WorkerList* head, long unsigned id);
int indexReq(WorkerList* head, long unsigned id);
WorkerList* deleteWorstWorker(WorkerList* head);
void update_worker(WorkerList* head, float percent);
WorkerList* reverse(WorkerList* head);
void freeWorkers(WorkerList* head);

void main()
{
	int type1, type2;
	WorkerList* list = NULL;
	Worker* worker = (Worker*)malloc(sizeof(Worker));
	Worker* worker2 = (Worker*)malloc(sizeof(Worker));
	//worker->id = (238983289);                               אופציות לדוגמא במידת הצורך
	//worker->name = "notguy";
	//worker->salary = 250;
	//worker->gregYear = 2994; //NULL;

	//Worker* worker2 = (Worker*)malloc(sizeof(Worker));
	//worker2->id = 234516641;
	//worker2->name = "nottomer";
	//worker2->salary = 640;
	//worker2->gregYear = 2992;

	//Worker* worker4 = (Worker*)malloc(sizeof(Worker));
	//worker4->id = 43289;
	//worker4->name = "guy";
	//worker4->salary = 120;
	//worker4->gregYear = 2994; //NULL;

	//Worker* worker3 = (Worker*)malloc(sizeof(Worker));
	//worker3->id = 913428;
	//worker3->name = "tomer";
	//worker3->salary = 500;
	//worker3->gregYear = 2992;

	worker = CreateWorker(&worker);
	worker2 = CreateWorker(&worker2);
	if (worker->gregYear == NULL)
		type1 = 1;
	else
		type1 = 0;

	if (worker2->gregYear == NULL)
		type2 = 1;
	else
		type2 = 0;

	PrintWorker(worker, type1);
	PrintWorker(worker2, type2);

	list = AddWorker(list, worker);
	list = AddWorker(list, worker2);
	//list = AddWorker(list, worker3);
	//list = AddWorker(list, worker4);

	printList(list);

	int num = indexReq(list, 234516641);
	if (num == -1)
		printf("\n Worker hasn't found in the list \n");
	else
	{
		printf("\n Worker place in the list is - %d \n", num);
	}

	list = reverse(list);

	printList(list);

	update_worker(list, 10);

	printList(list);

	deleteWorstWorker(list);
	
	printList(list);

	int num1 =indexLoop(list, 913428);
	if (num1 == -1)
		printf("\n Worker hasn't found in the list \n");
	else
	{
		printf("\n Worker place in the list is - %d \n", num1);
	}
	
	freeWorkers(list);


}
int printList(WorkerList* list)
{
	WorkerList* ptr = list;
	if (ptr == NULL)
	{
		printf("list is empty");
		return;
	}
	printf("\n--the list:--\n");
	while (ptr != NULL)
	{
		printf("Worker details are :\n Id - %d \n Name - %s \n Salary - %d \n Starting date - %d\n", ptr->data->id, ptr->data->name, ptr->data->salary, ptr->data->gregYear);
		ptr = ptr->next;
	}
	return 0;
}

Worker* CreateWorker(Worker* n)
{
	int type = 0;
	Worker* temp = (Worker*)malloc(sizeof(Worker));
	temp->name = (char*)malloc(100 * sizeof(char));
	if (n == NULL) {
		printf("Bad allocation\n");
		return NULL;
	}
	printf("Enter worker id: ");
	scanf("%d", &temp->id);
	printf("Enter worker name: ");
	scanf("%s", (temp->name));
	printf("Enter the workers salary: ");
	scanf("%d", &(temp->salary));
	printf("Enter the workers starting year, Press 0 for Hebrew date Or 1 for Greg:\n ");
	scanf("%d", &type);

	switch (type)
	{
	case 0:
		printf("Enter the year - ");
		scanf("%s", &temp->hebYear);
		break;

	case 1:
		printf("Enter the date - ");
		scanf_s("%d", &temp->gregYear);
		break;

	default:
		printf("Invalid input, please re-enter your choice: ");
	}
	n = temp;
	return n;
}
void PrintWorker(Worker* n, int type) {
	if (type == 0)
	{
		printf("Worker details are :\n Id - %d \n Name - %s \n Salary - %d \n Starting date - %d\n", n->id, n->name, n->salary, n->gregYear);
	}
	else
	{
		printf("Worker details are :\n Id - %d \n Name - %s \n Salary - %d \n Starting date - %s\n", n->id, n->name, n->salary, n->hebYear);
	}

}

WorkerList* AddWorker(WorkerList* head, Worker* w1) {
	WorkerList* new_worker = (WorkerList*)malloc(sizeof(WorkerList));  // locating larger memory slot for bigger lincked list.
	if (!new_worker) {  // check if location searching has failed.
		puts("allocation faild");
		return head;
	}
	new_worker->data = w1;  // insert new worker in to data of the new worker part of the list.
	new_worker->next = 0;  // reset next pointer of new worker.
	if (head == NULL) {  // check if list is empty.
		head = w1;  // insert new worker in to first locations data in the lincked list.
		new_worker->next = NULL;
		return new_worker;
	}
	WorkerList* ptr = NULL;
	WorkerList* temp = head;

	while (temp != NULL && temp->data->salary < new_worker->data->salary) {  // move temp to last position unless correct location is found.
		ptr = temp;
		temp = temp->next;
	}
	new_worker->next = temp;  // if proper location wasn't found add worker to last place. 
	if (ptr) {  // set next location as new worker.
		ptr->next = new_worker;
	}
	else {
		head = new_worker;
	}
	return head;
}

int indexLoop(WorkerList* head, long unsigned id)
{
	WorkerList* ptr;
	int counter = 1;
	for (ptr = head; ptr != NULL; ptr = ptr->next)
	{
		if (ptr->data->id == id)
		{
			return ++counter;
		}
		counter++;
	}
	return -1;
}
int indexReq(WorkerList* head, long unsigned id)
{
	WorkerList* ptr = head;
	if (ptr == NULL)
		return -1;
	if (ptr->data->id == id)
	{
		return 1;
	}
	if (indexReq(ptr->next, id) == -1)
		return;
	else
	{
		return 1 + indexReq(ptr->next, id);
	}

	
}
WorkerList* deleteWorstWorker(WorkerList* head)
{
	WorkerList* ptr = head;
	WorkerList* ptr2 = head;
	int salary = ptr->data->salary;
	int counter = 0, index = 0;
	while (ptr != NULL)
	{
		if (ptr->data->salary < salary)
		{
			salary = ptr->data->salary;
			index = counter;
		}
		ptr = ptr->next;
		counter += 1;
	}
	if (head->data->salary == salary) {
		head = head->next;
		ptr2->next = NULL;
		return head;
	}
	for (int rightI = 0; rightI <= index; rightI++) {
		ptr2 = ptr2->next;  //  progres temp1 until index before lowest salary index that was found.
		if (ptr2->next->data->salary == salary) {
			if (ptr2->next->next == NULL) {
				ptr2->next = NULL;
			}
			else {
				ptr2->next = ptr2->next->next;
			}
			break;
		}
	}
	return head;
}

void update_worker(WorkerList* head, float percent) {
	WorkerList* curr = head; //Creating a copy of the head integer
	while (curr) {
		curr->data->salary += curr->data->salary * (percent * 0.01); // Calculates the the new payment
		curr = curr->next; //Passing the pointer to the next integer
	}
}

WorkerList* reverse(WorkerList* head)
{
	if (head->next == NULL)
		return head;
	WorkerList* temp = reverse(head->next);
	head->next->next = head;
	head->next = NULL;
	return temp;
}
void freeWorkers(WorkerList* head)
{
	while (head->data != NULL)
	{
		free(head->data);
		head->data = head->next->data;
	}
}