#include "globals.h"

typedef struct
{
    int id;
    bool state;
    String days[MAX_DAYS];
    String time;
    struct
    {
        int relayId;
        String action;
    } actions[MAX_ACTIONS];
    int actionCount;
    String lastTriggered;
} Schedule;

class DLinkedList
{
public:
    class Node
    {
    public:
        Schedule schedule;
        Node *next;

        Node(Schedule schedule, Node *next = nullptr)
        {
            this->schedule = schedule;
            this->next = next;
        }
    };

private:
    Node *head;
    Node *tail;
    int count;

public:
    DLinkedList()
    {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    ~DLinkedList()
    {
        while (head != nullptr)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void add(Schedule schedule)
    {
        Node *newNode = new Node(schedule);
        if (count == 0)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    void insertAt(int index, Schedule schedule)
    {
        if (index < 0 || index > count)
        {
            throw std::out_of_range("Index is out of range!");
        }

        Node *newNode = new Node(schedule);
        if (index == 0)
        {
            newNode->next = head;
            head = newNode;
            if (tail == nullptr)
            {
                tail = newNode;
            }
        }
        else
        {
            Node *temp = head;
            for (int i = 0; i < index - 1; i++)
            {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
            if (newNode->next == nullptr)
            {
                tail = newNode;
            }
        }
        count++;
    }

    void removeAt(int index)
    {
        if (index < 0 || index >= count)
        {
            throw std::out_of_range("Index is out of range!");
        }

        Node *temp = head;
        if (index == 0)
        {
            head = head->next;
            if (head == nullptr)
            {
                tail = nullptr;
            }
            delete temp;
        }
        else
        {
            Node *prev = nullptr;
            for (int i = 0; i < index; i++)
            {
                prev = temp;
                temp = temp->next;
            }
            prev->next = temp->next;
            if (temp == tail)
            {
                tail = prev;
            }
            delete temp;
        }
        count--;
    }

    void reverse()
    {
        Node *prev = nullptr;
        Node *current = head;
        Node *next = nullptr;

        while (current != nullptr)
        {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        tail = head;
        head = prev;
    }

    bool empty()
    {
        return count == 0;
    }

    int size()
    {
        return count;
    }

    Schedule *getAt(int index)
    {
        if (index < 0 || index >= count)
        {
            throw std::out_of_range("Index is out of range!");
        }

        Node *temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        return &temp->schedule;
    }

    bool contains(int id)
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            if (temp->schedule.id == id)
            {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void printList()
    {
        Node *temp = head;
        Serial.println("Danh sách lịch trình:");
        while (temp != nullptr)
        {
            Serial.printf("  ID=%d, State=%s, Time=%s, ActionCount=%d\n",
                          temp->schedule.id,
                          temp->schedule.state ? "ON" : "OFF",
                          temp->schedule.time.c_str(),
                          temp->schedule.actionCount);
            temp = temp->next;
        }
    }
};
