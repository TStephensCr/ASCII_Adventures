struct Node
{
    MyPosition element;
    Node *next;
    Node(MyPosition pos)
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

    void enqueue(MyPosition pos)
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

    MyPosition dequeue()
    {
        if (front == NULL)
        {
            MyPosition tmp;
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
        MyPosition nullPos;
        for (int i = 0; i < queueInitialLenght; i++)
        {
            enqueue(nullPos);
        }
    }
};
