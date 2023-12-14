#pragma once
struct Node
{
    Position element;
    Node *next;
    Node(Position pos)
    {
        element = pos;
        next = NULL;
    }
};
typedef Node *node;

struct Queue
{
    node front, rear;
    int size;
    Queue()
    {
        front = rear = NULL;
        size = 0;
    }

    void enqueue(Position pos)
    {
        node temp = new Node(pos);
        size++;
        if (rear == NULL)
        {
            front = rear = temp;
            return;
        }

        rear->next = temp;
        rear = temp;
    }

    Position dequeue()
    {
        if (front == NULL)
        {
            Position tmp;
            return tmp; // return (-1,-1)
        }

        size--;
        node temp = front;
        front = front->next;

        if (front == NULL)
        {
            rear = NULL;
        }

        return temp->element;
    }

    void clear()
    {
        front = rear = NULL;
        size = 0;
    }

    void initialize(int queueInitialLenght)
    {
        Position nullPos;
        for (int i = 0; i < queueInitialLenght; i++)
        {
            enqueue(nullPos);
        }
    }
};
