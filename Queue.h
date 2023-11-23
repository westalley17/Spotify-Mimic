    #include "libraries.h"

    // give an overview of this class

    class Queue
    {
        private:
            struct Node
            {
                Song* song;
                Node *next;
            };
            Node *head;
            Node *tail;

        public:
            Queue()
            {
                head = NULL;
                tail = NULL;
            }

            ~Queue()
            {
                Node* temp;
                while(head)
                {
                    temp = head->next;
                    delete head;
                    head = temp;
                }
            }

            void addSongToDefaultQueue(Song* newSong)
            {
                Node *newNode = new Node;
                newNode->song = newSong;
                newNode->next = NULL;

                if (!head)
                {
                    head = newNode;
                    tail = newNode;
                }

                else
                {
                    char dupChoice;
                    if (validateSongChoice(newSong->songName))
                    {
                        std::cout << std::endl << newSong->songName << " is already in your queue. Would you still like to add it to the queue? (y or n)\n"
                                << "Choice: ";
                        while (!(std::cin >> dupChoice) || (tolower(dupChoice) != 'y' && tolower(dupChoice) != 'n')) // restrains the user from screwing up my hard work.
                        {
                            std::cin.clear();
                            std::cin.ignore(100, '\n');
                            std::cout << "You must input y or n:\n"
                                    << "Continue? (y or n): ";
                        }
                        if (tolower(dupChoice) == 'n')
                            return;
                    }
                    tail->next = newNode;
                    tail = newNode;
                }
            }

            void addSongToManualQueue(Song* newSong)
            {
                Node *newNode = new Node;
                newNode->song = newSong;
                newNode->next = NULL;

                if (!head) // no queue
                {
                    head = newNode;
                    tail = newNode;
                }
                else
                {
                    char dupChoice;
                    if (validateSongChoice(newSong->songName))
                    {
                        std::cout << std::endl << newSong->songName << " is already in your queue. Would you still like to add it to the queue? (y or n)\n"
                                << "Choice: ";
                        while (!(std::cin >> dupChoice) || (tolower(dupChoice) != 'y' && tolower(dupChoice) != 'n')) // restrains the user from screwing up my hard work.
                        {
                            std::cin.clear();
                            std::cin.ignore(100, '\n');
                            std::cout << "You must input y or n:\n"
                                    << "Continue? (y or n): ";
                        }
                        if (tolower(dupChoice) == 'n')
                            return;
                    }
                    tail->next = newNode;
                    tail = newNode;
                }
            }

            void dequeue()
            {
                if (!head)
                    std::cout << "\nQueue is empty!\n";
                else
                {
                    Node *tempPtr = head;
                    head = head->next;
                    std::cout << "Now playing " << tempPtr->song->songName << " by " << tempPtr->song->artist << " for " << tempPtr->song->minutes << " minutes!\n";
                    delete tempPtr->song;
                    delete tempPtr;
                }
            }

            void deleteSongFromQueue(const std::string& unwantedSong)
            {
                if (head)
                {
                    if (head->next) // multiple songs in queue.
                    {

                        Node *temp = head;
                        if (temp->song->songName == unwantedSong) // if the first song is the unwanted song.
                        {
                            head = head->next;
                            delete temp;
                            return;
                        }
                        while (temp->next && temp->next->song->songName != unwantedSong)
                            temp = temp->next;
                        Node *delNode = temp->next;
                        temp->next = temp->next->next;
                        delete delNode;
                    }
                    else // only one song in queue.
                    {
                        std::cout << "\nDeleted " << head->song->songName << " from the queue.\n";
                        delete head;
                        head = NULL;
                    }
                }
            }

            int printQueue()
            {
                if (isEmpty())
                {
                    std::cout << "\nThe queue is empty NOW!\n";
                    return 0;
                }
                Node *temp = head;
                while (temp)
                {
                    std::cout << "--> " << temp->song->songName << std::endl;
                    temp = temp->next;
                }
                return 1;
            }

            bool isEmpty()
            {
                if (!head)
                    return true;
                else
                    return false;
            }

            bool validateSongChoice(const std::string& songChoice)
            {
                Node *tempPtr = head;
                while (tempPtr)
                {
                    if (tempPtr->song->songName == songChoice)
                        return true;
                    tempPtr = tempPtr->next;
                }
                return false;
            }
    };