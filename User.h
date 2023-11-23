#include "libraries.h"

// give a more descriptive overview of this class

class User
{
    private:
        std::string username, password;
        Song* library;       // will be used to dynamically allocate an array of Songs later on.
        int libCapacity; // this starts the size of the library at 1 so that the user can keep doubling the array size until they have added all the songs that they want.
        int currCapacity;

        void quicksort(Song*& library, int low, int high)
        {
            int lowEndIndex;

            if (low >= high) // base case
                return;
            lowEndIndex = partition(library, low, high);
            quicksort(library, low, lowEndIndex);
            quicksort(library, lowEndIndex + 1, high);
        }

        int partition(Song* library, int left, int right)
        {
            int mid, pivot;
            Song temp;
            mid = left + (right - left) / 2;
            pivot = library[mid].minutes;

            bool done = false;
            while (!done)
            {
                while (library[left].minutes < pivot)
                {
                    left += 1;
                }
                while (pivot < library[right].minutes)
                {
                    right -= 1;
                }
                if (left >= right)
                    done = true;
                else
                {
                    temp = library[left];
                    library[left] = library[right];
                    library[right] = temp;
                    left += 1;
                    right -= 1;
                }
            }
            return right;
        }

    public:
        Queue* queue;

        User(const std::string& user, const std::string& pass)
        {
            username = user;
            password = pass;
            libCapacity = 1;
            currCapacity = 0;
            library = NULL;
            queue = NULL;
        }

        ~User()
        {
            delete [] library;
            delete queue;
        }

        const std::string& getUserName() const
        {
            return username;
        }

        const std::string& getPassWord() const
        {
            return password;
        }

        const Song getLibrarySong(int index) const
        {
            return library[index];
        }

        const int getLibrarySize() const
        {
            return currCapacity;
        }

        const Song* getLibrary() const
        {
            return library;
        }

        void addSongToLibrary(Song newSong)
        {
            if (!library) // for the edge case of the first song being added to the User's playlist.
            {
                library = new Song[libCapacity];
                library[currCapacity] = newSong;
                currCapacity++;
            }
            else
            {
                if (currCapacity == libCapacity)
                    resizeLibrary();
                library[currCapacity] = newSong;
                currCapacity++;
            }
        }

        void resizeLibrary()
        {
            libCapacity *= 2;
            Song *largerLib = new Song[libCapacity];
            for (int i = 0; i < currCapacity; i++)
                largerLib[i] = library[i];
            delete[] library; // deletes the smaller array.
            library = largerLib;
        }

        void printLibrary()
        {
            for (int i = 0; i < currCapacity; i++)
                std::cout << i + 1 << ". " << library[i].songName << std::endl;
        }

        bool duplicateSong(Song bufferSong)
        {
            for (int i = 0; i < currCapacity; i++)
            {
                if (bufferSong.songName == library[i].songName)
                    return true;
            }
            return false;
        }

        void shuffleLibrary()
        {
        }

        void songLengthSort()
        {
            quicksort(library, 0, currCapacity - 1);
        }
};